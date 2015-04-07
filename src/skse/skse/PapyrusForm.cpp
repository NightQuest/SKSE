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
		if(!thisForm)
			return;
		g_inputKeyEventRegs.Register<TESForm>(key, thisForm->GetFormType(), thisForm);
	}

	void UnregisterForKey(TESForm * thisForm, UInt32 key)
	{
		if(!thisForm)
			return;
		g_inputKeyEventRegs.Unregister<TESForm>(key, thisForm->GetFormType(), thisForm);
	}

	void UnregisterForAllKeys(TESForm * thisForm)
	{
		if(!thisForm)
			return;
		g_inputKeyEventRegs.UnregisterAll<TESForm>(thisForm->GetFormType(), thisForm);
	}

	void RegisterForControl(TESForm * thisForm, BSFixedString control)
	{
		if(!thisForm)
			return;
		g_inputControlEventRegs.Register<TESForm>(control, thisForm->GetFormType(), thisForm);
	}

	void UnregisterForControl(TESForm * thisForm, BSFixedString control)
	{
		if(!thisForm)
			return;
		g_inputControlEventRegs.Unregister<TESForm>(control, thisForm->GetFormType(), thisForm);
	}

	void UnregisterForAllControls(TESForm * thisForm)
	{
		if(!thisForm)
			return;
		g_inputControlEventRegs.UnregisterAll<TESForm>(thisForm->GetFormType(), thisForm);
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
		if(!thisForm || !menuName.data)
			return;
		
		g_menuOpenCloseRegs.Register<TESForm>(menuName, thisForm->GetFormType(), thisForm);
	}

	void UnregisterForMenu(TESForm * thisForm, BSFixedString menuName)
	{
		if(!thisForm || !menuName.data)
			return;

		g_menuOpenCloseRegs.Unregister<TESForm>(menuName, thisForm->GetFormType(), thisForm);
	}

	void UnregisterForAllMenus(TESForm * thisForm)
	{
		if(!thisForm)
			return;

		g_menuOpenCloseRegs.UnregisterAll<TESForm>(thisForm->GetFormType(), thisForm);
	}

	void RegisterForModEvent(TESForm * thisForm, BSFixedString eventName, BSFixedString callbackName)
	{
		if(!thisForm || !eventName.data || !callbackName.data)
			return;

		ModCallbackParameters params;
		params.callbackName = callbackName;

		g_modCallbackRegs.Register<TESForm>(eventName, thisForm->GetFormType(), thisForm, &params);
	}

	void UnregisterForModEvent(TESForm * thisForm, BSFixedString eventName)
	{
		if(!thisForm || !eventName.data)
			return;

		g_modCallbackRegs.Unregister<TESForm>(eventName, thisForm->GetFormType(), thisForm);
	}

	void UnregisterForAllModEvents(TESForm * thisForm)
	{
		g_modCallbackRegs.UnregisterAll<TESForm>(thisForm->GetFormType(), thisForm);
	}

	void SendModEvent(TESForm * thisForm, BSFixedString eventName, BSFixedString strArg, float numArg)
	{
		if (!eventName.data)
			return;

		SKSEModCallbackEvent evn(eventName, strArg, numArg, thisForm);
		g_modCallbackEventDispatcher.SendEvent(&evn);
	}

	void RegisterForCameraState(TESForm * thisForm)
	{
		if(!thisForm)
			return;

		g_cameraEventRegs.Register<TESForm>(thisForm->GetFormType(), thisForm);
	}

	void UnregisterForCameraState(TESForm * thisForm)
	{
		if(!thisForm)
			return;

		g_cameraEventRegs.Unregister<TESForm>(thisForm->GetFormType(), thisForm);
	}

	void RegisterForCrosshairRef(TESForm * thisForm)
	{
		if(!thisForm)
			return;

		g_crosshairRefEventRegs.Register<TESForm>(thisForm->GetFormType(), thisForm);
	}

	void UnregisterForCrosshairRef(TESForm * thisForm)
	{
		if(!thisForm)
			return;

		g_crosshairRefEventRegs.Unregister<TESForm>(thisForm->GetFormType(), thisForm);
	}

	TESForm * TempClone(TESForm * thisForm)
	{
		TESForm	* result = NULL;

		if(thisForm)
		{
			IFormFactory	* factory = IFormFactory::GetFactoryForType(thisForm->formType);
			if(factory)
			{
				result = factory->Create();
				if(result)
				{
					result->Init();
					result->CopyFrom(thisForm);
				}
				else
				{
					_ERROR("Form::TempClone: factory for type %02X failed", thisForm->formType);
				}
			}
			else
			{
				_MESSAGE("Form::TempClone: tried to clone form %08X (type %02X), no factory found", thisForm->formID, thisForm->formType);
			}
		}

		return result;
	}
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
		new NativeFunction1 <TESForm, void, UInt32> ("UnregisterForKey", "Form", papyrusForm::UnregisterForKey, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESForm, void> ("UnregisterForAllKeys", "Form", papyrusForm::UnregisterForAllKeys, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESForm, void, BSFixedString> ("RegisterForMenu", "Form", papyrusForm::RegisterForMenu, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESForm, void, BSFixedString> ("UnregisterForMenu", "Form", papyrusForm::UnregisterForMenu, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESForm, void> ("UnregisterForAllMenus", "Form", papyrusForm::UnregisterForAllMenus, registry));

	registry->RegisterFunction(
		new NativeFunction2 <TESForm, void, BSFixedString, BSFixedString> ("RegisterForModEvent", "Form", papyrusForm::RegisterForModEvent, registry));

	registry->RegisterFunction(
		new NativeFunction3 <TESForm, void, BSFixedString, BSFixedString, float> ("SendModEvent", "Form", papyrusForm::SendModEvent, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESForm, void, BSFixedString> ("UnregisterForModEvent", "Form", papyrusForm::UnregisterForModEvent, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESForm, void> ("UnregisterForAllModEvents", "Form", papyrusForm::UnregisterForAllModEvents, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESForm, TESForm *> ("TempClone", "Form", papyrusForm::TempClone, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESForm, void, BSFixedString> ("RegisterForControl", "Form", papyrusForm::RegisterForControl, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESForm, void, BSFixedString> ("UnregisterForControl", "Form", papyrusForm::UnregisterForControl, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESForm, void> ("UnregisterForAllControls", "Form", papyrusForm::UnregisterForAllControls, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESForm, void> ("RegisterForCameraState", "Form", papyrusForm::RegisterForCameraState, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESForm, void> ("UnregisterForCameraState", "Form", papyrusForm::UnregisterForCameraState, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESForm, void> ("RegisterForCrosshairRef", "Form", papyrusForm::RegisterForCrosshairRef, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESForm, void> ("UnregisterForCrosshairRef", "Form", papyrusForm::UnregisterForCrosshairRef, registry));

	registry->SetFunctionFlags("Form", "RegisterForKey", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Form", "UnregisterForKey", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Form", "UnregisterForAllKeys", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Form", "RegisterForMenu", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Form", "UnregisterForMenu", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Form", "UnregisterForAllMenus", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Form", "RegisterForModEvent", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Form", "SendModEvent", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Form", "UnregisterForAllModEvents", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Form", "RegisterForControl", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Form", "UnregisterForControl", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Form", "UnregisterForAllControls", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Form", "RegisterForCameraState", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Form", "UnregisterForCameraState", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Form", "RegisterForCrosshairRef", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Form", "UnregisterForCrosshairRef", VMClassRegistry::kFunctionFlag_NoWait);
}
