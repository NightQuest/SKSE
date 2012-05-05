Scriptname Weapon extends Form Hidden

; Fire this weapon base object from the specified source
Function Fire(ObjectReference akSource, Ammo akAmmo = None) native


; SKSE additions built 2012-05-03 06:58:27.122000 UTC

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

bool Function IsBattleaxe()
	Keyword WeapTypeBattleaxe = Keyword.GetKeyword("WeapTypeBattleaxe");
	return HasKeyword(WeapTypeBattleaxe)
endFunction

bool Function IsBow()
	Keyword WeapTypeBow = Keyword.GetKeyword("WeapTypeBow");
	return HasKeyword(WeapTypeBow)
endFunction

bool Function IsDagger()
	Keyword WeapTypeDagger = Keyword.GetKeyword("WeapTypeDagger");
	return HasKeyword(WeapTypeDagger)
endFunction

bool Function IsGreatsword()
	Keyword WeapTypeGreatsword = Keyword.GetKeyword("WeapTypeGreatsword");
	return HasKeyword(WeapTypeGreatsword)
endFunction

bool Function IsMace()
	Keyword WeapTypeMace = Keyword.GetKeyword("WeapTypeMace");
	return HasKeyword(WeapTypeMace)
endFunction

bool Function IsSword()
	Keyword WeapTypeSword = Keyword.GetKeyword("WeapTypeSword");
	return HasKeyword(WeapTypeSword)
endFunction

bool Function IsWarhammer()
	Keyword WeapTypeWarhammer = Keyword.GetKeyword("WeapTypeWarhammer");
	return HasKeyword(WeapTypeWarhammer)
endFunction

bool Function IsWarAxe()
	Keyword WeapTypeWarAxe = Keyword.GetKeyword("WeapTypeWarAxe");
	return HasKeyword(WeapTypeWarAxe)
endFunction



