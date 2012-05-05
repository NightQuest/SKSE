#pragma once

class TESObjectWEAP;
class VMClassRegistry;

#include "GameTypes.h"

namespace papyrusWeapon
{
	void RegisterFuncs(VMClassRegistry* registry);

	UInt32 GetBaseDamage(TESObjectWEAP* thisWeapon);
	void SetBaseDamage(TESObjectWEAP* thisWeapon, UInt32 nuDamage);
	float GetReach(TESObjectWEAP* thisWeapon);
	void SetReach(TESObjectWEAP* thisWeapon, float nuReach);
	UInt32 GetWeaponType(TESObjectWEAP* thisWeapon);
	void SetWeaponType(TESObjectWEAP* thisWeapon, UInt32 nuType);
	float GetSpeed(TESObjectWEAP* thisWeapon);
	void SetSpeed(TESObjectWEAP* thisWeapon, float speed);
	float GetStagger(TESObjectWEAP* thisWeapon);
	void SetStagger(TESObjectWEAP* thisWeapon, float stagger);

	BSFixedString GetModelPath(TESObjectWEAP* thisWeapon);
	void SetModelPath(TESObjectWEAP* thisWeapon, BSFixedString nuPath);

	BSFixedString GetIconPath(TESObjectWEAP* thisWeapon);
	void SetIconPath(TESObjectWEAP* thisWeapon, BSFixedString nuPath);

	BSFixedString GetMessageIconPath(TESObjectWEAP* thisWeapon);
	void SetMessageIconPath(TESObjectWEAP* thisWeapon, BSFixedString nuPath);
}
