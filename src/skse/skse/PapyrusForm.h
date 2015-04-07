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
	void UnregisterForMenu(TESForm * thisForm, BSFixedString menuName);
	void UnregisterForAllMenus(TESForm * thisForm);

	void RegisterForModEvent(TESForm * thisForm, BSFixedString eventName, BSFixedString callbackName);
	void UnregisterForModEvent(TESForm * thisForm, BSFixedString eventName);
	void UnregisterForAllModEvents(TESForm * thisForm);
	void SendModEvent(TESForm * thisForm, BSFixedString eventName, BSFixedString strArg, float numArg);

	void RegisterForKey(TESForm * thisForm, UInt32 key);
	void UnregisterForKey(TESForm * thisForm, UInt32 key);
	void UnregisterForAllKeys(TESForm * thisForm);

	void RegisterForControl(TESForm * thisForm, BSFixedString control);
	void UnregisterForControl(TESForm * thisForm, UInt32 control);
	void UnregisterForAllControls(TESForm * thisForm);

	void RegisterForCameraState(TESForm * thisForm);
	void UnregisterForCameraState(TESForm * thisForm);

	void RegisterForCrosshairRef(TESForm * thisForm);
	void UnregisterForCrosshairRef(TESForm * thisForm);
}
