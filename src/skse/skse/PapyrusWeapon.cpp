#include "PapyrusWeapon.h"

#include "GameObjects.h"

namespace papyrusWeapon
{
	UInt32 GetBaseDamage(TESObjectWEAP* thisWeapon)
	{
		if (!thisWeapon)
			return 0;
		return thisWeapon->damage.GetAttackDamage();
	}

	void SetBaseDamage(TESObjectWEAP* thisWeapon, UInt32 nuDamage)
	{
		if (thisWeapon) {
			thisWeapon->damage.attackDamage = nuDamage;
		}
	}

	UInt32 GetCritDamage(TESObjectWEAP* thisWeapon)
	{
		if (!thisWeapon)
			return 0;
		return thisWeapon->critDamage();
	}

	void SetCritDamage(TESObjectWEAP* thisWeapon, UInt32 critDamage)
	{
		if (thisWeapon) {
			thisWeapon->critData.critDamage = critDamage;
		}
	}

	float GetReach(TESObjectWEAP* thisWeapon)
	{
		if (!thisWeapon)
			return 0.0;
		return thisWeapon->reach();
	}

	void SetReach(TESObjectWEAP* thisWeapon, float nuReach)
	{
		if (!thisWeapon)
			return;
		thisWeapon->gameData.reach = nuReach;
	}

	float GetSpeed(TESObjectWEAP* thisWeapon)
	{
		if (!thisWeapon)
			return 0.0;
		return thisWeapon->speed();
	}

	void SetSpeed(TESObjectWEAP* thisWeapon, float speed)
	{
		if (thisWeapon) {
			thisWeapon->gameData.speed = speed;
		}
	}

	float GetStagger(TESObjectWEAP* thisWeapon)
	{
		if (!thisWeapon)
			return 0.0;
		return thisWeapon->stagger();
	}

	void SetStagger(TESObjectWEAP* thisWeapon, float stagger)
	{
		if (thisWeapon) {
			thisWeapon->gameData.stagger = stagger;
		}
	}

	float GetMinRange(TESObjectWEAP* thisWeapon)
	{
		if (!thisWeapon)
			return 0.0;
		return thisWeapon->minRange();
	}

	void SetMinRange(TESObjectWEAP* thisWeapon, float minRange)
	{
		if (thisWeapon) {
			thisWeapon->gameData.minRange = minRange;
		}
	}

	float GetMaxRange(TESObjectWEAP* thisWeapon)
	{
		if (!thisWeapon)
			return 0.0;
		return thisWeapon->maxRange();
	}

	void SetMaxRange(TESObjectWEAP* thisWeapon, float maxRange)
	{
		if (thisWeapon) {
			thisWeapon->gameData.maxRange = maxRange;
		}
	}

	UInt32 GetWeaponType(TESObjectWEAP* thisWeapon)
	{
		if (!thisWeapon)
			return 0;
		return thisWeapon->type();
	}

	void SetWeaponType(TESObjectWEAP* thisWeapon, UInt32 nuType)
	{
		if (!thisWeapon)
			return;
		thisWeapon->gameData.type = nuType;
	}


	BSFixedString GetModelPath(TESObjectWEAP* thisWeapon)
	{
		return (thisWeapon) ? thisWeapon->texSwap.GetModelName() : NULL;
	}

	void SetModelPath(TESObjectWEAP* thisWeapon, BSFixedString nuPath)
	{
		if (!thisWeapon)
			return;

		thisWeapon->texSwap.SetModelName(nuPath.data);
	}

	BSFixedString GetIconPath(TESObjectWEAP* thisWeapon)
	{
		return (thisWeapon) ? thisWeapon->icon.str : NULL;
	}

	void SetIconPath(TESObjectWEAP* thisWeapon, BSFixedString nuPath)
	{
		if (!thisWeapon)
			return;

		thisWeapon->icon.str = nuPath.data;
	}

	BSFixedString GetMessageIconPath(TESObjectWEAP* thisWeapon)
	{
		return (thisWeapon) ? thisWeapon->messageIcon.icon.str : NULL;
	}

	void SetMessageIconPath(TESObjectWEAP* thisWeapon, BSFixedString nuPath)
	{
		if (!thisWeapon)
			return;

		thisWeapon->messageIcon.icon.str = nuPath.data;
	}

	EnchantmentItem* GetEnchantment(TESObjectWEAP* thisWeapon)
	{
		return (thisWeapon) ? thisWeapon->enchantable.enchantment : NULL;
	}

	void SetEnchantment(TESObjectWEAP* thisWeapon, EnchantmentItem* enchantment)
	{
		if (thisWeapon) {
			thisWeapon->enchantable.enchantment = enchantment;
		}
	}

}

#include "PapyrusVM.h"
#include "PapyrusNativeFunctions.h"

void papyrusWeapon::RegisterFuncs(VMClassRegistry* registry)
{
	registry->RegisterFunction(
		new NativeFunction0 <TESObjectWEAP, UInt32>("GetWeaponType", "Weapon", papyrusWeapon::GetWeaponType, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESObjectWEAP, void, UInt32>("SetWeaponType", "Weapon", papyrusWeapon::SetWeaponType, registry));


	registry->RegisterFunction(
		new NativeFunction0 <TESObjectWEAP, UInt32>("GetBaseDamage", "Weapon", papyrusWeapon::GetBaseDamage, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESObjectWEAP, void, UInt32>("SetBaseDamage", "Weapon", papyrusWeapon::SetBaseDamage, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESObjectWEAP, UInt32>("GetCritDamage", "Weapon", papyrusWeapon::GetCritDamage, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESObjectWEAP, void, UInt32>("SetCritDamage", "Weapon", papyrusWeapon::SetCritDamage, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESObjectWEAP, float>("GetReach", "Weapon", papyrusWeapon::GetReach, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESObjectWEAP, void, float>("SetReach", "Weapon", papyrusWeapon::SetReach, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESObjectWEAP, float>("GetMinRange", "Weapon", papyrusWeapon::GetMinRange, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESObjectWEAP, void, float>("SetMinRange", "Weapon", papyrusWeapon::SetMinRange, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESObjectWEAP, float>("GetMaxRange", "Weapon", papyrusWeapon::GetMaxRange, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESObjectWEAP, void, float>("SetMaxRange", "Weapon", papyrusWeapon::SetMaxRange, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESObjectWEAP, float>("GetSpeed", "Weapon", papyrusWeapon::GetSpeed, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESObjectWEAP, void, float>("SetSpeed", "Weapon", papyrusWeapon::SetSpeed, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESObjectWEAP, float>("GetStagger", "Weapon", papyrusWeapon::GetStagger, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESObjectWEAP, void, float>("SetStagger", "Weapon", papyrusWeapon::SetStagger, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESObjectWEAP, BSFixedString>("GetModelPath", "Weapon", papyrusWeapon::GetModelPath, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESObjectWEAP, void, BSFixedString>("SetModelPath", "Weapon", papyrusWeapon::SetModelPath, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESObjectWEAP, BSFixedString>("GetIconPath", "Weapon", papyrusWeapon::GetIconPath, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESObjectWEAP, void, BSFixedString>("SetIconPath", "Weapon", papyrusWeapon::SetIconPath, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESObjectWEAP, BSFixedString>("GetMessageIconPath", "Weapon", papyrusWeapon::GetMessageIconPath, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESObjectWEAP, void, BSFixedString>("SetMessageIconPath", "Weapon", papyrusWeapon::SetMessageIconPath, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESObjectWEAP, EnchantmentItem*>("GetEnchantment", "Weapon", papyrusWeapon::GetEnchantment, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESObjectWEAP, void, EnchantmentItem*>("SetEnchantment", "Weapon", papyrusWeapon::SetEnchantment, registry));

}
