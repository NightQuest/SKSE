#include "PapyrusRace.h"

#include "GameObjects.h"
#include "GameFormComponents.h"
#include "GameForms.h"


namespace papyrusRace
{
	UInt32 GetSpellCount(TESRace* thisRace)
	{
		return (thisRace)? thisRace->spellList.GetSpellCount() : 0;
	}

	SpellItem* GetNthSpell(TESRace* thisRace, UInt32 n)
	{
		return (thisRace) ? thisRace->spellList.GetNthSpell(n) : NULL;
	}

	bool IsRaceFlagSet(TESRace* thisRace, UInt32 flag)
	{
		return (thisRace) ? (thisRace->data.raceFlags & flag) == flag : false;
	}

	void SetRaceFlag(TESRace* thisRace, UInt32 flag)
	{
		if (thisRace) {
			thisRace->data.raceFlags |= flag;
		}
	}

	void ClearRaceFlag(TESRace* thisRace, UInt32 flag)
	{
		if (thisRace) {
			thisRace->data.raceFlags &= ~flag;
		}
	}

}

#include "PapyrusVM.h"
#include "PapyrusNativeFunctions.h"

void papyrusRace::RegisterFuncs(VMClassRegistry* registry)
{

	registry->RegisterFunction(
		new NativeFunction0 <TESRace, UInt32>("GetSpellCount", "Race", papyrusRace::GetSpellCount, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESRace, SpellItem*, UInt32>("GetNthSpell", "Race", papyrusRace::GetNthSpell, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESRace, bool, UInt32>("IsRaceFlagSet", "Race", papyrusRace::IsRaceFlagSet, registry));
	
	registry->RegisterFunction(
		new NativeFunction1 <TESRace, void, UInt32>("SetRaceFlag", "Race", papyrusRace::SetRaceFlag, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESRace, void, UInt32>("ClearRaceFlag", "Race", papyrusRace::ClearRaceFlag, registry));

}
