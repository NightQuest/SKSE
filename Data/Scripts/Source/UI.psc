Scriptname UI Hidden

; For functions that require a menuName, potential values are
;
;	"Inventory Menu"
;	"Console"
;	"Dialogue Menu"
;	"HUD Menu"
;	"Main Menu"
;	"MessageBoxMenu"
;	"Cursor Menu"
;	"Fader Menu"
;	"Magic Menu"
;	"Top Menu"
;	"Overlay Menu"
;	"Overlay Interaction Menu"
;	"Loading Menu"
;	"Tween Menu"
;	"Barter Menu"
;	"Gift Menu"
;	"Debug Text Menu"
;	"Map Menu"
;	"Lockpicking Menu"
;	"Quantity Menu"
;	"Stats Menu"
;	"Container Menu"
;	"Sleep/Wait Menu"
;	"LevelUp Menu"
;	"Journal Menu"
;	"Book Menu"
;	"Favorites Menu"
;	"RaceSex Menu"
;	"Crafting Menu"
;	"Training Menu"
;	"Mist Menu"
;	"Tutorial Menu"
;	"Credits Menu"
;	"TitleSequence Menu"
;	"Console Native UI Menu"


; Returns if the menu is currently open.
bool Function IsMenuOpen(string menuName) global native

; The target parameter requires one the following prefixes:
;	_global		, for the default namespace;
;	_root		, for the movie root.
;
; To store global data that should be accessed from ActionScript, best use _global.myModName.
; To access and manipulate existing data of a menu, access it via _root.


; Set bool/number/string value at target location.
; If the target object tree leading up to the value doesn't exist yet, it will be created.
;
;	Examples:
;		UI.SetBool("Inventory Menu", "_root.Menu_mc._visible", false)
;		UI.SetNumber("Magic Menu", "_global.myModName.myValue", 42)
;		UI.SetString("Favorites Menu", "_root.Menu_mc.panel.message.text", "My Text")
;
;Function SetBool(string menuName, string target, bool value) global native
;Function SetNumber(string menuName, string target, float value) global native
;Function SetString(string menuName, string target, string value) global native


; Get bool/number/string from target location, or false/0/None if the value doesn't exist.
;
;	Examples:
;		bool	visible	= UI.GetBool("Inventory Menu", "_root.Menu_mc._visible")
;		float	height	= UI.GetNumber("Magic Menu", "_root.Menu_mc._height")
;		string	myTest	= UI.GetString("Favorites Menu", "_global.a.b.c.test")
;
;bool Function GetBool(string menuName, string target) global native
;float Function GetNumber(string menuName, string target) global native
;string Function GetString(string menuName, string target) global native


; Invoke the ActionScript function at given target location,
; with either no parameters, or a single bool/number/string.
;
;	Examples:
;		UI.InvokeString("Inventory Menu", "_global.skse.Log", "Printed to logfile")
;
; To pass more complex parameters, first use the setters to store your data at a
; known location, then invoke your ActionScript function, which may fetch the data
; from there.
;
;	Example:
;		UI.SetBool("Inventory Menu", "_global.myModName.functionData.func1.enabled", true)
;		UI.SetNumber("Inventory Menu", "_global.myModName.functionData.func1.height", 800)
;		UI.SetNumber("Inventory Menu", "_global.myModName.functionData.func1.width", 600)
;		UI.Invoke("Inventory Menu", "_root.Menu_mc.ItemsList.func1")
;
;Function Invoke(string menuName, string target) global native
;Function InvokeBool(string menuName, string target, bool arg) global native
;Function InvokeNumber(string menuName, string target, float arg) global native
;Function InvokeString(string menuName, string target, string arg) global native

