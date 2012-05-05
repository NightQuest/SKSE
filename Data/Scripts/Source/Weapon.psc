Scriptname Weapon extends Form Hidden

; Fire this weapon base object from the specified source
Function Fire(ObjectReference akSource, Ammo akAmmo = None) native


; SKSE additions built 2012-04-26 19:53:17.541000 UTC

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

; works on the path to the nif file representing the in-game model of the weapon
string Function GetModelPath() native
Function SetModelPath(string path) native

; works on the path to the nif file representing the icon for the weapon in the inventory
string Function GetIconPath() native
Function SetIconPath(string path) native

; works on the path to the file representing the message icon for the weapon
string Function GetMessageIconPath() native
Function SetMessageIconPath(string path) native
