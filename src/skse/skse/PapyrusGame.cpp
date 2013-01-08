#include "PapyrusGame.h"
#include "PapyrusColorForm.h"

#include "GameRTTI.h"
#include "GameAPI.h"
#include "GameReferences.h"
#include "GameData.h"
#include "GameSettings.h"
#include "GameForms.h"

typedef UInt32 (* _UpdatePlayerTints)();
_UpdatePlayerTints UpdatePlayerTints = (_UpdatePlayerTints)0x0087F190;

typedef void * (* _UpdatePlayerSkin)(PlayerCharacter*, NiColorA*);
_UpdatePlayerSkin UpdatePlayerSkin = (_UpdatePlayerSkin)0x005A9C60;

typedef void * (* _UpdatePlayerHair)(PlayerCharacter*, NiColorA*);
_UpdatePlayerHair UpdatePlayerHair = (_UpdatePlayerHair)0x005A9C90;

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
		return pPC->tintMasks.count;
	}

	UInt32 GetNthTintMaskColor(StaticFunctionTag * base, UInt32 n)
	{
		PlayerCharacter* pPC = (*g_thePlayer);
		TintMask * tintMask;
		if(pPC->tintMasks.GetNthItem(n, tintMask)) {
			return (((UInt32)(tintMask->alpha * 255)) << 24) | tintMask->color.red << 16 | tintMask->color.green << 8 | tintMask->color.blue;
		}
		return 0;
	}

	UInt32 GetNthTintMaskType(StaticFunctionTag * base, UInt32 n)
	{
		PlayerCharacter* pPC = (*g_thePlayer);
		TintMask * tintMask;
		if(pPC->tintMasks.GetNthItem(n, tintMask)) {
			return tintMask->tintType;
		}
		return 0;
	}

	BSFixedString GetNthTintMaskTexturePath(StaticFunctionTag * base, UInt32 n)
	{
		PlayerCharacter* pPC = (*g_thePlayer);
		TintMask * tintMask;
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
		TintMask * tintMask;
		if(pPC->tintMasks.GetNthItem(n, tintMask)) {
			if(tintMask->texture) {
				tintMask->texture->str = path;
			}
		}
	}

	void SetNthTintMaskColor(StaticFunctionTag * base, UInt32 n, UInt32 color)
	{
		PlayerCharacter* pPC = (*g_thePlayer);
		TESNPC* npc = DYNAMIC_CAST(pPC->baseForm, TESForm, TESNPC);
		TintMask * tintMask;
		if(pPC->tintMasks.GetNthItem(n, tintMask)) {
			float alpha = ((color & 0xFF000000) >> 24) / 255.0;
			UInt8 red = (color & 0x00FF0000) >> 16;
			UInt8 green = (color & 0x0000FF00) >> 8;
			UInt8 blue = color & 0x000000FF;

			if(alpha > 1.0)
				alpha = 1.0;
			if(alpha < 0.0)
				alpha = 0.0;

			// Skin tones must have full alpha, use the alpha channel for saturation instead
			if(tintMask->tintType == TintMask::kMaskType_SkinTone) {
				float saturation = papyrusColorComponent::GetSaturation(NULL, color);
				UInt32 outColor = papyrusColorComponent::SetSaturation(NULL, color, alpha * saturation);
				tintMask->color.red = (outColor & 0xFF0000) >> 16;
				tintMask->color.green = (outColor & 0x00FF00) >> 8;
				tintMask->color.blue = (outColor & 0x0000FF);
				npc->color.red = tintMask->color.red;
				npc->color.green = tintMask->color.green;
				npc->color.blue = tintMask->color.blue;
				tintMask->alpha = 1.0;
			} else {
				tintMask->color.red = red;
				tintMask->color.green = green;
				tintMask->color.blue = blue;
				tintMask->alpha = alpha;
			}
		}
	}

	UInt32 GetNumTintMasksByType(StaticFunctionTag * base, UInt32 tintType)
	{
		PlayerCharacter* pPC = (*g_thePlayer);
		return CALL_MEMBER_FN(pPC, GetNumTints)(tintType);
	}

	UInt32 GetTintMaskColor(StaticFunctionTag * base, UInt32 tintType, UInt32 index)
	{
		UInt32 color = 0;
		PlayerCharacter* pPC = (*g_thePlayer);
		TESNPC* npc = DYNAMIC_CAST(pPC->baseForm, TESForm, TESNPC);
		TintMask * tintMask = CALL_MEMBER_FN(pPC, GetTintMask)(tintType, index);
		if(tintMask) {
			color = (((UInt32)(tintMask->alpha * 255)) << 24) | tintMask->color.red << 16 | tintMask->color.green << 8 | tintMask->color.blue;
		}

		return color;
	}

	void SetTintMaskColor(StaticFunctionTag * base, UInt32 color, UInt32 tintType, UInt32 index)
	{
		PlayerCharacter* pPC = (*g_thePlayer);
		TintMask * tintMask = CALL_MEMBER_FN(pPC, GetTintMask)(tintType, index);
		TESNPC* npc = DYNAMIC_CAST(pPC->baseForm, TESForm, TESNPC);
		if(tintMask) {
			float alpha = ((color & 0xFF000000) >> 24) / 255.0;
			UInt8 red = (color & 0x00FF0000) >> 16;
			UInt8 green = (color & 0x0000FF00) >> 8;
			UInt8 blue = color & 0x000000FF;

			if(alpha > 1.0)
				alpha = 1.0;
			if(alpha < 0.0)
				alpha = 0.0;

			// Apply to overlay if there is one
			/*if(pPC->overlayTintMasks) {
				TintMask * overlayMask = pPC->GetOverlayTintMask(tintType, index);
				if(overlayMask && overlayMask->tintType == tintType) {
					if(tintType == TintMask::kMaskType_SkinTone) {
						float saturation = papyrusColorComponent::GetSaturation(NULL, color);
						UInt32 outColor = papyrusColorComponent::SetSaturation(NULL, color, alpha * saturation);
						overlayMask->color.red = (outColor & 0xFF0000) >> 16;
						overlayMask->color.green = (outColor & 0x00FF00) >> 8;
						overlayMask->color.blue = (outColor & 0x0000FF);
						overlayMask->alpha = 1.0;
					} else {
						overlayMask->color.red = red;
						overlayMask->color.green = green;
						overlayMask->color.blue = blue;
						overlayMask->alpha = alpha;
					}
				}
			}*/

			// Skin tones must have full alpha, use the alpha channel for saturation instead
			if(tintType == TintMask::kMaskType_SkinTone) {
				float saturation = papyrusColorComponent::GetSaturation(NULL, color);
				UInt32 outColor = papyrusColorComponent::SetSaturation(NULL, color, alpha * saturation);
				tintMask->color.red = (outColor & 0xFF0000) >> 16;
				tintMask->color.green = (outColor & 0x00FF00) >> 8;
				tintMask->color.blue = (outColor & 0x0000FF);
				npc->color.red = tintMask->color.red;
				npc->color.green = tintMask->color.green;
				npc->color.blue = tintMask->color.blue;
				tintMask->alpha = 1.0;
			} else {
				tintMask->color.red = red;
				tintMask->color.green = green;
				tintMask->color.blue = blue;
				tintMask->alpha = alpha;
			}

			//CALL_MEMBER_FN(pPC, QueueNiNodeUpdate)(true); // Call this explicitly incase multiple tints are changed simultanenously
		}
	}

	BSFixedString GetTintMaskTexturePath(StaticFunctionTag * base, UInt32 tintType, UInt32 index)
	{
		PlayerCharacter* pPC = (*g_thePlayer);
		TESNPC* npc = DYNAMIC_CAST(pPC->baseForm, TESForm, TESNPC);
		TintMask * tintMask = CALL_MEMBER_FN(pPC, GetTintMask)(tintType, index);
		if(tintMask && tintMask->texture) {
			return tintMask->texture->str;
		}

		return NULL;
	}

	void SetTintMaskTexturePath(StaticFunctionTag * base, BSFixedString path, UInt32 tintType, UInt32 index)
	{
		PlayerCharacter* pPC = (*g_thePlayer);
		TintMask * tintMask = CALL_MEMBER_FN(pPC, GetTintMask)(tintType, index);
		TESNPC* npc = DYNAMIC_CAST(pPC->baseForm, TESForm, TESNPC);
		if(tintMask && tintMask->texture) {
			tintMask->texture->str = path;
		}
	}

	void UpdateTintMaskColors(StaticFunctionTag * base)
	{
		PlayerCharacter* pPC = (*g_thePlayer);
		TintMask * tintMask = CALL_MEMBER_FN(pPC, GetTintMask)(TintMask::kMaskType_SkinTone, 0);
		if(tintMask) {
			NiColorA val;
			val.r = tintMask->color.red / 255.0;
			val.g = tintMask->color.green / 255.0;
			val.b = tintMask->color.blue / 255.0;
			UpdatePlayerSkin(pPC, &val);
		}

		UpdatePlayerTints();
	}

	void UpdateHairColor(StaticFunctionTag * base)
	{
		PlayerCharacter* pPC = (*g_thePlayer);
		TESNPC* npc = DYNAMIC_CAST(pPC->baseForm, TESForm, TESNPC);
		if(npc && npc->headData) {
			BGSColorForm * hairColor = npc->headData->hairColor;
			if(hairColor) {
				NiColorA val;
				val.r = hairColor->color.red / 128.0;
				val.g = hairColor->color.green / 128.0;
				val.b = hairColor->color.blue / 128.0;
				UpdatePlayerHair(pPC, &val);
			}
		}
	}

	UInt32 GetMiscStat(StaticFunctionTag * base, BSFixedString name)
	{
		MiscStatManager::MiscStat	* stat = MiscStatManager::GetSingleton()->Get(name.data);

		if(stat)
			return stat->value;
		else
		{
			_MESSAGE("GetMiscStat: could not find stat (%s)", name.data);
			return 0;
		}
	}

	void SetMiscStat(StaticFunctionTag * base, BSFixedString name, UInt32 value)
	{
		MiscStatManager::MiscStat	* stat = MiscStatManager::GetSingleton()->Get(name.data);

		if(stat)
			stat->value = value;
		else
			_MESSAGE("SetMiscStat: could not find stat (%s)", name.data);
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

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, UInt32, BSFixedString>("GetMiscStat", "Game", papyrusGame::GetMiscStat, registry));

	registry->RegisterFunction(
		new NativeFunction2 <StaticFunctionTag, void, BSFixedString, UInt32>("SetMiscStat", "Game", papyrusGame::SetMiscStat, registry));

	registry->SetFunctionFlags("Game", "GetModCount", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Game", "GetModByName", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Game", "GetModName", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Game", "GetModAuthor", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Game", "GetModDescription", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Game", "GetModDependencyCount", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Game", "GetNthModDependency", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Game", "SetGameSettingFloat", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Game", "SetGameSettingInt", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Game", "SetGameSettingBool", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Game", "SetGameSettingString", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Game", "SaveGame", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Game", "LoadGame", VMClassRegistry::kFunctionFlag_NoWait);

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
	registry->SetFunctionFlags("Game", "GetMiscStat", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("Game", "SetMiscStat", VMClassRegistry::kFunctionFlag_NoWait);

	//registry->SetFunctionFlags("Game", "UpdateTintMaskColors", VMClassRegistry::kFunctionFlag_NoWait);
	//registry->SetFunctionFlags("Game", "UpdateHairColor", VMClassRegistry::kFunctionFlag_NoWait);
}
