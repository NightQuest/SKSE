#include "PapyrusForm.h"

#include "GameForms.h"
#include "GameRTTI.h"
#include "PapyrusVM.h"

#include <map>
#include <set>

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
		
		const char* pName = thisForm->GetName();

		TESFullName* pFullName = DYNAMIC_CAST(thisForm, TESForm, TESFullName);
		if (pFullName)
			return pFullName->name.data;
		return NULL;
	}

	void SetName(TESForm* thisForm, BSFixedString nuName)
	{
		if (thisForm)
			thisForm->SetName(nuName.data);
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

	typedef std::set <UInt64>				HandleList;
	typedef std::map <UInt32, HandleList>	RegisteredKeyMap;

	// ### TODO: clear this on unload
	RegisteredKeyMap	g_regKeyMap;

	void RegisterForKey(TESForm * thisForm, UInt32 key)
	{
		VMClassRegistry		* registry =	(*g_skyrimVM)->GetClassRegistry();
		IObjectHandlePolicy	* policy =		registry->GetHandlePolicy();

		UInt64	handle = policy->Create(thisForm->formType, (void *)thisForm);

		g_regKeyMap[key].insert(handle);
	}

	class OneIntArg : public IFunctionArguments
	{
	public:
		OneIntArg(UInt32 _data) :data(_data) { }

		virtual bool	Copy(Output * dst)
		{
			dst->Resize(1);
			dst->Get(0)->SetInt(data);

			return true;
		}

	private:
		UInt32	data;
	};

	void UpdateKeys(UInt8 * data)
	{
		static UInt8	oldState[0x100] = { 0 };

		if(!*g_skyrimVM) return;

		// ### this is off because it's a super temp hack
#if 0
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
		}
#endif
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
}
