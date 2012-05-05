#include "PapyrusActor.h"

#include "GameForms.h"
#include "GameObjects.h"

namespace papyrusActor
{
	TESCombatStyle* GetCombatStyle(TESNPC* thisNPC)
	{
		if (!thisNPC)
			return NULL;
		return thisNPC->combatStyle;
	}

	void SetCombatStyle(TESNPC* thisNPC, TESCombatStyle* cs)
	{
		if (thisNPC && cs) {
			thisNPC->combatStyle = cs;
		}
	}

	BGSOutfit* GetOutfit(TESNPC* thisNPC, bool bSleepOutfit)
	{
		if (!thisNPC)
			return NULL;
		return (bSleepOutfit) ? thisNPC->sleepOutfit : thisNPC->defaultOutfit;
	}

	TESClass* GetClass(TESNPC* thisNPC)
	{
		if (!thisNPC)
			return NULL;
		return thisNPC->npcClass;
	}

	void SetClass(TESNPC* thisNPC, TESClass* nuClass)
	{
		if (thisNPC && nuClass) {
			thisNPC->npcClass = nuClass;
		}
	}


}

#include "PapyrusVM.h"
#include "PapyrusNativeFunctions.h"

void papyrusActor::RegisterFuncs(VMClassRegistry* registry)
{
	registry->RegisterFunction(
		new NativeFunction0 <TESNPC, TESCombatStyle*>("GetCombatStyle", "Actor", papyrusActor::GetCombatStyle, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESNPC, void, TESCombatStyle*>("SetCombatStyle", "Actor", papyrusActor::SetCombatStyle, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESNPC, BGSOutfit*, bool>("GetOutfit", "Actor", papyrusActor::GetOutfit, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESNPC, TESClass*>("Getclass", "Actor", papyrusActor::GetClass, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESNPC, void, TESClass*>("SetClass", "Actor", papyrusActor::SetClass, registry));

}