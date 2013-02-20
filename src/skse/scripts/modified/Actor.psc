; returns the form for the item worn at the specified slotMask
; use Armor.GetMaskForSlot() to generate appropriate slotMask
Form Function GetWornForm(int slotMask) native

; returns the number of added spells for the actor
Int Function GetSpellCount() native

; returns the specified added spell for the actor
Spell Function GetNthSpell(int n) native

; Updates an Actors meshes (Used for Armor mesh/texture changes and face changes)
Function QueueNiNodeUpdate() native

int Property EquipSlot_Default = 0 AutoReadOnly
int Property EquipSlot_RightHand = 1 AutoReadOnly
int Property EquipSlot_LeftHand = 2 AutoReadOnly

; equips item at the given slot
Function EquipItemEx(Form item, int equipSlot = 0, bool preventUnequip = false, bool equipSound = true) native

; unequips item at the given slot
Function UnequipItemEx(Form item, int equipSlot = 0, bool preventEquip = false) native