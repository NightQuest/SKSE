#include "PapyrusWeapon.h"

#include "GameObjects.h"

namespace papyrusWeapon
{
	UInt16 GetBaseDamage(TESObjectWEAP* thisWeapon)
	{
		if (!thisWeapon)
			return 0;
		return thisWeapon->damage.GetAttackDamage();
	}

	void SetBaseDamage(TESObjectWEAP* thisWeapon, UInt16 nuDamage)
	{
		if (thisWeapon) {
			thisWeapon->damage.attackDamage = nuDamage;
		}
	}

	float GetReach(TESObjectWEAP* thisWeapon)
	{
		if (!thisWeapon)
			return 0.0;
		return thisWeapon->unk0C4.reach;
	}

	void SetReach(TESObjectWEAP* thisWeapon, float nuReach)
	{
		if (!thisWeapon)
			return;
		thisWeapon->unk0C4.reach = nuReach;
	}

	float GetSpeed(TESObjectWEAP* thisWeapon)
	{
		if (!thisWeapon)
			return 0.0;
		return thisWeapon->unk0C4.speed;
	}

	void SetSpeed(TESObjectWEAP* thisWeapon, float speed)
	{
		if (thisWeapon) {
			thisWeapon->unk0C4.speed = speed;
		}
	}

	float GetStagger(TESObjectWEAP* thisWeapon)
	{
		if (!thisWeapon)
			return 0.0;
		return thisWeapon->unk0C4.stagger;
	}

	void SetStagger(TESObjectWEAP* thisWeapon, float stagger)
	{
		if (thisWeapon) {
			thisWeapon->unk0C4.stagger = stagger;
		}
	}



	UInt8 GetWeaponType(TESObjectWEAP* thisWeapon)
	{
		if (!thisWeapon)
			return 0;
		return thisWeapon->type();
	}

	void SetWeaponType(TESObjectWEAP* thisWeapon, UInt8 nuType)
	{
		if (!thisWeapon)
			return;
		thisWeapon->unk0C4.type = nuType;
	}

}
