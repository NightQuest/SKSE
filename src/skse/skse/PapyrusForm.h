#pragma once

#include "skse/GameTypes.h"

class TESForm;
class BGSKeyword;
class VMClassRegistry;

namespace papyrusForm
{
	void RegisterFuncs(VMClassRegistry* registry);

	UInt32 GetType(TESForm* thisForm);
	BSFixedString GetName(TESForm* thisForm);
	void SetName(TESForm* thisForm, BSFixedString nuName);
	float GetWeight(TESForm* thisForm);
	void SetWeight(TESForm* thisForm, float nuWeight);
	UInt32 GetBaseDamage(TESForm* thisForm);
	UInt32 GetValue(TESForm* thisForm);
	void SetGoldValue(TESForm* thisForm, UInt32 value);
	UInt32 GetNumKeywords(TESForm* thisForm);
	BGSKeyword* GetNthKeyword(TESForm* thisForm, UInt32 index);

	void UpdateKeys(UInt8 * data);

	void RegisterForMenu(TESForm * thisForm, BSFixedString menuName);
	void UnregisterFromMenu(TESForm * thisForm, BSFixedString menuName);
	void UnregisterFromAllMenus(TESForm * thisForm);

	void RegisterForModEvent(TESForm * thisForm, BSFixedString eventName, BSFixedString callbackName);
	void UnregisterFromModEvent(TESForm * thisForm, BSFixedString eventName);
	void UnregisterFromAllModEvents(TESForm * thisForm);
	void SendModEvent(TESForm * thisForm, BSFixedString eventName, BSFixedString strArg, float numArg);
}
