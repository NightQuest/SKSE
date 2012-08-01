#pragma once

#include "GameForms.h"
#include "GameTypes.h"
#include "GameEvents.h"
#include <map>
#include <set>


// crashes otherwise
#pragma pack (push, 4)

template <typename D>
class EventRegistration
{
public:

	UInt64	handle;
	D		params;

	bool operator<(const EventRegistration & rhs) const	{ return handle < rhs.handle; }
};

#pragma pack (pop, 4)

template <typename K, typename D = void*>
class RegistrationMapHolder : public SafeDataHolder<std::map<K,std::set<EventRegistration<D>>>>
{
	typedef std::set<EventRegistration<D>>	RegSet;
	typedef std::map<K,RegSet>				RegMap;

public:

	void Register(TESForm * form, K& key, D * params = NULL)
	{
		VMClassRegistry		* registry =	(*g_skyrimVM)->GetClassRegistry();
		IObjectHandlePolicy	* policy =		registry->GetHandlePolicy();

		EventRegistration<D> reg;
		reg.handle = policy->Create(form->formType, (void *)form);
		if (params)
			reg.params = *params;
		
		Lock();

		if (m_data[key].insert(reg).second)
			policy->AddRef(reg.handle);

		Release();
	}

	void Unregister(TESForm * form, K& key)
	{
		VMClassRegistry		* registry =	(*g_skyrimVM)->GetClassRegistry();
		IObjectHandlePolicy	* policy =		registry->GetHandlePolicy();

		EventRegistration<D> reg;
		reg.handle = policy->Create(form->formType, (void *)form);

		Lock();

		if (m_data[key].erase(reg))
			policy->Release(reg.handle);

		Release();
	}

	void UnregisterFromAll(TESForm * form)
	{
		VMClassRegistry		* registry =	(*g_skyrimVM)->GetClassRegistry();
		IObjectHandlePolicy	* policy =		registry->GetHandlePolicy();

		EventRegistration<D> reg;
		reg.handle = policy->Create(form->formType, (void *)form);

		Lock();

		for (RegMap::iterator iter = m_data.begin(); iter != m_data.end(); ++iter)
			if (iter->second.erase(reg))
				policy->Release(reg.handle);

		Release();
	}

	void UnregisterFromAll(UInt64 handle)
	{
		VMClassRegistry		* registry =	(*g_skyrimVM)->GetClassRegistry();
		IObjectHandlePolicy	* policy =		registry->GetHandlePolicy();

		EventRegistration<D> reg;
		reg.handle = handle;

		Lock();

		for (RegMap::iterator iter = m_data.begin(); iter != m_data.end(); ++iter)
			if (iter->second.erase(reg))
				policy->Release(handle);

		Release();
	}

	template <typename F>
	void ForEach(K& key, F& functor)
	{
		Lock();

		RegMap::iterator handles = m_data.find(key);

		if (handles != m_data.end())
			for (RegSet::iterator iter = handles->second.begin(); iter != handles->second.end(); ++iter)
				functor(*iter);

		Release();
	}

	void Clear(void)
	{
		Lock();

		m_data.clear();

		Release();
	}
};

struct ModCallbackParameters
{
	BSFixedString callbackName;
};

extern RegistrationMapHolder<BSFixedString>							g_menuOpenCloseRegs;
extern RegistrationMapHolder<UInt32>								g_inputEventRegs;
extern RegistrationMapHolder<BSFixedString,ModCallbackParameters>	g_modCallbackRegs;


struct SKSEModCallbackEvent
{
	BSFixedString	eventName;
	BSFixedString	strArg;
	float			numArg;
	TESForm *		sender;

	SKSEModCallbackEvent(BSFixedString a_eventName, BSFixedString a_strArg, float a_numArg, TESForm * a_sender) :
		eventName(a_eventName.data), strArg(a_strArg.data), numArg(a_numArg), sender(a_sender) {}
};

template <>
class BSTEventSink <SKSEModCallbackEvent>
{
public:
	virtual ~BSTEventSink() {}; // todo?
	virtual	EventResult ReceiveEvent(SKSEModCallbackEvent * evn, EventDispatcher<SKSEModCallbackEvent> * dispatcher) = 0;
};

extern EventDispatcher<SKSEModCallbackEvent> g_modCallbackEventDispatcher;


class SKSEEventHandler :
	public BSTEventSink <MenuOpenCloseEvent>,
	public BSTEventSink <InputEvent>,
	public BSTEventSink <SKSEModCallbackEvent>
{

public:
	virtual EventResult		ReceiveEvent(MenuOpenCloseEvent * evn, EventDispatcher<MenuOpenCloseEvent> * dispatcher);
	virtual EventResult		ReceiveEvent(InputEvent ** evns, EventDispatcher<InputEvent,InputEvent*> * dispatcher);
	virtual	EventResult		ReceiveEvent(SKSEModCallbackEvent * evn, EventDispatcher<SKSEModCallbackEvent> * dispatcher);
};

extern SKSEEventHandler	g_skseEventHandler;
