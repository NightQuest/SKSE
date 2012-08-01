#include "PapyrusGame.h"

#include "GameAPI.h"
#include "GameReferences.h"
#include "GameData.h"

namespace papyrusGame
{
	UInt32 GetPerkPoints(StaticFunctionTag*)
	{
		PlayerCharacter* pPC = (*g_thePlayer);
		return pPC->numPerkPoints;
	}

	void SetPerkPoints(StaticFunctionTag*, UInt32 points)
	{
		if(points > 255) // Not sure if signed or unsigned but this was only a byte in size
			points = 255;

		PlayerCharacter* pPC = (*g_thePlayer);
		pPC->numPerkPoints = points;
	}

	void ModPerkPoints(StaticFunctionTag*, SInt32 points)
	{
		PlayerCharacter* pPC = (*g_thePlayer);
		SInt32 nuPerkPoints = pPC->numPerkPoints + points;
		if (nuPerkPoints < 0)
			nuPerkPoints = 0;
		else if (nuPerkPoints > 255)
			nuPerkPoints = 255;

		pPC->numPerkPoints = nuPerkPoints;
	}

	UInt32 GetModCount(StaticFunctionTag*)
	{
		DataHandler* pDataHandler = DataHandler::GetSingleton();
		return pDataHandler->modList.loadedModCount;
	}

	UInt32 GetModByName(StaticFunctionTag*, BSFixedString name)
	{
		DataHandler* pDataHandler = DataHandler::GetSingleton();
		return pDataHandler->GetModIndex(name.data);
	}

	BSFixedString GetModName(StaticFunctionTag*, UInt32 index)
	{
		if(index < 0 || index > 255)
			return NULL;
		DataHandler* pDataHandler = DataHandler::GetSingleton();
		ModInfo* modInfo = pDataHandler->modList.modInfoList.GetNthItem(index);
		return (modInfo) ? modInfo->name : NULL;
	}

	BSFixedString GetModAuthor(StaticFunctionTag*, UInt32 index)
	{
		if(index < 0 || index > 255)
			return NULL;
		DataHandler* pDataHandler = DataHandler::GetSingleton();
		ModInfo* modInfo = pDataHandler->modList.modInfoList.GetNthItem(index);
		return (modInfo) ? modInfo->author.Get() : NULL;
	}

	BSFixedString GetModDescription(StaticFunctionTag*, UInt32 index)
	{
		if(index < 0 || index > 255)
			return NULL;
		DataHandler* pDataHandler = DataHandler::GetSingleton();
		ModInfo* modInfo = pDataHandler->modList.modInfoList.GetNthItem(index);
		return (modInfo) ? modInfo->description.Get() : NULL;
	}

	UInt32 GetModDependencyCount(StaticFunctionTag*, UInt32 index)
	{
		if(index < 0 || index > 255)
			return NULL;
		DataHandler* pDataHandler = DataHandler::GetSingleton();
		ModInfo* modInfo = pDataHandler->modList.modInfoList.GetNthItem(index);
		return (modInfo) ? modInfo->numRefMods : 0;
	}

	UInt32 GetNthModDependency(StaticFunctionTag*, UInt32 index, UInt32 dep_index)
	{
		if(index < 0 || index > 255)
			return NULL;
		DataHandler* pDataHandler = DataHandler::GetSingleton();
		ModInfo* modInfo = pDataHandler->modList.modInfoList.GetNthItem(index);
		return (modInfo && dep_index > 0 && dep_index < modInfo->numRefMods) ? modInfo->refModInfo[dep_index]->modIndex : 0;
	}

}

#include "PapyrusVM.h"
#include "PapyrusNativeFunctions.h"

void papyrusGame::RegisterFuncs(VMClassRegistry* registry)
{
	// Perk Points
	registry->RegisterFunction(
		new NativeFunction0 <StaticFunctionTag, UInt32>("GetPerkPoints", "Game", papyrusGame::GetPerkPoints, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, UInt32>("SetPerkPoints", "Game", papyrusGame::SetPerkPoints, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, SInt32>("ModPerkPoints", "Game", papyrusGame::ModPerkPoints, registry));

	// Mods
	registry->RegisterFunction(
		new NativeFunction0 <StaticFunctionTag, UInt32>("GetModCount", "Game", papyrusGame::GetModCount, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, UInt32, BSFixedString>("GetModByName", "Game", papyrusGame::GetModByName, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, BSFixedString, UInt32>("GetModName", "Game", papyrusGame::GetModName, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, BSFixedString, UInt32>("GetModAuthor", "Game", papyrusGame::GetModAuthor, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, BSFixedString, UInt32>("GetModDescription", "Game", papyrusGame::GetModDescription, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, UInt32, UInt32>("GetModDependencyCount", "Game", papyrusGame::GetModDependencyCount, registry));

	registry->RegisterFunction(
		new NativeFunction2 <StaticFunctionTag, UInt32, UInt32, UInt32>("GetNthModDependency", "Game", papyrusGame::GetNthModDependency, registry));

}
