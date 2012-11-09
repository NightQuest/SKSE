#include "PapyrusRace.h"

#include "GameObjects.h"
#include "GameFormComponents.h"
#include "GameForms.h"
#include "GameData.h"
#include <vector>

#include "common/ICriticalSection.h"

UInt32 g_invalidatePlayableRaceCache = 0;

namespace papyrusRace
{
	typedef std::vector<TESRace*> PlayableRaceCache;
	static ICriticalSection	s_raceCacheLock;
	static PlayableRaceCache s_raceCache;

	UInt32 GetNumPlayableRaces(StaticFunctionTag * base)
	{
		s_raceCacheLock.Enter();

		if(g_invalidatePlayableRaceCache == 1) {
			s_raceCache.clear();
			g_invalidatePlayableRaceCache = 0;
		}

		if (s_raceCache.empty()) {
			DataHandler* pDataHandler = DataHandler::GetSingleton();
			tArray<TESRace*>& races = pDataHandler->races;
			for (UInt32 n = 0; n < 	races.count; n++) {
				TESRace* pRace = NULL;
				races.GetNthItem(n, pRace);
				if (pRace && IsRaceFlagSet(pRace, TESRace::kRace_Playable)) {
					s_raceCache.push_back(pRace);
				}
			}
		}

		s_raceCacheLock.Leave();
		return s_raceCache.size();
	}

	TESRace * GetNthPlayableRace(StaticFunctionTag * base, UInt32 n)
	{
		if(n < 0) {
			return NULL;
		}

		s_raceCacheLock.Enter();

		if(g_invalidatePlayableRaceCache == 1) {
			s_raceCache.clear();
			g_invalidatePlayableRaceCache = 0;
		}

		if (s_raceCache.empty()) {
			DataHandler* pDataHandler = DataHandler::GetSingleton();
			tArray<TESRace*>& races = pDataHandler->races;
			for (UInt32 n = 0; n < 	races.count; n++) {
				TESRace* pRace = NULL;
				races.GetNthItem(n, pRace);
				if (pRace && IsRaceFlagSet(pRace, TESRace::kRace_Playable)) {
					s_raceCache.push_back(pRace);
				}
			}
		}

		s_raceCacheLock.Leave();
		return (n < s_raceCache.size()) ? s_raceCache.at(n) : NULL;
	}

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
			if((flag & TESRace::kRace_Playable) == TESRace::kRace_Playable)
				g_invalidatePlayableRaceCache = 1;
		}
	}

	void ClearRaceFlag(TESRace* thisRace, UInt32 flag)
	{
		if (thisRace) {
			thisRace->data.raceFlags &= ~flag;
			if((flag & TESRace::kRace_Playable) == TESRace::kRace_Playable)
				g_invalidatePlayableRaceCache = 1;
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

	registry->RegisterFunction(
		new NativeFunction0 <StaticFunctionTag, UInt32>("GetNumPlayableRaces", "Race", papyrusRace::GetNumPlayableRaces, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, TESRace*, UInt32>("GetNthPlayableRace", "Race", papyrusRace::GetNthPlayableRace, registry));
}
