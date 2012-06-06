; returns the form for the item worn at the specified slotMask
; use Armor.GetMaskForSlot() to generate appropriate slotMask
Form Function GetWornForm(int slotMask) native

; returns the number of added spells for the actor
Int Function GetSpellCount() native

; returns the specified added spell for the actor
Spell Function GetNthSpell(int n) native

Function QueueNiNodeUpdate() native

; functions added by BGS in 1.6.87
Event OnPlayerBowshot(Weapon akWeapon, Ammo akAmmo, float afPower, bool abSunGazing)
EndEvent

bool Function CanFlyHere() native
bool Function IsOnMount() native
Function UnequipItemSlot(int aiSlot) native
Function SetExpressionOverride(int aiMood, int aiStrength) native
Function StartDeferredKill() native
Function SetEyeTexture(TextureSet akNewTexture) native
Function SetAllowFlyingEx(bool abAllowed, bool abAllowCrash, bool abAllowSearch) native
Function DrawWeapon() native
Function StartSneaking() native
Function EndDeferredKill() native

Event OnPlayerLoadGame()
EndEvent

bool Function IsBeingRidden() native
Function SetSubGraphFloatVariable(string asVariableName, float afValue) native
bool Function Dismount() native
Function ClearExpressionOverride() native