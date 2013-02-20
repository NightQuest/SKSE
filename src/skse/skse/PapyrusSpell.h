#pragma once

class SpellItem;
class MagicItem;
class BGSPerk;
class EffectSetting;
class VMClassRegistry;
class Character;

namespace papyrusSpell
{
	void RegisterFuncs(VMClassRegistry* registry);

	float GetCastTime(SpellItem* thisSpell);
	BGSPerk* GetPerk(SpellItem* thisSpell);

	// MagicItem funcs
	UInt32 GetNumEffects(SpellItem* thisMagic);
	float GetNthEffectMagnitude(SpellItem* thisMagic, UInt32 index);
	UInt32 GetNthEffectArea(SpellItem* thisMagic, UInt32 index);
	UInt32 GetNthEffectDuration(SpellItem* thisMagic, UInt32 index);
	EffectSetting* GetNthEffectMagicEffect(SpellItem* thisMagic, UInt32 index);
	UInt32 GetCostliestEffectIndex(SpellItem* thisMagic);
	UInt32 GetMagickaCost(SpellItem* thisMagic);
	UInt32 GetEffectiveMagickaCost(SpellItem* thisSpell, Character* caster);
};

namespace magicItemUtils {
	UInt32 GetNumEffects(MagicItem* thisMagic);
	float GetNthEffectMagnitude(MagicItem* thisMagic, UInt32 index);
	UInt32 GetNthEffectArea(MagicItem* thisMagic, UInt32 index);
	UInt32 GetNthEffectDuration(MagicItem* thisMagic, UInt32 index);
	EffectSetting* GetNthEffectMagicEffect(MagicItem* thisMagic, UInt32 index);
	UInt32 GetCostliestEffectIndex(MagicItem* thisMagic);
}
