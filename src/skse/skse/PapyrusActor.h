#pragma once

class TESNPC;
class TESCombatStyle;
class BGSOutfit;
class TESClass;
class VMClassRegistry;

namespace papyrusActor
{
	void RegisterFuncs(VMClassRegistry* registry);

	TESCombatStyle* GetCombatStyle(TESNPC* thisNPC);
	void SetCombatStyle(TESNPC* thisNPC, TESCombatStyle* cs);

	BGSOutfit* GetOutfit(TESNPC* thisNPC, bool bSleepOutfit = false);

	TESClass* GetClass(TESNPC* thisNPC);
	void SetClass(TESNPC* thisNPC, TESClass* nuClass);
}
