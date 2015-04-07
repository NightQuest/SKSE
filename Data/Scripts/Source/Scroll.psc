Scriptname Scroll extends Form Hidden

; Cast this scroll from an ObjectReference, optionally toward another.
Function Cast(ObjectReference akSource, ObjectReference akTarget=NONE) native	

; SKSE additions built 2013-06-06 02:29:15.175000 UTC
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

; sets the magnitude of the specified effect
Function SetNthEffectMagnitude(int index, float value) native

; sets the area of the specified effect
Function SetNthEffectArea(int index, int value) native

; sets the duration of the specified effect
Function SetNthEffectDuration(int index, int value) native

; Returns the particular equipslot type
EquipSlot Function GetEquipType() native
Function SetEquipType(EquipSlot type) native