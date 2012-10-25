Scriptname Shout extends Form Hidden

; SKSE additions built 2012-10-15 23:22:58.026000 UTC
WordOfPower Function GetNthWordOfPower(int n) native
Spell Function GetNthSpell(int n) native
float Function GetNthRecoveryTime(int n) native

Function SetNthWordOfPower(int n, WordOfPower aWoop) native
Function SetNthSpell(int n, Spell aSpell) native
Function SetNthRecoveryTime(int n, float time) native