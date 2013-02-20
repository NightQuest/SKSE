Scriptname HeadPart extends Form Hidden

int Property kTypeMisc = 0 AutoReadOnly
int Property kTypeFace = 1 AutoReadOnly
int Property kTypeEyes = 2 AutoReadOnly
int Property kTypeHair = 3 AutoReadOnly
int Property kTypeFacialHair = 4 AutoReadOnly
int Property kTypeScar = 5 AutoReadOnly
int Property kTypeBrows = 6 AutoReadOnly

; Returns the head part type
int Function GetType() native

int Function GetNumExtraParts() native
HeadPart Function GetNthExtraPart(int n) native

bool Function HasExtraPart(HeadPart p) native
int Function GetIndexOfExtraPart(HeadPart p) native

; Returns a formlist of the valid races for this head part
FormList Function GetValidRaces() native
Function SetValidRaces(FormList vRaces) native
