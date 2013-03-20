#include "GameData.h"

DataHandler * DataHandler::GetSingleton()
{
	return *((DataHandler **)0x012E2CB8);
}

class LoadedModFinder
{
	const char * m_stringToFind;

public:
	LoadedModFinder(const char * str) : m_stringToFind(str) { }

	bool Accept(ModInfo* modInfo)
	{
		return _stricmp(modInfo->name, m_stringToFind) == 0;
	}
};

const ModInfo * DataHandler::LookupModByName(const char * modName)
{
	return modList.modInfoList.Find(LoadedModFinder(modName));
}

UInt8 DataHandler::GetModIndex(const char* modName)
{
	return modList.modInfoList.GetIndexOf(LoadedModFinder(modName));
}

void BGSSaveLoadManager::Save(const char * name)
{
	CALL_MEMBER_FN(this, Save_Internal)(name, -1, 0);
}

void BGSSaveLoadManager::Load(const char * name)
{
	CALL_MEMBER_FN(this, Load_Internal)(name, -1, 0, 1);
}

BGSSaveLoadManager * BGSSaveLoadManager::GetSingleton(void)
{
	return *((BGSSaveLoadManager **)0x01B2E3A8);
}

MiscStatManager * MiscStatManager::GetSingleton(void)
{
	return (MiscStatManager *)0x012E6C34;
}

MiscStatManager::MiscStat * MiscStatManager::Get(const char * name)
{
	for(UInt32 i = 0; i < m_numStats; i++)
	{
		MiscStat	* stat = &m_stats[i];

		if(!_stricmp(name, stat->name))
		{
			return stat;
		}
	}

	return NULL;
}

EquipManager * EquipManager::GetSingleton(void)
{
	return *((EquipManager **)0x012E5FAC);
}

const _GetEitherHandSlot GetEitherHandSlot = (_GetEitherHandSlot)0x0054C870;
const _GetRightHandSlot GetRightHandSlot = (_GetRightHandSlot)0x0054C840;
const _GetLeftHandSlot GetLeftHandSlot = (_GetLeftHandSlot)0x0054C810;

const _LookupActorValueByName LookupActorValueByName = (_LookupActorValueByName)0x005AD5F0;

ActorValueList * ActorValueList::GetSingleton(void)
{
	return *((ActorValueList **)0x012E2BDC);
}

ActorValueInfo * ActorValueList::GetActorValue(UInt32 id)
{
	return (id < kNumActorValues) ? actorValues[id] : NULL;
}

const _ChangeActorHeadPart ChangeActorHeadPart = (_ChangeActorHeadPart)0x005AA4E0; // Changes one HeadPart to another
const _UpdatePlayerTints UpdatePlayerTints = (_UpdatePlayerTints)0x0087EE70; // Regenerates dynamic tints

FaceGen * FaceGen::GetSingleton(void)
{
	return *((FaceGen **)0x012E3538);
}

const _GetActorBaseOverlays GetActorBaseOverlays = (_GetActorBaseOverlays)0x00568280;
const _GetNumActorBaseOverlays GetNumActorBaseOverlays = (_GetNumActorBaseOverlays)0x005682F0;
