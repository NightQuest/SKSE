#pragma once

class TESNPC;
class TESCombatStyle;
class BGSOutfit;
class TESClass;

namespace papyrusActor
{
	TESCombatStyle* GetCombatStyle(TESNPC* thisNPC);
	void SetCombatStyle(TESNPC* thisNPC, TESCombatStyle* cs);

	BGSOutfit* GetDefaultOutfit(TESNPC* thisNPC);
	void SetDefaultOutfit(TESNPC* thisNPC, BGSOutfit* outfit);
	BGSOutfit* GetSleepOutfit(TESNPC* thisNPC);
	void SetSleepOutfit(TESNPC* thisNPC, BGSOutfit* outfit);

	TESClass* GetClass(TESNPC* thisNPC);
	void SetClass(TESNPC* thisNPC, TESClass* nuClass);
}
