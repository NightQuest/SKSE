#include "PapyrusScroll.h"
#include "PapyrusSpell.h"
#include "GameObjects.h"

namespace papyrusScroll
{
	float GetCastTime(ScrollItem* thisSpell)
	{
		return (thisSpell)? thisSpell->data.castTime : 0.0;
	}

	BGSPerk* GetPerk(ScrollItem* thisSpell)
	{
		return (thisSpell) ? thisSpell->data.spellPerk : NULL;
	}

	UInt32 GetNumEffects(ScrollItem* thisMagic)
	{ return magicItemUtils::GetNumEffects(thisMagic); }

	float GetNthEffectMagnitude(ScrollItem* thisMagic, UInt32 index)
	{ return magicItemUtils::GetNthEffectMagnitude(thisMagic, index); }

	UInt32 GetNthEffectArea(ScrollItem* thisMagic, UInt32 index)
	{ return magicItemUtils::GetNthEffectArea(thisMagic, index); }

	UInt32 GetNthEffectDuration(ScrollItem* thisMagic, UInt32 index)
	{ return magicItemUtils::GetNthEffectDuration(thisMagic, index); }

	EffectSetting* GetNthEffectMagicEffect(ScrollItem* thisMagic, UInt32 index)
	{ return magicItemUtils::GetNthEffectMagicEffect(thisMagic, index); }

	UInt32 GetCostliestEffectIndex(ScrollItem* thisMagic)
	{ return magicItemUtils::GetCostliestEffectIndex(thisMagic); }
}

#include "PapyrusVM.h"
#include "PapyrusNativeFunctions.h"

void papyrusScroll::RegisterFuncs(VMClassRegistry* registry)
{

	registry->RegisterFunction(
		new NativeFunction0<ScrollItem, UInt32>("GetNumEffects", "Scroll", papyrusScroll::GetNumEffects, registry));

	registry->RegisterFunction(
		new NativeFunction1<ScrollItem, float, UInt32>("GetNthEffectMagnitude", "Scroll", papyrusScroll::GetNthEffectMagnitude, registry));

	registry->RegisterFunction(
		new NativeFunction1<ScrollItem, UInt32, UInt32>("GetNthEffectArea", "Scroll", papyrusScroll::GetNthEffectArea, registry));

	registry->RegisterFunction(
		new NativeFunction1<ScrollItem, UInt32, UInt32>("GetNthEffectDuration", "Scroll", papyrusScroll::GetNthEffectDuration, registry));

	registry->RegisterFunction(
		new NativeFunction1<ScrollItem, EffectSetting*, UInt32>("GetNthEffectMagicEffect", "Scroll", papyrusScroll::GetNthEffectMagicEffect, registry));

	registry->RegisterFunction(
		new NativeFunction0<ScrollItem, UInt32>("GetCostliestEffectIndex", "Scroll", papyrusScroll::GetCostliestEffectIndex, registry));
}
