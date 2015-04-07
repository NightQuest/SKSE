#include "PapyrusGame.h"
#include "PapyrusColorForm.h"

#include "GameRTTI.h"
#include "GameAPI.h"
#include "GameReferences.h"
#include "GameData.h"
#include "GameSettings.h"
#include "GameForms.h"
#include "GameCamera.h"
#include "GameMenus.h"
#include "GameThreads.h"

#include "NiNodes.h"
#include "Colors.h"

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
		if(index > 255)
			return NULL;
		DataHandler* pDataHandler = DataHandler::GetSingleton();
		ModInfo* modInfo = pDataHandler->modList.modInfoList.GetNthItem(index);
		return (modInfo) ? modInfo->name : NULL;
	}

	BSFixedString GetModAuthor(StaticFunctionTag*, UInt32 index)
	{
		if(index > 255)
			return NULL;
		DataHandler* pDataHandler = DataHandler::GetSingleton();
		ModInfo* modInfo = pDataHandler->modList.modInfoList.GetNthItem(index);
		return (modInfo) ? modInfo->author.Get() : NULL;
	}

	BSFixedString GetModDescription(StaticFunctionTag*, UInt32 index)
	{
		if(index > 255)
			return NULL;
		DataHandler* pDataHandler = DataHandler::GetSingleton();
		ModInfo* modInfo = pDataHandler->modList.modInfoList.GetNthItem(index);
		return (modInfo) ? modInfo->description.Get() : NULL;
	}

	UInt32 GetModDependencyCount(StaticFunctionTag*, UInt32 index)
	{
		if(index > 255)
			return NULL;
		DataHandler* pDataHandler = DataHandler::GetSingleton();
		ModInfo* modInfo = pDataHandler->modList.modInfoList.GetNthItem(index);
		return (modInfo) ? modInfo->numRefMods : 0;
	}

	UInt32 GetNthModDependency(StaticFunctionTag*, UInt32 index, UInt32 dep_index)
	{
		if(index > 255)
			return NULL;
		DataHandler* pDataHandler = DataHandler::GetSingleton();
		ModInfo* modInfo = pDataHandler->modList.modInfoList.GetNthItem(index);
		return (modInfo && dep_index < modInfo->numRefMods) ? modInfo->refModInfo[dep_index]->modIndex : 0;
	}

	void SetGameSettingFloat(StaticFunctionTag * base, BSFixedString name, float value)
	{
		SettingCollectionMap	* settings = *g_gameSettingCollection;

		if(settings)
		{
			Setting	* setting = settings->Get(name.data);
			if(setting)
			{
				if(!setting->SetDouble(value))
				{
					_WARNING("SetGameSettingFloat: %s is not a float", name.data);
				}
			}
			else
			{
				_WARNING("SetGameSettingFloat: %s not found", name.data);
			}
		}
	}

	void SetGameSettingInt(StaticFunctionTag * base, BSFixedString name, UInt32 value)
	{
		SettingCollectionMap	* settings = *g_gameSettingCollection;

		if(settings)
		{
			Setting	* setting = settings->Get(name.data);
			if(setting)
			{
				if(setting->GetType() == Setting::kType_Integer)
				{
					setting->data.u32 = value;
				}
				else
				{
					_WARNING("SetGameSettingInt: %s is not an int", name.data);
				}	
			}
			else
			{
				_WARNING("SetGameSettingInt: %s not found", name.data);
			}
		}
	}

	void SetGameSettingBool(StaticFunctionTag * base, BSFixedString name, bool value)
	{
		SettingCollectionMap	* settings = *g_gameSettingCollection;

		if(settings)
		{
			Setting	* setting = settings->Get(name.data);
			if(setting)
			{
				if(setting->GetType() == Setting::kType_Bool)
				{
					setting->data.u8 = value;
				}
				else
				{
					_WARNING("SetGameSettingBool: %s is not a bool", name.data);
				}
			}
			else
			{
				_WARNING("SetGameSettingBool: %s not found", name.data);
			}
		}
	}

	void SetGameSettingString(StaticFunctionTag * base, BSFixedString name, BSFixedString value)
	{
		SettingCollectionMap	* settings = *g_gameSettingCollection;

		if(settings)
		{
			Setting	* setting = settings->Get(name.data);
			if(setting)
			{
				if(!setting->SetString(value.data))
				{
					_WARNING("SetGameSettingString: %s is not a string", name.data);
				}
			}
			else
			{
				_WARNING("SetGameSettingString: %s not found", name.data);
			}
		}
	}

	void SaveGame(StaticFunctionTag * base, BSFixedString name)
	{
		BGSSaveLoadManager	* mgr = BGSSaveLoadManager::GetSingleton();
		if(!mgr)
			return;

		mgr->RequestSave(name.data);
	}

	void LoadGame(StaticFunctionTag * base, BSFixedString name)
	{
		BGSSaveLoadManager	* mgr = BGSSaveLoadManager::GetSingleton();
		if(!mgr)
			return;

		mgr->RequestLoad(name.data);
	}

	UInt32 GetNumTintMasks(StaticFunctionTag * base)
	{
		PlayerCharacter* pPC = (*g_thePlayer);
		if(!pPC) {
			return 0;
		}
		return pPC->tintMasks.count;
	}

	UInt32 GetNthTintMaskColor(StaticFunctionTag * base, UInt32 n)
	{
		PlayerCharacter* pPC = (*g_thePlayer);
		if(!pPC) {
			return 0;
		}
		TintMask * tintMask = NULL;
		if(pPC->tintMasks.GetNthItem(n, tintMask)) {
			return tintMask->ToARGB();
		}
		return 0;
	}

	UInt32 GetNthTintMaskType(StaticFunctionTag * base, UInt32 n)
	{
		PlayerCharacter* pPC = (*g_thePlayer);
		if(!pPC) {
			return 0;
		}
		TintMask * tintMask = NULL;
		if(pPC->tintMasks.GetNthItem(n, tintMask)) {
			return tintMask->tintType;
		}
		return 0;
	}

	BSFixedString GetNthTintMaskTexturePath(StaticFunctionTag * base, UInt32 n)
	{
		PlayerCharacter* pPC = (*g_thePlayer);
		if(!pPC) {
			return NULL;
		}
		TintMask * tintMask = NULL;
		if(pPC->tintMasks.GetNthItem(n, tintMask)) {
			if(tintMask->texture) {
				return tintMask->texture->str;
			}
		}
	
		return NULL;
	}

	void SetNthTintMaskTexturePath(StaticFunctionTag * base, BSFixedString path, UInt32 n)
	{
		PlayerCharacter* pPC = (*g_thePlayer);
		if(pPC) {
			TintMask * tintMask = NULL;
			if(pPC->tintMasks.GetNthItem(n, tintMask)) {
				if(tintMask->texture) {
					tintMask->texture->str = path;
				}
			}
			if(pPC->overlayTintMasks) {
				if(pPC->overlayTintMasks->GetNthItem(n, tintMask)) {
					if(tintMask->texture) {
						tintMask->texture->str = path;
					}
				}
			}
		}
	}

	void SetPlayerTintMaskColor(TESNPC* actorBase, TintMask * tintMask, UInt32 argb)
	{
		ARGBColor color(argb);
		float alpha = color.GetAlpha() / 255.0;
		if(alpha > 1.0)
			alpha = 1.0;
		if(alpha < 0.0)
			alpha = 0.0;

		// Skin tones must have full alpha, use the alpha channel for saturation instead
		if(tintMask->tintType == TintMask::kMaskType_SkinTone) {
			double saturation = color.GetSaturation();
			color.SetSaturation(alpha * saturation);
			tintMask->color.red = color.GetRed();
			tintMask->color.green = color.GetGreen();
			tintMask->color.blue = color.GetBlue();
			actorBase->color.red = tintMask->color.red;
			actorBase->color.green = tintMask->color.green;
			actorBase->color.blue = tintMask->color.blue;
			tintMask->alpha = 1.0;
		} else {
			tintMask->color.red = color.GetRed();
			tintMask->color.green = color.GetGreen();
			tintMask->color.blue = color.GetBlue();
			tintMask->alpha = alpha;
		}
	}

	void SetNthTintMaskColor(StaticFunctionTag * base, UInt32 n, UInt32 color)
	{
		PlayerCharacter* pPC = (*g_thePlayer);
		if(pPC) {
			TESNPC* npc = DYNAMIC_CAST(pPC->baseForm, TESForm, TESNPC);
			if(npc) {
				TintMask * tintMask = NULL;
				if(pPC->tintMasks.GetNthItem(n, tintMask)) {
					SetPlayerTintMaskColor(npc, tintMask, color);
				}
				if(pPC->overlayTintMasks) {
					if(pPC->overlayTintMasks->GetNthItem(n, tintMask)) {
						SetPlayerTintMaskColor(npc, tintMask, color);
					}
				}
			}
		}
	}

	UInt32 GetNumTintMasksByType(StaticFunctionTag * base, UInt32 tintType)
	{
		PlayerCharacter* pPC = (*g_thePlayer);
		if(!pPC) {
			return 0;
		}
		return CALL_MEMBER_FN(pPC, GetNumTints)(tintType);
	}

	UInt32 GetTintMaskColor(StaticFunctionTag * base, UInt32 tintType, UInt32 index)
	{
		PlayerCharacter* pPC = (*g_thePlayer);
		if(!pPC) {
			return 0;
		}

		UInt32 color = 0;
		TintMask * tintMask = CALL_MEMBER_FN(pPC, GetTintMask)(tintType, index);
		if(tintMask) {
			color = tintMask->ToARGB();
		}


		return color;
	}

	void SetTintMaskColor(StaticFunctionTag * base, UInt32 color, UInt32 tintType, UInt32 index)
	{
		PlayerCharacter* pPC = (*g_thePlayer);
		if(pPC) {
			TESNPC* npc = DYNAMIC_CAST(pPC->baseForm, TESForm, TESNPC);
			if(npc) {
				TintMask * tintMask = CALL_MEMBER_FN(pPC, GetTintMask)(tintType, index);
				if(tintMask) {
					SetPlayerTintMaskColor(npc, tintMask, color);
				}
				if(pPC->overlayTintMasks) { // Overlays don't always have types for some dumb reason
					TintMask * overlayMask = pPC->GetOverlayTintMask(tintMask);
					if(overlayMask) {
						SetPlayerTintMaskColor(npc, overlayMask, color);
					}
				}
			}
		}
	}

	BSFixedString GetTintMaskTexturePath(StaticFunctionTag * base, UInt32 tintType, UInt32 index)
	{
		PlayerCharacter* pPC = (*g_thePlayer);
		if(!pPC) {
			return NULL;
		}
		TintMask * tintMask = CALL_MEMBER_FN(pPC, GetTintMask)(tintType, index);
		if(tintMask && tintMask->texture) {
			return tintMask->texture->str;
		}

		return NULL;
	}

	void SetTintMaskTexturePath(StaticFunctionTag * base, BSFixedString path, UInt32 tintType, UInt32 index)
	{
		PlayerCharacter* pPC = (*g_thePlayer);
		if(pPC) {
			TintMask * tintMask = CALL_MEMBER_FN(pPC, GetTintMask)(tintType, index);
			if(tintMask && tintMask->texture) {
				tintMask->texture->str = path;
			}
			if(pPC->overlayTintMasks) {
				TintMask * overlayMask = pPC->GetOverlayTintMask(tintMask);
				if(overlayMask && overlayMask->texture) {
					overlayMask->texture->str = path;
				}
			}
		}
	}

	void UpdateTintMaskColors(StaticFunctionTag * base)
	{
		BSTaskPool * taskPool = BSTaskPool::GetSingleton();
		if(taskPool) {
			taskPool->UpdateTintMasks();
		}
	}

#ifdef PAPYRUS_CUSTOM_CLASS
	TintMask * GetNthTintMask(StaticFunctionTag * base, UInt32 n)
	{
		PlayerCharacter* pPC = (*g_thePlayer);
		if(pPC) {
			TintMask * tintMask = NULL;
			if(pPC->tintMasks.GetNthItem(n, tintMask)) {
				return tintMask;
			}
		}

		return NULL;
	}
#endif

	void UpdateHairColor(StaticFunctionTag * base)
	{
		BSTaskPool * taskPool = BSTaskPool::GetSingleton();
		if(taskPool) {
			taskPool->UpdateHairColor();
		}
	}

	SInt32 GetCameraState(StaticFunctionTag * base)
	{
		PlayerCamera * playerCamera = PlayerCamera::GetSingleton();
		if(playerCamera) {
			for(int i = 0; i < PlayerCamera::kNumCameraStates; i++) {
				if(playerCamera->cameraState == playerCamera->cameraStates[i])
					return i;
			}
		}

		return -1;
	}

	void SetMiscStat(StaticFunctionTag * base, BSFixedString name, UInt32 value)
	{
		MiscStatManager::MiscStat	* stat = MiscStatManager::GetSingleton()->Get(name.data);

		if(stat)
			stat->value = value;
		else
			_MESSAGE("SetMiscStat: could not find stat (%s)", name.data);
	}

	void SetPlayersLastRiddenHorse(StaticFunctionTag * base, Actor* actor)
	{
		PlayerCharacter* pPC = (*g_thePlayer);
		if(pPC) {
			if(!actor) {
				pPC->lastRiddenHorseHandle = 0;
			} else {
				pPC->lastRiddenHorseHandle = actor->CreateRefHandle();
			}
		}
	}

	SInt32 GetSkillLegendaryLevel(StaticFunctionTag * base, BSFixedString actorValue)
	{
		PlayerCharacter* pPC = (*g_thePlayer);
		if(pPC && pPC->skills) {
			return pPC->skills->GetSkillLegendaryLevel(actorValue);
		}

		return -1;
	}

	void SetSkillLegendaryLevel(StaticFunctionTag * base, BSFixedString actorValue, UInt32 level)
	{
		PlayerCharacter* pPC = (*g_thePlayer);
		if(pPC && pPC->skills) {
			return pPC->skills->SetSkillLegendaryLevel(actorValue, level);
		}
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

	registry->RegisterFunction(
		new NativeFunction2 <StaticFunctionTag, void, BSFixedString, float>("SetGameSettingFloat", "Game", papyrusGame::SetGameSettingFloat, registry));

	registry->RegisterFunction(
		new NativeFunction2 <StaticFunctionTag, void, BSFixedString, UInt32>("SetGameSettingInt", "Game", papyrusGame::SetGameSettingInt, registry));

	registry->RegisterFunction(
		new NativeFunction2 <StaticFunctionTag, void, BSFixedString, bool>("SetGameSettingBool", "Game", papyrusGame::SetGameSettingBool, registry));

	registry->RegisterFunction(
		new NativeFunction2 <StaticFunctionTag, void, BSFixedString, BSFixedString>("SetGameSettingString", "Game", papyrusGame::SetGameSettingString, registry));

	// Save/Load
	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, BSFixedString>("SaveGame", "Game", papyrusGame::SaveGame, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, BSFixedString>("LoadGame", "Game", papyrusGame::LoadGame, registry));

	// Tintmasks
	registry->RegisterFunction(
		new NativeFunction0 <StaticFunctionTag, UInt32>("GetNumTintMasks", "Game", papyrusGame::GetNumTintMasks, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, UInt32, UInt32>("GetNthTintMaskColor", "Game", papyrusGame::GetNthTintMaskColor, registry));

	registry->RegisterFunction(
		new NativeFunction2 <StaticFunctionTag, void, UInt32, UInt32>("SetNthTintMaskColor", "Game", papyrusGame::SetNthTintMaskColor, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, UInt32, UInt32>("GetNthTintMaskType", "Game", papyrusGame::GetNthTintMaskType, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, BSFixedString, UInt32>("GetNthTintMaskTexturePath", "Game", papyrusGame::GetNthTintMaskTexturePath, registry));

	registry->RegisterFunction(
		new NativeFunction2 <StaticFunctionTag, void, BSFixedString, UInt32>("SetNthTintMaskTexturePath", "Game", papyrusGame::SetNthTintMaskTexturePath, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, UInt32, UInt32>("GetNumTintsByType", "Game", papyrusGame::GetNumTintMasksByType, registry));

	registry->RegisterFunction(
		new NativeFunction2 <StaticFunctionTag, UInt32, UInt32, UInt32>("GetTintMaskColor", "Game", papyrusGame::GetTintMaskColor, registry));

	registry->RegisterFunction(
		new NativeFunction3 <StaticFunctionTag, void, UInt32, UInt32, UInt32>("SetTintMaskColor", "Game", papyrusGame::SetTintMaskColor, registry));

	registry->RegisterFunction(
		new NativeFunction2 <StaticFunctionTag, BSFixedString, UInt32, UInt32>("GetTintMaskTexturePath", "Game", papyrusGame::GetTintMaskTexturePath, registry));

	registry->RegisterFunction(
		new NativeFunction3 <StaticFunctionTag, void, BSFixedString, UInt32, UInt32>("SetTintMaskTexturePath", "Game", papyrusGame::SetTintMaskTexturePath, registry));

	registry->RegisterFunction(
		new NativeFunction0 <StaticFunctionTag, void>("UpdateTintMaskColors", "Game", papyrusGame::UpdateTintMaskColors, registry));

	registry->RegisterFunction(
		new NativeFunction0 <StaticFunctionTag, void>("UpdateHairColor", "Game", papyrusGame::UpdateHairColor, registry));

#ifdef PAPYRUS_CUSTOM_CLASS
	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, TintMask*, UInt32>("GetNthTintMask", "Game", papyrusGame::GetNthTintMask, registry));
#endif

	// Misc
	registry->RegisterFunction(
		new NativeFunction0 <StaticFunctionTag, SInt32>("GetCameraState", "Game", papyrusGame::GetCameraState, registry));

	registry->RegisterFunction(
		new NativeFunction2 <StaticFunctionTag, void, BSFixedString, UInt32>("SetMiscStat", "Game", papyrusGame::SetMiscStat, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, Actor*>("SetPlayersLastRiddenHorse", "Game", papyrusGame::SetPlayersLastRiddenHorse, registry));

	// Skills
	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, SInt32, BSFixedString>("GetSkillLegendaryLevel", "Game", papyrusGame::GetSkillLegendaryLevel, registry));

	registry->RegisterFunction(
		new NativeFunction2 <StaticFunctionTag, void, BSFixedString, UInt32>("SetSkillLegendaryLevel", "Game", papyrusGame::SetSkillLegendaryLevel, registry));

	// Mod
	registry->SetFunctionFlags("Game", "GetModCount", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Game", "GetModByName", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Game", "GetModName", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Game", "GetModAuthor", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Game", "GetModDescription", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Game", "GetModDependencyCount", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Game", "GetNthModDependency", VMClassRegistry::kFunctionFlag_NoWait);

	// GameSettings
	registry->SetFunctionFlags("Game", "SetGameSettingFloat", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Game", "SetGameSettingInt", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Game", "SetGameSettingBool", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Game", "SetGameSettingString", VMClassRegistry::kFunctionFlag_NoWait);

	// Save/Load
	registry->SetFunctionFlags("Game", "SaveGame", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Game", "LoadGame", VMClassRegistry::kFunctionFlag_NoWait);

	// Tintmasks
	registry->SetFunctionFlags("Game", "GetNumTintMasks", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Game", "GetNthTintMaskColor", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Game", "SetNthTintMaskColor", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Game", "GetNthTintMaskType", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Game", "GetNthTintMaskTexturePath", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Game", "SetNthTintMaskTexturePath", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Game", "GetNumTintsByType", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Game", "GetTintMaskColor", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Game", "SetTintMaskColor", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Game", "GetTintMaskTexturePath", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Game", "SetTintMaskTexturePath", VMClassRegistry::kFunctionFlag_NoWait);

#ifdef PAPYRUS_CUSTOM_CLASS
	registry->SetFunctionFlags("Game", "GetNthTintMask", VMClassRegistry::kFunctionFlag_NoWait);
#endif

	// Misc
	registry->SetFunctionFlags("Game", "SetMiscStat", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Game", "GetCameraState", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Game", "SetPlayersLastRiddenHorse", VMClassRegistry::kFunctionFlag_NoWait);

	//registry->SetFunctionFlags("Game", "UpdateTintMaskColors", VMClassRegistry::kFunctionFlag_NoWait);
	//registry->SetFunctionFlags("Game", "UpdateHairColor", VMClassRegistry::kFunctionFlag_NoWait);

	// Skills
	registry->SetFunctionFlags("Game", "GetSkillLegendaryLevel", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Game", "SetSkillLegendaryLevel", VMClassRegistry::kFunctionFlag_NoWait);
}
