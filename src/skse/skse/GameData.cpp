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
