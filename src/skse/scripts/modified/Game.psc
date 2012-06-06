; Get/Set Perk Points
int Function GetPerkPoints() global native
Function SetPerkPoints(int perkPoints) global native
Function ModPerkPoints(int perkPoints) global native

; functions added by BGS in 1.6.87
float Function GetSunPositionX() global native
float Function GetSunPositionY() global native
float Function GetSunPositionZ() global native
Form Function GetFormFromFile(int aiFormID, string asFilename) global native
Function ShowLimitedRaceMenu() global native
Function SetSunGazeImageSpaceModifier(ImageSpaceModifier apImod) global native
bool Function IsPlayerSungazing() global native
