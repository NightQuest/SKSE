Scriptname Spell extends Form Hidden

; Cast this spell from an ObjectReference, optionally toward another.
Function Cast(ObjectReference akSource, ObjectReference akTarget=NONE) native

; Cast this spell from an ObjectReference, optionally toward another, and blame it on a particular actor.
Function RemoteCast(ObjectReference akSource, Actor akBlameActor, ObjectReference akTarget=NONE) native

; Is this spell classified as hostile?
bool Function IsHostile() native

; Preload the art for this spell. Useful for spells you equip & unequip on the player.
; Warning: Misuse of this function can lead to erroneous behavior as well as excessive
; memory consumption. It's best to avoid using this. This function will likely be
; deprecated in the future.
Function Preload() native

; Unload the art for this spell. Call this only if you've previously called Preload.
; Warning: Misuse of this function can lead to erroneous behavior including spell art
; being unloaded while in use, and excessive memory consumption. It's best to avoid using this.
; This function will likely be deprecated in the future.
Function Unload() native


; SKSE additions built 2014-07-08 04:02:05.441000 UTC
; return the casting time
float Function GetCastTime() native

; return the perk associated with the spell
Perk Function GetPerk() native

; return the number of the effects
int Function GetNumEffects() native

; return the magnitude of the specified effect
float Function GetNthEffectMagnitude(int index) native

; return the area of the specified effect
int Function GetNthEffectArea(int index) native

; return the duration of the specified effect
int Function GetNthEffectDuration(int index) native

; return the magic effect of the specified effect
MagicEffect Function GetNthEffectMagicEffect(int index) native

; return the index of the costliest effect
int Function GetCostliestEffectIndex() native

; return the base magicka cost of the spell
int Function GetMagickaCost() native

; return the effective magicka cost of the spell for given caster
int Function GetEffectiveMagickaCost(Actor caster) native

; sets the magnitude of the specified effect
Function SetNthEffectMagnitude(int index, float value) native

; sets the area of the specified effect
Function SetNthEffectArea(int index, int value) native

; sets the duration of the specified effect
Function SetNthEffectDuration(int index, int value) native

; Returns the particular equipslot type
EquipSlot Function GetEquipType() native
Function SetEquipType(EquipSlot type) native