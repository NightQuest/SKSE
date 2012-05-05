Scriptname Armor extends Form Hidden

; SKSE additions built 2012-04-26 19:53:17.541000 UTC
int Function GetArmorRating() native
int Function GetAR()
	return GetArmorRating()
endFunction

Function SetArmorRating(int armorRating) native
Function SetAR(int armorRating)
	return SetArmorRating(armorRating)
endFunction

Function ModArmorRating(int modBy) native
Function ModAR(int modBy)
	return ModArmorRating(modBy)
endFunction

; Functions and Flags dealing the BipedObject slot values from the CK
; These are the equivalent of 1 << (SlotMask-30).  Basically
; these are a flags where 30 is the first bit, and 61 is the 31st bit.

; returns the slot mask for the armor.
int Function GetSlotMask() native
; sets the slot mask for the armor
Function SetSlotMask(int slotMask) native
; adds the specified slotMask to the armor
int Function AddToSlotMask(int slotMask) native
; removes the specified slot masks from the armor
int Function RemoveFromSlotMask(int slotMask) native

; calculates the equivalent value for the properties below
int Function GetMaskForSlot(int slot) global native

; returns the SlotMask for a single slot from the CK
; can be used with the non-global SlotMask functions above
; and with the Math bit shifting functions
int Property kSlotMask30 =	0x00000001 AutoReadOnly
int Property kSlotMask31 =	0x00000002 AutoReadOnly
int Property kSlotMask32 =	0x00000004 AutoReadOnly
int Property kSlotMask33 =	0x00000008 AutoReadOnly
int Property kSlotMask34 =	0x00000010 AutoReadOnly
int Property kSlotMask35 =	0x00000020 AutoReadOnly
int Property kSlotMask36 =	0x00000040 AutoReadOnly
int Property kSlotMask37 =	0x00000080 AutoReadOnly
int Property kSlotMask38 =	0x00000100 AutoReadOnly
int Property kSlotMask39 =	0x00000200 AutoReadOnly
int Property kSlotMask40 =	0x00000400 AutoReadOnly
int Property kSlotMask41 =	0x00000800 AutoReadOnly
int Property kSlotMask42 =	0x00001000 AutoReadOnly
int Property kSlotMask43 =	0x00002000 AutoReadOnly
int Property kSlotMask44 =	0x00004000 AutoReadOnly
int Property kSlotMask45 =	0x00008000 AutoReadOnly
int Property kSlotMask46 =	0x00010000 AutoReadOnly
int Property kSlotMask47 =	0x00020000 AutoReadOnly
int Property kSlotMask48 =	0x00040000 AutoReadOnly
int Property kSlotMask49 =	0x00080000 AutoReadOnly
int Property kSlotMask50 =	0x00100000 AutoReadOnly
int Property kSlotMask51 =	0x00200000 AutoReadOnly
int Property kSlotMask52 =	0x00400000 AutoReadOnly
int Property kSlotMask53 =	0x00800000 AutoReadOnly
int Property kSlotMask54 =	0x01000000 AutoReadOnly
int Property kSlotMask55 =	0x02000000 AutoReadOnly
int Property kSlotMask56 =	0x04000000 AutoReadOnly
int Property kSlotMask57 =	0x08000000 AutoReadOnly
int Property kSlotMask58 =	0x10000000 AutoReadOnly
int Property kSlotMask59 =	0x20000000 AutoReadOnly
int Property kSlotMask60 =	0x40000000 AutoReadOnly
int Property kSlotMask61 =	0x80000000 AutoReadOnly
