#include "PapyrusEvents.h"
#include "GameMenus.h"
#include "GameRTTI.h"
#include <set>
#include "PapyrusArgs.h"


//// Global instances

RegistrationMapHolder<BSFixedString>						g_menuOpenCloseRegs;
RegistrationMapHolder<UInt32>								g_inputEventRegs;
RegistrationMapHolder<BSFixedString,ModCallbackParameters>	g_modCallbackRegs;
EventDispatcher<SKSEModCallbackEvent>						g_modCallbackEventDispatcher;
SKSEEventHandler											g_skseEventHandler;


//// Generic functors

template <typename T> void SetVMValue(VMValue * val, T arg);

template <> void SetVMValue<bool> (VMValue * val, bool arg)						{ val->SetBool(arg); }
template <> void SetVMValue<SInt32> (VMValue * val, SInt32 arg)					{ val->SetInt(arg); }
template <> void SetVMValue<float> (VMValue * val, float arg)					{ val->SetFloat(arg); }
template <> void SetVMValue<BSFixedString> (VMValue * val, BSFixedString arg)	{ val->SetString(arg.data); }


template <typename T1>
class EventQueueFunctor1 : public IFunctionArguments
{
public:
	EventQueueFunctor1(BSFixedString & a_eventName, T1 a_arg1)
		: eventName(a_eventName.data), arg1(a_arg1) {}

	virtual bool	Copy(Output * dst)
	{
		dst->Resize(1);
		SetVMValue(dst->Get(0), arg1);

		return true;
	}

	void			operator() (const EventRegistration<NullParameters> & reg)
	{
		VMClassRegistry * registry = (*g_skyrimVM)->GetClassRegistry();
		registry->QueueEvent(reg.handle, &eventName, this);
	}

private:
	BSFixedString	eventName;
	T1				arg1;
};

template <typename T1, typename T2>
class EventQueueFunctor2 : public IFunctionArguments
{
public:
	EventQueueFunctor2(BSFixedString & a_eventName, T1 a_arg1, T2 a_arg2)
		: eventName(a_eventName.data), arg1(a_arg1), arg2(a_arg2) {}

	virtual bool	Copy(Output * dst)
	{
		dst->Resize(2);
		SetVMValue(dst->Get(0), arg1);
		SetVMValue(dst->Get(1), arg2);

		return true;
	}

	void			operator() (const EventRegistration<NullParameters> & reg)
	{
		VMClassRegistry * registry = (*g_skyrimVM)->GetClassRegistry();
		registry->QueueEvent(reg.handle, &eventName, this);
	}

private:
	BSFixedString	eventName;
	T1				arg1;
	T2				arg2;
};

//// Specific functors

class ModCallbackEventFunctor : public IFunctionArguments
{
public:
	ModCallbackEventFunctor(BSFixedString & a_eventName, TESForm * a_sender, BSFixedString & a_strArg, float a_numArg)
		: eventName(a_eventName.data), strArg(a_strArg.data), numArg(a_numArg), sender(a_sender) {}

	virtual bool	Copy(Output * dst)
	{
		VMClassRegistry * registry = (*g_skyrimVM)->GetClassRegistry();

		dst->Resize(4);
		dst->Get(0)->SetString(eventName.data);
		dst->Get(1)->SetString(strArg.data);
		dst->Get(2)->SetFloat(numArg);
		PackValue(dst->Get(3), &sender, registry);

		return true;
	}

	void			operator() (const EventRegistration<ModCallbackParameters> & reg)
	{
		VMClassRegistry * registry = (*g_skyrimVM)->GetClassRegistry();
		registry->QueueEvent(reg.handle, &reg.params.callbackName, this);
	}

private:
	BSFixedString	eventName;
	BSFixedString	strArg;
	float			numArg;
	TESForm			* sender;
};


//// Event handlers

EventResult SKSEEventHandler::ReceiveEvent(MenuOpenCloseEvent * evn, EventDispatcher<MenuOpenCloseEvent> * dispatcher)
{
#if _DEBUG
	_MESSAGE("Received internal MenuOpenCloseEvent. Name: %s, Opening: %d", evn->menuName, evn->opening);
#endif

	BSFixedString eventName = evn->opening ? BSFixedString("OnMenuOpen") : BSFixedString("OnMenuClose");

	g_menuOpenCloseRegs.ForEach(
		evn->menuName,
		EventQueueFunctor1<BSFixedString>(eventName, evn->menuName)
	);

	return kEvent_Continue;
}

EventResult SKSEEventHandler::ReceiveEvent(InputEvent ** evns, InputEventDispatcher * dispatcher)
{
	// Function is called periodically, if no buttons pressed/held *evns == NULL

	static UInt8	keyState[InputMap::kMaxMacros] = { 0 };
	static float	keyTimer[InputMap::kMaxMacros] = { 0 };

	for (UInt32 i = 0; i < InputMap::kMaxMacros; i++)
	{
		if (keyState[i] && (--keyState[i] == 0))
		{
			g_inputEventRegs.ForEach(
				i,
				EventQueueFunctor2<SInt32, float>(BSFixedString("OnKeyUp"), (SInt32)i, keyTimer[i])
			);
		}
	}

	if (! *evns)
		return kEvent_Continue;

	for (InputEvent * e = *evns; e; e = e->next)
	{
		switch(e->eventType)
		{
			case InputEvent::kEventType_Button:
			{
				ButtonEvent * t = DYNAMIC_CAST(e, InputEvent, ButtonEvent);

				UInt32 keyCode;
				UInt32 deviceType = t->deviceType;
				UInt32 keyMask = t->keyMask;

				// Mouse
				if (deviceType == kDeviceType_Mouse)
					keyCode = InputMap::kMacro_MouseButtonOffset + keyMask; 

				// Gamepad
				else if (deviceType == kDeviceType_Gamepad)
					keyCode = InputMap::GetGamepadKeycode(keyMask);

				// Keyboard
				else
					keyCode = keyMask;

				// Valid scancode?
				if (keyCode >= InputMap::kMaxMacros)
					break;

				if (!keyState[keyCode])
				{
					g_inputEventRegs.ForEach(
						keyCode,
						EventQueueFunctor1<SInt32>(BSFixedString("OnKeyDown"), (SInt32)keyCode)
					);
				}

				keyState[keyCode] = 2;
				keyTimer[keyCode] = t->timer;

				break;
			}
		};
	}

	return kEvent_Continue;
}

EventResult SKSEEventHandler::ReceiveEvent(SKSEModCallbackEvent * evn, EventDispatcher<SKSEModCallbackEvent> * dispatcher)
{
#if _DEBUG
	_MESSAGE("Received internal SKSEModCallbackEvent. EventName: %s. strArg: %s. numArg: %d", evn->eventName, evn->strArg, evn->numArg);
#endif

	const char * eventNameData = evn->eventName.data;

	g_modCallbackRegs.ForEach(
		evn->eventName,
		ModCallbackEventFunctor(evn->eventName, evn->sender, evn->strArg, evn->numArg)
	);

	return kEvent_Continue;
}
