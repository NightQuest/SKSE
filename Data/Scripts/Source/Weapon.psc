Scriptname Weapon extends Form Hidden

; Fire this weapon base object from the specified source
Function Fire(ObjectReference akSource, Ammo akAmmo = None) native


; SKSE additions built 2012-04-19 03:58:54.546000 UTC

int Function GetBaseDamage() native
Function SetBaseDamage(int damage) native

float Function GetReach() native
Function SetReach(float reach) native

float Function GetSpeed() native
Function SetSpeed(float speed) native

float Function GetStagger() native
Function SetStagger(float stagger) native

int Function GetWeaponType() native
Function SetWeaponType(int type) native
