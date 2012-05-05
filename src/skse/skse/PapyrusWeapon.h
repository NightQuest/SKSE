#pragma once

class TESObjectWEAP;

namespace papyrusWeapon
{
	UInt16 GetBaseDamage(TESObjectWEAP* thisWeapon);
	void SetBaseDamage(TESObjectWEAP* thisWeapon, UInt16 nuDamage);
	float GetReach(TESObjectWEAP* thisWeapon);
	void SetReach(TESObjectWEAP* thisWeapon, float nuReach);
	UInt8 GetWeaponType(TESObjectWEAP* thisWeapon);
	void SetWeaponType(TESObjectWEAP* thisWeapon, UInt8 nuType);
	float GetSpeed(TESObjectWEAP* thisWeapon);
	void SetSpeed(TESObjectWEAP* thisWeapon, float speed);
	float GetStagger(TESObjectWEAP* thisWeapon);
	void SetStagger(TESObjectWEAP* thisWeapon, float stagger);
}
