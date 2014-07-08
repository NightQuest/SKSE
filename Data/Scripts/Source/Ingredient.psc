Scriptname Ingredient extends Form

; Is this ingredient classified as hostile?
bool Function IsHostile() native

; Flags the effect with the given 0 based index as known by the player
Function LearnEffect(int aiIndex) native

; Flags the next unknown effect as known by the player, returning index of effect learned
int Function LearnNextEffect() native

; Flags the all effects as known by the player
Function LearnAllEffects() native

; SKSE additions built 2014-07-08 04:02:05.441000 UTC
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

; determines whether the player knows this effect
bool Function GetIsNthEffectKnown(int index) native