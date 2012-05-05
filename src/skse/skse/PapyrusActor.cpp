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

	BGSOutfit* GetDefaultOutfit(TESNPC* thisNPC)
	{
		if (!thisNPC)
			return NULL;
		return thisNPC->defaultOutfit;
	}

	void SetDefaultOutfit(TESNPC* thisNPC, BGSOutfit* outfit)
	{
		if (thisNPC && outfit) {
			thisNPC->defaultOutfit = outfit;
		}
	}

	BGSOutfit* GetSleepOutfit(TESNPC* thisNPC)
	{
		if (!thisNPC)
			return NULL;
		return thisNPC->sleepOutfit;
	}

	void SetSleepOutfit(TESNPC* thisNPC, BGSOutfit* outfit)
	{
		if (thisNPC && outfit) {
			thisNPC->sleepOutfit = outfit;
		}
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
