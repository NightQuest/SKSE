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

bool GetAllowDuelWielding(TESCombatStyle* thisCombatStyle)
{
	if (!thisCombatStyle)
		return false;
	return thisCombatStyle->allowDuelWielding ? true : false;
}

void SetAllowDuelWielding(TESCombatStyle* thisCombatStyle, bool bAllow)
{
	if (thisCombatStyle) {
		thisCombatStyle->allowDuelWielding = (bAllow) ? 1 : 0;
	}
}

}
