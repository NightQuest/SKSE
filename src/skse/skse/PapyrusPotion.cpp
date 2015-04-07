#include "PapyrusPotion.h"
#include "PapyrusSpell.h"
#include "GameObjects.h"

namespace papyrusPotion
{
	bool IsFood(AlchemyItem* thisPotion)
	{
		return (thisPotion) ? thisPotion->IsFood() : false;
	}

	UInt32 GetNumEffects(AlchemyItem* thisMagic)
	{ return magicItemUtils::GetNumEffects(thisMagic); }

	float GetNthEffectMagnitude(AlchemyItem* thisMagic, UInt32 index)
	{ return magicItemUtils::GetNthEffectMagnitude(thisMagic, index); }

	UInt32 GetNthEffectArea(AlchemyItem* thisMagic, UInt32 index)
	{ return magicItemUtils::GetNthEffectArea(thisMagic, index); }

	UInt32 GetNthEffectDuration(AlchemyItem* thisMagic, UInt32 index)
	{ return magicItemUtils::GetNthEffectDuration(thisMagic, index); }

	EffectSetting* GetNthEffectMagicEffect(AlchemyItem* thisMagic, UInt32 index)
	{ return magicItemUtils::GetNthEffectMagicEffect(thisMagic, index); }

	UInt32 GetCostliestEffectIndex(AlchemyItem* thisMagic)
	{ return magicItemUtils::GetCostliestEffectIndex(thisMagic); }
}

#include "PapyrusVM.h"
#include "PapyrusNativeFunctions.h"

void papyrusPotion::RegisterFuncs(VMClassRegistry* registry)
{
	registry->RegisterFunction(
		new NativeFunction0 <AlchemyItem, bool>("IsFood", "Potion", papyrusPotion::IsFood, registry));

	registry->RegisterFunction(
		new NativeFunction0<AlchemyItem, UInt32>("GetNumEffects", "Potion", papyrusPotion::GetNumEffects, registry));

	registry->RegisterFunction(
		new NativeFunction1<AlchemyItem, float, UInt32>("GetNthEffectMagnitude", "Potion", papyrusPotion::GetNthEffectMagnitude, registry));

	registry->RegisterFunction(
		new NativeFunction1<AlchemyItem, UInt32, UInt32>("GetNthEffectArea", "Potion", papyrusPotion::GetNthEffectArea, registry));

	registry->RegisterFunction(
		new NativeFunction1<AlchemyItem, UInt32, UInt32>("GetNthEffectDuration", "Potion", papyrusPotion::GetNthEffectDuration, registry));

	registry->RegisterFunction(
		new NativeFunction1<AlchemyItem, EffectSetting*, UInt32>("GetNthEffectMagicEffect", "Potion", papyrusPotion::GetNthEffectMagicEffect, registry));

	registry->RegisterFunction(
		new NativeFunction0<AlchemyItem, UInt32>("GetCostliestEffectIndex", "Potion", papyrusPotion::GetCostliestEffectIndex, registry));
}
