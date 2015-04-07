Scriptname Perk extends Form Hidden


; SKSE additions built 2014-01-29 08:07:50.058000 UTC
Perk Function GetNextPerk() native

int Function GetNumEntries() native

int Function GetNthEntryRank(int n) native
bool Function SetNthEntryRank(int n, int rank) native

int Function GetNthEntryPriority(int n) native
bool Function SetNthEntryPriority(int n, int priority) native

Quest Function GetNthEntryQuest(int n) native
bool Function SetNthEntryQuest(int n, Quest newQuest) native

int Function GetNthEntryStage(int n) native
bool Function SetNthEntryStage(int n, int stage) native

Spell Function GetNthEntrySpell(int n) native
bool Function SetNthEntrySpell(int n, Spell newSpell) native

LeveledItem Function GetNthEntryLeveledList(int n) native
bool Function SetNthEntryLeveledList(int n, LeveledItem lList) native

string Function GetNthEntryText(int n) native
bool Function SetNthEntryText(int n, string newText) native

float Function GetNthEntryValue(int n, int i) native
bool Function SetNthEntryValue(int n, int i, float value) native