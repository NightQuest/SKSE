
; Container-only functions
int Function GetNumItems() native
Form Function GetNthForm(int index) native
float Function GetTotalItemWeight() native
float Function GetTotalArmorWeight() native

; Tree and Flora only functions
bool Function IsHarvested() native
Function SetHarvested(bool harvested) native

; Tempering
Function SetItemHealthPercent(float health) native

; Charges
float Function GetItemMaxCharge() native
float Function GetItemCharge() native
Function SetItemCharge(float charge) native

Function ResetInventory() native

; NiNode Manipulation
float Function GetNiNodePositionX(string node) native
float Function GetNiNodePositionY(string node) native
float Function GetNiNodePositionZ(string node) native

; Sets the scale of a particular Nif node
float Function GetNiNodeScale(string node) native
Function SetNiNodeScale(string node, float scale) native