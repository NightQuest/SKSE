#include "PapyrusForm.h"

#include "GameForms.h"
#include "GameRTTI.h"
#include "PapyrusVM.h"
#include "PapyrusEvents.h"
#include "GameMenus.h"


namespace papyrusForm
{
	UInt32 GetType(TESForm* thisForm)
	{
		return (thisForm) ? thisForm->GetFormType() : 0;
	}

	BSFixedString GetName(TESForm* thisForm)
	{
		if (!thisForm)
			return NULL;
		
		TESFullName* pFullName = DYNAMIC_CAST(thisForm, TESForm, TESFullName);
		if (pFullName)
			return pFullName->name.data;
		return NULL;
	}

	void SetName(TESForm* thisForm, BSFixedString nuName)
	{
		TESFullName* pFullName = DYNAMIC_CAST(thisForm, TESForm, TESFullName);
		// is a const string, so have to just reassign it.
		if (pFullName) {
			pFullName->name = nuName;
		}
	}

	float GetWeight(TESForm* thisForm)
	{
		if (!thisForm)
			return 0.0;

		TESWeightForm* pWeight = DYNAMIC_CAST(thisForm, TESForm, TESWeightForm);
		if (pWeight)
			return pWeight->weight;
		return 0.0;
	}

	void SetWeight(TESForm* thisForm, float nuWeight)
	{
		if (!thisForm)
			return;

		TESWeightForm* pWeight = DYNAMIC_CAST(thisForm, TESForm, TESWeightForm);
		if (pWeight)
			pWeight->weight = nuWeight;
	}

	UInt32 GetBaseDamage(TESForm* thisForm)
	{
		if (!thisForm)
			return 0;
		TESAttackDamageForm* pAttack = DYNAMIC_CAST(thisForm, TESForm, TESAttackDamageForm);
		if (pAttack)
			return pAttack->GetAttackDamage();
		return 0;
	}

	UInt32 GetValue(TESForm* thisForm)
	{
		if (!thisForm)
			return 0;
		TESValueForm* pValue = DYNAMIC_CAST(thisForm, TESForm, TESValueForm);
		if (pValue)
			return pValue->value;
		return 0;
	}

	void SetGoldValue(TESForm* thisForm, UInt32 value)
	{
		if (!thisForm)
			return;
		TESValueForm* pValue = DYNAMIC_CAST(thisForm, TESForm, TESValueForm);
		if (pValue)
			pValue->value = value;		
	}

	UInt32 GetNumKeywords(TESForm* thisForm)
	{
		if (!thisForm)
			return 0;
		BGSKeywordForm* pKeywords = DYNAMIC_CAST(thisForm, TESForm, BGSKeywordForm);
		if (pKeywords)
			return pKeywords->numKeywords;
		return 0;
	}

	BGSKeyword* GetNthKeyword(TESForm* thisForm, UInt32 index)
	{
		if (!thisForm)
			return NULL;
		BGSKeywordForm* pKeywords = DYNAMIC_CAST(thisForm, TESForm, BGSKeywordForm);
		if (pKeywords && index < pKeywords->numKeywords) {
			return pKeywords->keywords[index];
		}
		return NULL;
	}

	void RegisterForKey(TESForm * thisForm, UInt32 key)
	{
		g_inputEventRegs.Register(thisForm, key);
	}

	void UnregisterFromKey(TESForm * thisForm, UInt32 key)
	{
		g_inputEventRegs.Unregister(thisForm, key);
	}

	void UnregisterFromAllKeys(TESForm * thisForm)
	{
		g_inputEventRegs.UnregisterFromAll(thisForm);
	}

	void UpdateKeys(UInt8 * data)
	{
		/*static UInt8	oldState[0x100] = { 0 };

		if(!*g_skyrimVM) return;

		// ### this is off because it's a super temp hack

		BSFixedString		eventName("OnKeyDown");
		VMClassRegistry		* registry =	(*g_skyrimVM)->GetClassRegistry();

		for(UInt32 i = 0; i < 0x100; i++)
		{
			if(!oldState[i] && data[i])
			{
				RegisteredKeyMap::iterator	registeredHandles = g_regKeyMap.find(i);
				if(registeredHandles != g_regKeyMap.end())
				{
					for(HandleList::iterator iter = registeredHandles->second.begin(); iter != registeredHandles->second.end(); ++iter)
					{
						OneIntArg	args(i);

						registry->QueueEvent(*iter, &eventName, &args);
					}
				}
			}

			oldState[i] = data[i];
		}*/
	}

	void RegisterForMenu(TESForm * thisForm, BSFixedString menuName)
	{
		if (!menuName.data)
			return;
		
		g_menuOpenCloseRegs.Register(thisForm, menuName);
	}

	void UnregisterFromMenu(TESForm * thisForm, BSFixedString menuName)
	{
		if (!menuName.data)
			return;

		g_menuOpenCloseRegs.Unregister(thisForm, menuName);
	}

	void UnregisterFromAllMenus(TESForm * thisForm)
	{
		g_menuOpenCloseRegs.UnregisterFromAll(thisForm);
	}

	void RegisterForModEvent(TESForm * thisForm, BSFixedString eventName, BSFixedString callbackName)
	{
		if (!eventName.data || !callbackName.data)
			return;

		ModCallbackParameters params;
		params.callbackName = callbackName;

		g_modCallbackRegs.Register(thisForm, eventName, &params);
	}

	void UnregisterFromModEvent(TESForm * thisForm, BSFixedString eventName)
	{
		if (!eventName.data)
			return;

		g_modCallbackRegs.Unregister(thisForm, eventName);
	}

	void UnregisterFromAllModEvents(TESForm * thisForm)
	{
		g_modCallbackRegs.UnregisterFromAll(thisForm);
	}

	void SendModEvent(TESForm * thisForm, BSFixedString eventName, BSFixedString strArg, float numArg)
	{
		if (!eventName.data)
			return;

		SKSEModCallbackEvent evn(eventName, strArg, numArg, thisForm);
		g_modCallbackEventDispatcher.SendEvent(&evn);
	}
}

void papyrusForm::RegisterEventSinks(void)
{
	MenuManager * mm = MenuManager::GetSingleton();
	if (mm)
		mm->MenuOpenCloseEventDispatcher()->AddEventSink(&g_skseEventHandler);

	g_modCallbackEventDispatcher.AddEventSink(&g_skseEventHandler);

	// Has to be done later, because the pointer is not set yet.
	//(*g_inputEventDispatcher)->AddEventSink(&g_skseEventHandler);
}

#include "PapyrusVM.h"
#include "PapyrusNativeFunctions.h"

void papyrusForm::RegisterFuncs(VMClassRegistry* registry)
{
	registry->RegisterFunction(
		new NativeFunction0 <TESForm, UInt32> ("GetType", "Form", papyrusForm::GetType, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESForm, BSFixedString> ("GetName", "Form", papyrusForm::GetName, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESForm, void, BSFixedString> ("SetName", "Form", papyrusForm::SetName, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESForm, float> ("GetWeight", "Form", papyrusForm::GetWeight, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESForm, void, float> ("SetWeight", "Form", papyrusForm::SetWeight, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESForm, void, UInt32> ("SetGoldValue", "Form", papyrusForm::SetGoldValue, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESForm, UInt32> ("GetNumKeywords", "Form", papyrusForm::GetNumKeywords, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESForm, BGSKeyword *, UInt32> ("GetNthKeyword", "Form", papyrusForm::GetNthKeyword, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESForm, void, UInt32> ("RegisterForKey", "Form", papyrusForm::RegisterForKey, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESForm, void, UInt32> ("UnregisterFromKey", "Form", papyrusForm::UnregisterFromKey, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESForm, void> ("UnregisterFromAllKeys", "Form", papyrusForm::UnregisterFromAllKeys, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESForm, void, BSFixedString> ("RegisterForMenu", "Form", papyrusForm::RegisterForMenu, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESForm, void, BSFixedString> ("UnregisterFromMenu", "Form", papyrusForm::UnregisterFromMenu, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESForm, void> ("UnregisterFromAllMenus", "Form", papyrusForm::UnregisterFromAllMenus, registry));

	registry->RegisterFunction(
		new NativeFunction2 <TESForm, void, BSFixedString, BSFixedString> ("RegisterForModEvent", "Form", papyrusForm::RegisterForModEvent, registry));

	registry->RegisterFunction(
		new NativeFunction3 <TESForm, void, BSFixedString, BSFixedString, float> ("SendModEvent", "Form", papyrusForm::SendModEvent, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESForm, void, BSFixedString> ("UnregisterFromModEvent", "Form", papyrusForm::UnregisterFromModEvent, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESForm, void> ("UnregisterFromAllModEvents", "Form", papyrusForm::UnregisterFromAllModEvents, registry));
}
