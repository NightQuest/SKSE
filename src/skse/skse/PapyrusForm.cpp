#include "PapyrusForm.h"

#include "GameForms.h"
#include "GameRTTI.h"

namespace papyrusForm
{
	UInt32 GetType(TESForm* thisForm)
	{
		return (thisForm) ? thisForm->GetFormType() : 0;
	}

	const char* GetName(TESForm* thisForm)
	{
		if (!thisForm)
			return NULL;
		
		const char* pName = thisForm->GetName();

		TESFullName* pFullName = DYNAMIC_CAST(thisForm, TESForm, TESFullName);
		if (pFullName)
			return pFullName->name.data;
		return NULL;
	}

	void SetName(TESForm* thisForm, const char* nuName)
	{
		if (thisForm)
			thisForm->SetName(nuName);
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

}

#include "PapyrusVM.h"
#include "PapyrusNativeFunctions.h"

void papyrusForm::RegisterFuncs(VMClassRegistry* registry)
{
	registry->RegisterFunction(
		new NativeFunction0 <TESForm, UInt32> ("GetType", "Form", papyrusForm::GetType, registry));

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
}
