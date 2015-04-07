Scriptname UI Hidden

; For functions that require a menuName, potential values are
;	"InventoryMenu"
;	"Console"
;	"Dialogue Menu"
;	"HUD Menu"
;	"Main Menu"
;	"MessageBoxMenu"
;	"Cursor Menu"
;	"Fader Menu"
;	"MagicMenu"
;	"Top Menu"
;	"Overlay Menu"
;	"Overlay Interaction Menu"
;	"Loading Menu"
;	"TweenMenu"
;	"BarterMenu"
;	"GiftMenu"
;	"Debug Text Menu"
;	"MapMenu"
;	"Lockpicking Menu"
;	"Quantity Menu"
;	"StatsMenu"
;	"ContainerMenu"
;	"Sleep/Wait Menu"
;	"LevelUp Menu"
;	"Journal Menu"
;	"Book Menu"
;	"FavoritesMenu"
;	"RaceSex Menu"
;	"Crafting Menu"
;	"Training Menu"
;	"Mist Menu"
;	"Tutorial Menu"
;	"Credits Menu"
;	"TitleSequence Menu"
;	"Console Native UI Menu"
;	"Kinect Menu"
;
; The target parameter requires one the following prefixes:
;	_global		, for the default namespace;
;	_root		, for the movie root.


; Returns if the menu is currently open.
bool Function IsMenuOpen(string menuName) global native


; Sets bool/number/string value at target location.
; Target value must already exist.
;
;	Examples:
;		UI.SetBool("InventoryMenu", "_root.Menu_mc._visible", false)
;		UI.SetString("FavoritesMenu", "_root.Menu_mc.panel.message.text", "My Text")
;
Function SetBool(string menuName, string target, bool value) global native
Function SetNumber(string menuName, string target, float value) global native
Function SetString(string menuName, string target, string value) global native


; Gets bool/number/string from target location, or false/0/none if the value doesn't exist.
;
;	Examples:
;		bool	visible	= UI.GetBool("Inventory Menu", "_root.Menu_mc._visible")
;		float	height	= UI.GetNumber("Magic Menu", "_root.Menu_mc._height")
;
bool	Function GetBool(string menuName, string target) global native
float	Function GetNumber(string menuName, string target) global native
string	Function GetString(string menuName, string target) global native


; Invokes the ActionScript function at given target location.
;
;	Examples:
;		UI.InvokeString("InventoryMenu", "_global.skse.Log", "Printed to logfile")
;		UI.InvokeStringA("InventoryMenu", "_global.myFunction", myArray)
;
Function Invoke(string menuName, string target) global
	InvokeBool(menuName, target, false)
EndFunction

Function InvokeBool(string menuName, string target, bool arg) global native
Function InvokeNumber(string menuName, string target, float arg) global native
Function InvokeString(string menuName, string target, string arg) global native

Function InvokeBoolA(string menuName, string target, bool[] args) global native
Function InvokeNumberA(string menuName, string target, float[] args) global native
Function InvokeStringA(string menuName, string target, string[] args) global native

; Sends Form data to Scaleform as a Flash object, FormLists included.
Function InvokeForm(string menuName, string target, Form arg) global native