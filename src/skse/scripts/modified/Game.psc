; Get/Set Perk Points
int Function GetPerkPoints() global native
Function SetPerkPoints(int perkPoints) global native
Function ModPerkPoints(int perkPoints) global native

; returns the number of active mods
int Function GetModCount() native global

; returns the index of the specified mod
int Function GetModByName(string name) native global

; returns the name of the mod at the specified modIndex
string Function GetModName(int modIndex) native global

; returns the author of the mod at the specified modIndex
string Function GetModAuthor(int modIndex) native global

; returns the description of the mod at the specified modIndex
string Function GetModDescription(int modIndex) native global

; gets the count of mods the specified mod depends upon
int Function GetModDependencyCount(int modIndex) native global

; gets the index of the nth mod dependency of the specfied mod
int Function GetNthModDependency(int modIndex, int n) native global

; functions added by BGS in 1.6.87
float Function GetSunPositionX() global native
float Function GetSunPositionY() global native
float Function GetSunPositionZ() global native
Form Function GetFormFromFile(int aiFormID, string asFilename) global native
Function ShowLimitedRaceMenu() global native
Function SetSunGazeImageSpaceModifier(ImageSpaceModifier apImod) global native
bool Function IsPlayerSungazing() global native
