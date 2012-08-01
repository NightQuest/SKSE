#pragma once

class TESRace;
class SpellItem;
class VMClassRegistry;

namespace papyrusRace
{
	void RegisterFuncs(VMClassRegistry* registry);

	UInt32 GetSpellCount(TESRace* thisRace);
	SpellItem* GetNthSpell(TESRace* thisRace, UInt32 n);
	
	bool IsRaceFlagSet(TESRace* thisRace, UInt32 flag);
	void SetRaceFlag(TESRace* thisRace, UInt32 flag);
	void ClearRaceFlag(TESRace* thisRace, UInt32 flag);
}