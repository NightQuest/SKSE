#include "PapyrusCombatStyle.h"

#include "GameForms.h"

namespace papyrusCombatStyle
{

	float GetOffensiveMult(TESCombatStyle* thisCombatStyle)
	{
		if (!thisCombatStyle)
			return 0.0;
		return thisCombatStyle->general.offensiveMult;
	}

	void SetOffensiveMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->general.offensiveMult = nuVal;
		}
	}

	float GetDefensiveMult(TESCombatStyle* thisCombatStyle)
	{
		if (!thisCombatStyle)
			return 0.0;
		return thisCombatStyle->general.defensiveMult;
	}

	void SetDefensiveMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->general.defensiveMult = nuVal;
		}
	}

	float GetGroupOffensiveMult(TESCombatStyle* thisCombatStyle)
	{
		if (!thisCombatStyle)
			return 0.0;
		return thisCombatStyle->general.groupOffensiveMult;
	}

	void SetGroupOffensiveMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->general.groupOffensiveMult = nuVal;
		}
	}

	float GetMeleeMult(TESCombatStyle* thisCombatStyle)
	{
		if (!thisCombatStyle)
			return 0.0;
		return thisCombatStyle->general.meleeMult;
	}

	void SetMeleeMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->general.meleeMult = nuVal;
		}
	}

	float GetRangedMult(TESCombatStyle* thisCombatStyle)
	{
		if (!thisCombatStyle)
			return 0.0;
		return thisCombatStyle->general.rangedMult;
	}

	void SetRangedMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->general.rangedMult = nuVal;
		}
	}

	float GetMagicMult(TESCombatStyle* thisCombatStyle)
	{
		if (!thisCombatStyle)
			return 0.0;
		return thisCombatStyle->general.magicMult;
	}

	void SetMagicMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->general.magicMult = nuVal;
		}
	}

	float GetShoutMult(TESCombatStyle* thisCombatStyle)
	{
		if (!thisCombatStyle)
			return 0.0;
		return thisCombatStyle->general.shoutMult;
	}

	void SetShoutMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->general.shoutMult = nuVal;
		}
	}

	float GetStaffMult(TESCombatStyle* thisCombatStyle)
	{
		if (!thisCombatStyle)
			return 0.0;
		return thisCombatStyle->general.staffMult;
	}

	void SetStaffMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->general.staffMult = nuVal;
		}
	}

	float GetUnarmedMult(TESCombatStyle* thisCombatStyle)
	{
		if (!thisCombatStyle)
			return 0.0;
		return thisCombatStyle->general.unarmedMult;
	}

	void SetUnarmedMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->general.unarmedMult = nuVal;
		}
	}

	float GetAvoidThreatChance(TESCombatStyle* thisCombatStyle)
	{
		if (!thisCombatStyle)
			return 0.0;
		return thisCombatStyle->general.avoidThreatChance;
	}

	void SetAvoidThreatChance(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->general.avoidThreatChance = nuVal;
		}
	}

	float GetMeleeAttackStaggeredMult(TESCombatStyle* thisCombatStyle)
	{
		if (!thisCombatStyle)
			return 0.0;
		return thisCombatStyle->melee.attackStaggeredMult;
	}

	void SetMeleeAttackStaggeredMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->melee.attackStaggeredMult = nuVal;
		}
	}

	float GetMeleePowerAttackStaggeredMult(TESCombatStyle* thisCombatStyle)
	{
		if (!thisCombatStyle)
			return 0.0;
		return thisCombatStyle->melee.powerAttackStaggeredMult;
	}

	void SetMeleePowerAttackStaggeredMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->melee.powerAttackStaggeredMult = nuVal;
		}
	}

	float GetMeleePowerAttackBlockingMult(TESCombatStyle* thisCombatStyle)
	{
		if (!thisCombatStyle)
			return 0.0;
		return thisCombatStyle->melee.powerAttackBlockingMult;
	}

	void SetMeleePowerAttackBlockingMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->melee.powerAttackBlockingMult = nuVal;
		}
	}

	float GetMeleeBashMult(TESCombatStyle* thisCombatStyle)
	{
		if (!thisCombatStyle)
			return 0.0;
		return thisCombatStyle->melee.bashMult;
	}

	void SetMeleeBashMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->melee.bashMult = nuVal;
		}
	}

	float GetMeleeBashRecoiledMult(TESCombatStyle* thisCombatStyle)
	{
		if (!thisCombatStyle)
			return 0.0;
		return thisCombatStyle->melee.bashRecoiledMult;
	}

	void SetMeleeBashRecoiledMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->melee.bashRecoiledMult = nuVal;
		}
	}

	float GetMeleeBashAttackMult(TESCombatStyle* thisCombatStyle)
	{
		if (!thisCombatStyle)
			return 0.0;
		return thisCombatStyle->melee.bashAttackMult;
	}

	void SetMeleeBashAttackMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->melee.bashAttackMult = nuVal;
		}
	}

	float GetMeleeBashPowerAttackMult(TESCombatStyle* thisCombatStyle)
	{
		if (!thisCombatStyle)
			return 0.0;
		return thisCombatStyle->melee.bashPowerAttackMult;
	}

	void SetMeleeBashPowerAttackMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->melee.bashPowerAttackMult = nuVal;
		}
	}

	float GetMeleeSpecialAttackMult(TESCombatStyle* thisCombatStyle)
	{
		if (!thisCombatStyle)
			return 0.0;
		return thisCombatStyle->melee.specialAttackMult;
	}

	void SetMeleeSpecialAttackMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->melee.specialAttackMult = nuVal;
		}
	}

	float GetCloseRangeDuelingCircleMult(TESCombatStyle* thisCombatStyle)
	{
		if (!thisCombatStyle)
			return 0.0;
		return thisCombatStyle->closeRange.duelingCircleMult;
	}

	void SetCloseRangeDuelingCircleMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->closeRange.duelingCircleMult = nuVal;
		}
	}

	float GetCloseRangeDuelingFallbackMult(TESCombatStyle* thisCombatStyle)
	{
		if (!thisCombatStyle)
			return 0.0;
		return thisCombatStyle->closeRange.duelingFallbackMult;
	}

	void SetCloseRangeDuelingFallbackMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->closeRange.duelingFallbackMult = nuVal;
		}
	}

	float GetCloseRangeFlankingFlankDistance(TESCombatStyle* thisCombatStyle)
	{
		if (!thisCombatStyle)
			return 0.0;
		return thisCombatStyle->closeRange.flankingFlankDistance;
	}

	void SetCloseRangeFlankingFlankDistance(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->closeRange.flankingFlankDistance = nuVal;
		}
	}

	float GetCloseRangeFlankingStalkTime(TESCombatStyle* thisCombatStyle)
	{
		if (!thisCombatStyle)
			return 0.0;
		return thisCombatStyle->closeRange.flankingStalkTime;
	}

	void SetCloseRangeFlankingStalkTime(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->closeRange.flankingStalkTime = nuVal;
		}
	}

	float GetLongRangeStrafeMult(TESCombatStyle* thisCombatStyle)
	{
		if (!thisCombatStyle)
			return 0.0;
		return thisCombatStyle->longRange.strafeMult;
	}

	void SetLongRangeStrafeMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->longRange.strafeMult = nuVal;
		}
	}


	float GetFlightHoverChance(TESCombatStyle* thisCombatStyle)
	{
		if (!thisCombatStyle)
			return 0.0;
		return thisCombatStyle->flight.hoverChance;
	}

	void SetFlightHoverChance(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->flight.hoverChance = nuVal;
		}
	}

	float GetFlightDiveBombChance(TESCombatStyle* thisCombatStyle)
	{
		if (!thisCombatStyle)
			return 0.0;
		return thisCombatStyle->flight.diveBombChance;
	}

	void SetFlightDiveBombChance(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->flight.diveBombChance = nuVal;
		}
	}

	// undecoded
	float GetFlightFlyingAttackChance(TESCombatStyle* thisCombatStyle)
	{
		if (!thisCombatStyle)
			return 0.0;
		return thisCombatStyle->flight.flyingAttackChance;
	}

	void SetFlightFlyingAttackChance(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->flight.flyingAttackChance = nuVal;
		}
	}

	bool GetAllowDualWielding(TESCombatStyle* thisCombatStyle)
	{
		if (!thisCombatStyle)
			return false;
		return thisCombatStyle->allowDualWielding ? true : false;
	}

	void SetAllowDualWielding(TESCombatStyle* thisCombatStyle, bool bAllow)
	{
		if (thisCombatStyle) {
			thisCombatStyle->allowDualWielding = (bAllow) ? 1 : 0;
		}
	}
}

#include "PapyrusVM.h"
#include "PapyrusNativeFunctions.h"

void papyrusCombatStyle::RegisterFuncs(VMClassRegistry* registry)
{
	registry->RegisterForm(TESCombatStyle::kTypeID, "CombatStyle");

	// get general tab
	registry->RegisterFunction(
		new NativeFunction0 <TESCombatStyle, float>("GetOffensiveMult", "CombatStyle", papyrusCombatStyle::GetOffensiveMult, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESCombatStyle, float>("GetDefensiveMult", "CombatStyle", papyrusCombatStyle::GetDefensiveMult, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESCombatStyle, float>("GetGroupOffensiveMult", "CombatStyle", papyrusCombatStyle::GetGroupOffensiveMult, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESCombatStyle, float>("GetAvoidThreatChance", "CombatStyle", papyrusCombatStyle::GetAvoidThreatChance, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESCombatStyle, float>("GetMeleeMult", "CombatStyle", papyrusCombatStyle::GetMeleeMult, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESCombatStyle, float>("GetRangedMult", "CombatStyle", papyrusCombatStyle::GetRangedMult, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESCombatStyle, float>("GetMagicMult", "CombatStyle", papyrusCombatStyle::GetMagicMult, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESCombatStyle, float>("GetShoutMult", "CombatStyle", papyrusCombatStyle::GetShoutMult, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESCombatStyle, float>("GetStaffMult", "CombatStyle", papyrusCombatStyle::GetStaffMult, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESCombatStyle, float>("GetUnarmedMult", "CombatStyle", papyrusCombatStyle::GetUnarmedMult, registry));

	// set general tab values
	registry->RegisterFunction(
		new NativeFunction1 <TESCombatStyle, void, float>("SetOffensiveMult", "CombatStyle", papyrusCombatStyle::SetOffensiveMult, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESCombatStyle, void, float>("SetDefensiveMult", "CombatStyle", papyrusCombatStyle::SetDefensiveMult, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESCombatStyle, void, float>("SetGroupOffensiveMult", "CombatStyle", papyrusCombatStyle::SetGroupOffensiveMult, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESCombatStyle, void, float>("SetAvoidThreatChance", "CombatStyle", papyrusCombatStyle::SetAvoidThreatChance, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESCombatStyle, void, float>("SetMeleeMult", "CombatStyle", papyrusCombatStyle::SetMeleeMult, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESCombatStyle, void, float>("SetRangedMult", "CombatStyle", papyrusCombatStyle::SetRangedMult, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESCombatStyle, void, float>("SetMagicMult", "CombatStyle", papyrusCombatStyle::SetMagicMult, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESCombatStyle, void, float>("SetShoutMult", "CombatStyle", papyrusCombatStyle::SetShoutMult, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESCombatStyle, void, float>("SetStaffMult", "CombatStyle", papyrusCombatStyle::SetStaffMult, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESCombatStyle, void, float>("SetUnarmedMult", "CombatStyle", papyrusCombatStyle::SetUnarmedMult, registry));

	// get melee tab values
	registry->RegisterFunction(
		new NativeFunction0 <TESCombatStyle, float>("GetMeleeAttackStaggeredMult", "CombatStyle", papyrusCombatStyle::GetMeleeAttackStaggeredMult, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESCombatStyle, float>("GetMeleePowerAttackStaggeredMult", "CombatStyle", papyrusCombatStyle::GetMeleePowerAttackStaggeredMult, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESCombatStyle, float>("GetMeleePowerAttackBlockingMult", "CombatStyle", papyrusCombatStyle::GetMeleePowerAttackBlockingMult, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESCombatStyle, float>("GetMeleeBashMult", "CombatStyle", papyrusCombatStyle::GetMeleeBashMult, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESCombatStyle, float>("GetMeleeBashRecoiledMult", "CombatStyle", papyrusCombatStyle::GetMeleeBashRecoiledMult, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESCombatStyle, float>("GetMeleeBashAttackMult", "CombatStyle", papyrusCombatStyle::GetMeleeBashAttackMult, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESCombatStyle, float>("GetMeleeBashPowerAttackMult", "CombatStyle", papyrusCombatStyle::GetMeleeBashPowerAttackMult, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESCombatStyle, float>("GetMeleeSpecialAttackMult", "CombatStyle", papyrusCombatStyle::GetMeleeSpecialAttackMult, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESCombatStyle, bool>("GetAllowDualWielding", "CombatStyle", papyrusCombatStyle::GetAllowDualWielding, registry));

	// set melee tab values
	registry->RegisterFunction(
		new NativeFunction1 <TESCombatStyle, void, float>("SetMeleeAttackStaggeredMult", "CombatStyle", papyrusCombatStyle::SetMeleeAttackStaggeredMult, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESCombatStyle, void, float>("SetMeleePowerAttackStaggeredMult", "CombatStyle", papyrusCombatStyle::SetMeleePowerAttackStaggeredMult, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESCombatStyle, void, float>("SetMeleePowerAttackBlockingMult", "CombatStyle", papyrusCombatStyle::SetMeleePowerAttackBlockingMult, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESCombatStyle, void, float>("SetMeleeBashMult", "CombatStyle", papyrusCombatStyle::SetMeleeBashMult, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESCombatStyle, void, float>("SetMeleeBashRecoiledMult", "CombatStyle", papyrusCombatStyle::SetMeleeBashRecoiledMult, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESCombatStyle, void, float>("SetMeleeBashAttackMult", "CombatStyle", papyrusCombatStyle::SetMeleeBashAttackMult, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESCombatStyle, void, float>("SetMeleeBashPowerAttackMult", "CombatStyle", papyrusCombatStyle::SetMeleeBashPowerAttackMult, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESCombatStyle, void, float>("SetMeleeSpecialAttackMult", "CombatStyle", papyrusCombatStyle::SetMeleeSpecialAttackMult, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESCombatStyle, void, bool>("SetAllowDualWielding", "CombatStyle", papyrusCombatStyle::SetAllowDualWielding, registry));

	// get Close Range tab values
	registry->RegisterFunction(
		new NativeFunction0 <TESCombatStyle, float>("GetCloseRangeDuelingCircleMult", "CombatStyle", papyrusCombatStyle::GetCloseRangeDuelingCircleMult, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESCombatStyle, float>("GetCloseRangeDuelingFallbackMult", "CombatStyle", papyrusCombatStyle::GetCloseRangeDuelingFallbackMult, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESCombatStyle, float>("GetCloseRangeFlankingFlankDistance", "CombatStyle", papyrusCombatStyle::GetCloseRangeFlankingFlankDistance, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESCombatStyle, float>("GetCloseRangeFlankingStalkTime", "CombatStyle", papyrusCombatStyle::GetCloseRangeFlankingStalkTime, registry));

	// set Close Range tab values
	registry->RegisterFunction(
		new NativeFunction1 <TESCombatStyle, void, float>("SetCloseRangeDuelingCircleMult", "CombatStyle", papyrusCombatStyle::SetCloseRangeDuelingCircleMult, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESCombatStyle, void, float>("SetCloseRangeDuelingFallbackMult", "CombatStyle", papyrusCombatStyle::SetCloseRangeDuelingFallbackMult, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESCombatStyle, void, float>("SetCloseRangeFlankingFlankDistance", "CombatStyle", papyrusCombatStyle::SetCloseRangeFlankingFlankDistance, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESCombatStyle, void, float>("SetCloseRangeFlankingStalkTime", "CombatStyle", papyrusCombatStyle::SetCloseRangeFlankingStalkTime, registry));

	// get/set long range tab values
	registry->RegisterFunction(
		new NativeFunction0 <TESCombatStyle, float>("GetLongRangeStrafeMult", "CombatStyle", papyrusCombatStyle::GetLongRangeStrafeMult, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESCombatStyle, void, float>("SetLongRangeStrafeMult", "CombatStyle", papyrusCombatStyle::SetLongRangeStrafeMult, registry));

	// get flight tab values
	registry->RegisterFunction(
		new NativeFunction0 <TESCombatStyle, float>("GetFlightHoverChance", "CombatStyle", papyrusCombatStyle::GetFlightHoverChance, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESCombatStyle, float>("GetFlightDiveBombChance", "CombatStyle", papyrusCombatStyle::GetFlightDiveBombChance, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESCombatStyle, float>("GetFlightFlyingAttackChance", "CombatStyle", papyrusCombatStyle::GetFlightFlyingAttackChance, registry));

	// set flight tab values
	registry->RegisterFunction(
		new NativeFunction1 <TESCombatStyle, void, float>("SetFlightHoverChance", "CombatStyle", papyrusCombatStyle::SetFlightHoverChance, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESCombatStyle, void, float>("SetFlightDiveBombChance", "CombatStyle", papyrusCombatStyle::SetFlightDiveBombChance, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESCombatStyle, void, float>("SetFlightFlyingAttackChance", "CombatStyle", papyrusCombatStyle::SetFlightFlyingAttackChance, registry));
}
