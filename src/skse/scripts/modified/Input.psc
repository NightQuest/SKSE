Scriptname Input Hidden

; returns whether a key is pressed
bool Function IsKeyPressed(Int dxKeycode) global native

; taps the specified key
Function TapKey(Int dxKeycode) global native

; holds down the specified key until released
Function HoldKey(Int dxKeycode) global native

; releases the specified key
Function ReleaseKey(Int dxKeycode) global native

; returns whether a key is held
;bool Function IsKeyHeld(Int dxKeycode) global native

; disables the specified key until enabled again
;Function DisableKey(Int dxKeycode) global native

; enables a disabled key
;Function EnableKey(Int dxKeycode) global native

; returns whether a key is disabled
;bool Function IsKeyEnabled(Int dxKeycode) global native
