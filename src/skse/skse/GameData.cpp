#include "GameData.h"

DataHandler * DataHandler::GetSingleton()
{
	return *((DataHandler **)0x012E1EB8);
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
	return *((BGSSaveLoadManager **)0x01B2D698);
}

MiscStatManager * MiscStatManager::GetSingleton(void)
{
	return (MiscStatManager *)0x012E5E34;
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
	return *((EquipManager **)0x012E51AC);
}

const _GetEitherHandSlot GetEitherHandSlot = (_GetEitherHandSlot)0x0054BD70;
const _GetRightHandSlot GetRightHandSlot = (_GetRightHandSlot)0x0054BD40;
const _GetLeftHandSlot GetLeftHandSlot = (_GetLeftHandSlot)0x0049D0D0;


const _LookupActorValueByName LookupActorValueByName = (_LookupActorValueByName)0x005AD770;

ActorValueList * ActorValueList::GetSingleton(void)
{
	return *((ActorValueList **)0x012E1DDC);
}

ActorValueInfo * ActorValueList::GetActorValue(UInt32 id)
{
	return (id < kNumActorValues) ? actorValues[id] : NULL;
}


const _ChangeActorHeadPart ChangeActorHeadPart = (_ChangeActorHeadPart)0x005AA6C0; // Changes one HeadPart to another
const _UpdatePlayerTints UpdatePlayerTints = (_UpdatePlayerTints)0x0087F190; // Regenerates dynamic tints

FaceGen * FaceGen::GetSingleton(void)
{
	return *((FaceGen **)0x012E2738);
}

const _GetActorBaseOverlays GetActorBaseOverlays = (_GetActorBaseOverlays)0x005679D0;
const _GetNumActorBaseOverlays GetNumActorBaseOverlays = (_GetNumActorBaseOverlays)0x00567A40;