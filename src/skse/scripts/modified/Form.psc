
; Returns the typecode for this form object
Int Function GetType() native

; returns the form's name, full name if possible
string Function GetName() native

; sets the name of the form
Function SetName(string name) native

; returns the weight of the form
float Function GetWeight() native

; sets the weight of the form
Function SetWeight(float weight) native

; sets the gold value of the form
Function SetGoldValue(int value) native

; returns the number of keywords on the form
int Function GetNumKeywords() native

; returns the keyword at the specified index
Keyword Function GetNthKeyword(int index) native

bool Function HasKeywordString(string s)
	Keyword k = Keyword.GetKeyword(s)
	return HasKeyword(k)
endFunction

; upcoming support to register for OnKeyDown input events
;Function RegisterForKey(int keyCode) native
;Function UnregisterFromKey(int keyCode) native
;Function UnregisterFromAllKeys() native

; Registers for OnMenuOpen and OnMenuClose events for the given menu.
; Registrations have to be refreshed after each game load.
; For a list of valid menu names, see UI.psc.
Function RegisterForMenu(string menuName) native
Function UnregisterFromMenu(string menuName) native
Function UnregisterFromAllMenus() native

Event OnMenuOpen(string menuName)
endEvent

Event OnMenuClose(string menuName)
endEvent

; Registers a custom event callback for given event name.
; Registrations have to be refreshed after each game load.
;
;	Examples:
;		RegisterForModEvent("myCustomEvent", "MyModEventCallback")
;
;	Event signature of custom event callbacks:
;		Event MyModEventCallback(string eventName, string strArg, float numArg, Form sender)
;		endEvent
;
Function RegisterForModEvent(string eventName, string callbackName) native
Function UnregisterFromModEvent(string eventName) native
Function UnregisterFromAllModEvents() native

; Sends custom event with given generic parameters.
Function SendModEvent(string eventName, string strArg = "", float numArg = 0.0) native
