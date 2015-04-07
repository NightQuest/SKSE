#include "PapyrusEvents.h"
#include "GameMenus.h"
#include "GameReferences.h"
#include "GameRTTI.h"
#include <set>
#include "PapyrusArgs.h"
#include "Hooks_Scaleform.h"

//// Global instances

RegistrationMapHolder<BSFixedString>						g_menuOpenCloseRegs;
RegistrationMapHolder<UInt32>								g_inputKeyEventRegs;
RegistrationMapHolder<BSFixedString>						g_inputControlEventRegs;
RegistrationMapHolder<BSFixedString,ModCallbackParameters>	g_modCallbackRegs;

RegistrationSetHolder<NullParameters>						g_cameraEventRegs;
RegistrationSetHolder<NullParameters>						g_crosshairRefEventRegs;

EventDispatcher<SKSEModCallbackEvent>	g_modCallbackEventDispatcher;
EventDispatcher<SKSECameraEvent>		g_cameraEventDispatcher;
EventDispatcher<SKSECrosshairRefEvent>	g_crosshairRefEventDispatcher;

MenuEventHandler			g_menuEventHandler;
InputEventHandler			g_inputEventHandler;
ModCallbackEventHandler		g_modCallbackEventHandler;
CameraEventHandler			g_cameraEventHandler;
CrosshairRefEventHandler	g_crosshairRefEventHandler;

//// Generic functors

template <typename T> void SetVMValue(VMValue * val, T arg)
{
	VMClassRegistry * registry = (*g_skyrimVM)->GetClassRegistry();
	PackValue(val, &arg, registry);
}

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

EventResult MenuEventHandler::ReceiveEvent(MenuOpenCloseEvent * evn, EventDispatcher<MenuOpenCloseEvent> * dispatcher)
{
	BSFixedString eventName = evn->opening ? BSFixedString("OnMenuOpen") : BSFixedString("OnMenuClose");

	g_menuOpenCloseRegs.ForEach(
		evn->menuName,
		EventQueueFunctor1<BSFixedString>(eventName, evn->menuName)
	);

	return kEvent_Continue;
}

EventResult InputEventHandler::ReceiveEvent(InputEvent ** evns, InputEventDispatcher * dispatcher)
{
	// Function is called periodically, if no buttons pressed/held *evns == NULL
	if (! *evns)
		return kEvent_Continue;

	for (InputEvent * e = *evns; e; e = e->next)
	{
		if (e->eventType != InputEvent::kEventType_Button)
			continue;

		ButtonEvent * t = DYNAMIC_CAST(e, InputEvent, ButtonEvent);

		UInt32	keyCode;
		UInt32	deviceType = t->deviceType;
		UInt32	keyMask = t->keyMask;

		// Mouse
		if (deviceType == kDeviceType_Mouse)
			keyCode = InputMap::kMacro_MouseButtonOffset + keyMask; 
		// Gamepad
		else if (deviceType == kDeviceType_Gamepad)
			keyCode = InputMap::GamepadMaskToKeycode(keyMask);
		// Keyboard
		else
			keyCode = keyMask;

		// Valid scancode?
		if (keyCode >= InputMap::kMaxMacros)
			continue;

		BSFixedString	control	= *t->GetControlID();
		float			timer	= t->timer;

		bool isDown	= t->flags != 0 && timer == 0.0;
		bool isUp	= t->flags == 0 && timer != 0;

		if (isDown)
		{
			// Used by scaleform skse.GetLastControl
			SetLastControlDown(control.data, keyCode);

			g_inputKeyEventRegs.ForEach(
				keyCode,
				EventQueueFunctor1<SInt32>(BSFixedString("OnKeyDown"), (SInt32)keyCode)
			);
			g_inputControlEventRegs.ForEach(
				control,
				EventQueueFunctor1<BSFixedString>(BSFixedString("OnControlDown"), control)
			);
		}
		else if (isUp)
		{
			SetLastControlUp(control.data, keyCode);

			g_inputKeyEventRegs.ForEach(
				keyCode,
				EventQueueFunctor2<SInt32, float>(BSFixedString("OnKeyUp"), (SInt32)keyCode, timer)
			);
			g_inputControlEventRegs.ForEach(
				control,
				EventQueueFunctor2<BSFixedString, float>(BSFixedString("OnControlUp"), control, timer)
			);
		}
	}

	return kEvent_Continue;
}

EventResult ModCallbackEventHandler::ReceiveEvent(SKSEModCallbackEvent * evn, EventDispatcher<SKSEModCallbackEvent> * dispatcher)
{
	const char * eventNameData = evn->eventName.data;

	g_modCallbackRegs.ForEach(
		evn->eventName,
		ModCallbackEventFunctor(evn->eventName, evn->sender, evn->strArg, evn->numArg)
	);

	return kEvent_Continue;
}

EventResult CameraEventHandler::ReceiveEvent(SKSECameraEvent * evn, EventDispatcher<SKSECameraEvent> * dispatcher)
{
	SInt32 oldState = -1;
	SInt32 newState = -1;

	PlayerCamera * playerCamera = PlayerCamera::GetSingleton();
	if(playerCamera) {
		for(int i = 0; i < PlayerCamera::kNumCameraStates; i++) {
			if(evn->oldState == playerCamera->cameraStates[i])
				oldState = i;
			if(evn->newState == playerCamera->cameraStates[i])
				newState = i;
		}
	}

	g_cameraEventRegs.ForEach(
		EventQueueFunctor2<SInt32, SInt32>(BSFixedString("OnPlayerCameraState"), oldState, newState)
	);

	return kEvent_Continue;
}

EventResult CrosshairRefEventHandler::ReceiveEvent(SKSECrosshairRefEvent * evn, EventDispatcher<SKSECrosshairRefEvent> * dispatcher)
{
	g_crosshairRefEventRegs.ForEach(
		EventQueueFunctor1<TESObjectREFR*>(BSFixedString("OnCrosshairRefChange"), evn->crosshairRef)
	);

	return kEvent_Continue;
}
