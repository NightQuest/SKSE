Scriptname Shout extends Form Hidden

; SKSE additions built 2013-01-07 17:38:10.814000 UTC
WordOfPower Function GetNthWordOfPower(int n) native
Spell Function GetNthSpell(int n) native
float Function GetNthRecoveryTime(int n) native

Function SetNthWordOfPower(int n, WordOfPower aWoop) native
Function SetNthSpell(int n, Spell aSpell) native
Function SetNthRecoveryTime(int n, float time) native