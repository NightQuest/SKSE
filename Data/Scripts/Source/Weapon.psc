Scriptname Weapon extends Form Hidden

; Fire this weapon base object from the specified source
Function Fire(ObjectReference akSource, Ammo akAmmo = None) native


; SKSE additions built 2013-02-20 11:33:33.219000 UTC

int Function GetBaseDamage() native
Function SetBaseDamage(int damage) native

int Function GetCritDamage() native
Function SetCritDamage(int damage) native

float Function GetReach() native
Function SetReach(float reach) native

float Function GetMinRange() native
Function SetMinRange(float minRange) native

float Function GetMaxRange() native
Function SetMaxRange(float maxRange) native

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

; works on the enchantment associated with the weapon
Enchantment Function GetEnchantment() native
Function SetEnchantment(Enchantment e) native

bool Function IsBattleaxe()
	return HasKeywordString("WeapTypeBattleaxe")
endFunction

bool Function IsBow()
	return HasKeywordString("WeapTypeBow")
endFunction

bool Function IsDagger()
	return HasKeywordString("WeapTypeDagger")
endFunction

bool Function IsGreatsword()
	return HasKeywordString("WeapTypeGreatsword")
endFunction

bool Function IsMace()
	return HasKeywordString("WeapTypeMace")
endFunction

bool Function IsStaff()
	return HasKeywordString("WeapTypeStaff")
endFunction

bool Function IsSword()
	return HasKeywordString("WeapTypeSword")
endFunction

bool Function IsWarhammer()
	return HasKeywordString("WeapTypeWarhammer")
endFunction

bool Function IsWarAxe()
	return HasKeywordString("WeapTypeWarAxe")
endFunction
