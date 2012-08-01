
; Container-only functions
int Function GetNumItems() native
Form Function GetNthForm(int index) native
float Function GetTotalItemWeight() native
float Function GetTotalArmorWeight() native

; Tree and Flora only functions
bool Function IsHarvested() native

; added by BGS in 1.6.87
bool Function IsDeleted() native

; Tempering
Function SetItemHealthPercent(float health) native

; Charges
float Function GetItemMaxCharge() native
float Function GetItemCharge() native
Function SetItemCharge(float charge) native