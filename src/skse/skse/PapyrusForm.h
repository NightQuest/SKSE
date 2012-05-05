#pragma once

class TESForm;
class BGSKeyword;

namespace papyrusForm
{
	UInt32 GetType(TESForm* thisForm);
	const char* GetName(TESForm* thisForm);
	void SetName(TESForm* thisForm, const char* nuName);
	float GetWeight(TESForm* thisForm);
	void SetWeight(TESForm* thisForm, float nuWeight);
	UInt16 GetBaseDamage(TESForm* thisForm);
	UInt32 GetValue(TESForm* thisForm);
	void SetValue(TESForm* thisForm, UInt32 value);
	UInt32 GetNumKeywords(TESForm* thisForm);
	BGSKeyword* GetNthKeyword(TESForm* thisForm, UInt32 index);
}
