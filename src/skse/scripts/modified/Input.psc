Scriptname Input Hidden

; returns whether a key is pressed
bool Function IsKeyPressed(Int dxKeycode) global native

; taps the specified key
Function TapKey(Int dxKeycode) global native

; holds down the specified key until released
Function HoldKey(Int dxKeycode) global native

; releases the specified key
Function ReleaseKey(Int dxKeycode) global native

; how many keys are pressed
int Function GetNumKeysPressed() global native

; for walking over the pressed keys
int Function GetNthKeyPressed(int n) global native