#include "PapyrusSpell.h"

#include "GameObjects.h"
#include "GameReferences.h"

namespace papyrusSpell
{
	float GetCastTime(SpellItem* thisSpell)
	{
		return (thisSpell)? thisSpell->data.castTime : 0.0;
	}

	BGSPerk* GetPerk(SpellItem* thisSpell)
	{
		return (thisSpell) ? thisSpell->data.spellPerk : NULL;
	}

	UInt32 GetNumEffects(SpellItem* thisMagic)
	{ return magicItemUtils::GetNumEffects(thisMagic); }

	float GetNthEffectMagnitude(SpellItem* thisMagic, UInt32 index)
	{ return magicItemUtils::GetNthEffectMagnitude(thisMagic, index); }

	UInt32 GetNthEffectArea(SpellItem* thisMagic, UInt32 index)
	{ return magicItemUtils::GetNthEffectArea(thisMagic, index); }

	UInt32 GetNthEffectDuration(SpellItem* thisMagic, UInt32 index)
	{ return magicItemUtils::GetNthEffectDuration(thisMagic, index); }

	EffectSetting* GetNthEffectMagicEffect(SpellItem* thisMagic, UInt32 index)
	{ return magicItemUtils::GetNthEffectMagicEffect(thisMagic, index); }

	UInt32 GetCostliestEffectIndex(SpellItem* thisMagic)
	{ return magicItemUtils::GetCostliestEffectIndex(thisMagic); }

	UInt32 GetMagickaCost(SpellItem* thisSpell)
	{
		return (thisSpell) ? thisSpell->GetMagickaCost() : 0;
	}

	UInt32 GetEffectiveMagickaCost(SpellItem* thisSpell, Character* caster)
	{
		if (!thisSpell)
			return 0;

		return CALL_MEMBER_FN(thisSpell,GetEffectiveMagickaCost)(caster);
	}
}

namespace magicItemUtils
{
	UInt32 GetNumEffects(MagicItem* thisMagic)
	{
		return (thisMagic) ? thisMagic->effectItemList.count : 0;
	}

	float GetNthEffectMagnitude(MagicItem* thisMagic, UInt32 index)
	{
		if (!thisMagic)
			return 0.0;

		MagicItem::EffectItem* pEI = NULL;
		thisMagic->effectItemList.GetNthItem(index, pEI);
		return (pEI) ? pEI->magnitude : 0.0;
	}

	UInt32 GetNthEffectArea(MagicItem* thisMagic, UInt32 index)
	{
		if (!thisMagic)
			return 0;

		MagicItem::EffectItem* pEI = NULL;
		thisMagic->effectItemList.GetNthItem(index, pEI);
		return (pEI) ? pEI->area : 0;
	}

	UInt32 GetNthEffectDuration(MagicItem* thisMagic, UInt32 index)
	{
		if (!thisMagic)
			return 0;

		MagicItem::EffectItem* pEI = NULL;
		thisMagic->effectItemList.GetNthItem(index, pEI);
		return (pEI) ? pEI->duration : 0;
	}

	EffectSetting* GetNthEffectMagicEffect(MagicItem* thisMagic, UInt32 index)
	{
		if (!thisMagic)
			return NULL;

		MagicItem::EffectItem* pEI = NULL;
		thisMagic->effectItemList.GetNthItem(index, pEI);
		return (pEI) ? pEI->mgef : NULL;
	}

	UInt32 GetCostliestEffectIndex(MagicItem* thisMagic)
	{
		if (!thisMagic)
			return 0;

		MagicItem::EffectItem * pEI = CALL_MEMBER_FN(thisMagic, GetCostliestEffectItem)(5, false);
		return (pEI) ? thisMagic->effectItemList.GetItemIndex(pEI) : 0;
	}
}

#include "PapyrusVM.h"
#include "PapyrusNativeFunctions.h"

void papyrusSpell::RegisterFuncs(VMClassRegistry* registry)
{
	registry->RegisterFunction(
		new NativeFunction0<SpellItem, float>("GetCastTime", "Spell", papyrusSpell::GetCastTime, registry));

	registry->RegisterFunction(
		new NativeFunction0<SpellItem, BGSPerk*>("GetPerk", "Spell", papyrusSpell::GetPerk, registry));

	registry->RegisterFunction(
		new NativeFunction0<SpellItem, UInt32>("GetNumEffects", "Spell", papyrusSpell::GetNumEffects, registry));

	registry->RegisterFunction(
		new NativeFunction1<SpellItem, float, UInt32>("GetNthEffectMagnitude", "Spell", papyrusSpell::GetNthEffectMagnitude, registry));

	registry->RegisterFunction(
		new NativeFunction1<SpellItem, UInt32, UInt32>("GetNthEffectArea", "Spell", papyrusSpell::GetNthEffectArea, registry));

	registry->RegisterFunction(
		new NativeFunction1<SpellItem, UInt32, UInt32>("GetNthEffectDuration", "Spell", papyrusSpell::GetNthEffectDuration, registry));

	registry->RegisterFunction(
		new NativeFunction1<SpellItem, EffectSetting*, UInt32>("GetNthEffectMagicEffect", "Spell", papyrusSpell::GetNthEffectMagicEffect, registry));

	registry->RegisterFunction(
		new NativeFunction0<SpellItem, UInt32>("GetCostliestEffectIndex", "Spell", papyrusSpell::GetCostliestEffectIndex, registry));

	registry->RegisterFunction(
		new NativeFunction0<SpellItem, UInt32>("GetMagickaCost", "Spell", papyrusSpell::GetMagickaCost, registry));

	registry->RegisterFunction(
		new NativeFunction1<SpellItem, UInt32, Character*>("GetEffectiveMagickaCost", "Spell", papyrusSpell::GetEffectiveMagickaCost, registry));
}