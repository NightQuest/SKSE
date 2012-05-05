#pragma once

class TESForm;
class TESNPC;
class TESCombatStyle;
class BGSOutfit;
class TESClass;
class Actor;
class VMClassRegistry;

namespace papyrusActor
{
	void RegisterFuncs(VMClassRegistry* registry);

	TESCombatStyle* GetCombatStyle(Actor* thisActor);
	void SetCombatStyle(Actor* thisActor, TESCombatStyle* cs);

	BGSOutfit* GetOutfit(Actor* thisActor, bool bSleepOutfit = false);

	TESClass* GetClass(Actor* thisActor);
	void SetClass(Actor* thisActor, TESClass* nuClass);

	TESForm* GetWornForm(Actor* thisActor, UInt32 slot);
}
