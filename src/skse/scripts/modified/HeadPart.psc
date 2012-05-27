Scriptname HeadPart extends Form Hidden

; Returns the head part type
int Function GetType() native

int Function GetNumExtraParts() native
HeadPart Function GetNthExtraPart(int n) native

bool Function HasExtraPart(HeadPart p) native
int Function GetIndexOfExtraPart(HeadPart p) native

; Returns a formlist of the valid races for this head part
FormList Function GetValidRaces() native
Function SetValidRaces(FormList vRaces) native
