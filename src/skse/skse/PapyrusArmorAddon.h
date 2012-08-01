#pragma once

#include "GameTypes.h"
class TESObjectARMA;
class VMClassRegistry;
class TESRace;
class BGSTextureSet;

namespace papyrusArmorAddon
{
	void RegisterFuncs(VMClassRegistry* registry);

	BSFixedString GetModelPath(TESObjectARMA* thisArmorAddon, bool bFirst, bool bFemale);
	void SetModelPath(TESObjectARMA* thisArmorAddon, BSFixedString nuPath, bool bFirst, bool bFemale);

	UInt32 GetModelNumTextureSets(TESObjectARMA* thisArmorAddon, bool bFirst, bool bFemale);
	BGSTextureSet* GetModelNthTextureSet(TESObjectARMA* thisArmorAddon, UInt32 n, bool bFirst, bool bFemale);

	UInt32 GetNumAdditionalRaces(TESObjectARMA* thisArmorAddon);
	TESRace* GetNthAdditionalRace(TESObjectARMA* thisArmorAddon, UInt32 n);
}
