#pragma once

class TESForm;
class TESNPC;
class TESCombatStyle;
class BGSOutfit;
class TESClass;
class SpellItem;
class VMClassRegistry;

namespace papyrusActorBase {
	void RegisterFuncs(VMClassRegistry* registry);

	TESCombatStyle* GetCombatStyle(TESNPC* thisNPC);
	void SetCombatStyle(TESNPC* thisNPC, TESCombatStyle* cs);

	BGSOutfit* GetOutfit(TESNPC* thisNPC, bool bSleepOutfit = false);

	void SetClass(TESNPC* thisNPC, TESClass* nuClass);

	float GetWeight(TESNPC* thisNPC);
	void SetWeight(TESNPC* thisNPC, float weight);
	UInt32 GetNumHeadParts(TESNPC* thisNPC);
	TESForm* GetNthHeadPart(TESNPC* thisNPC, UInt32 n);
	void SetNthHeadPart(TESNPC* thisNPC, TESForm* form, UInt32 n );
	float GetFaceMorph(TESNPC* thisNPC, UInt32 index);
	void SetFaceMorph(TESNPC* thisNPC, float value, UInt32 index);
	UInt32 GetSpellCount(TESNPC* thisNPC);
	SpellItem* GetNthSpell(TESNPC* thisNPC, UInt32 n);
};
