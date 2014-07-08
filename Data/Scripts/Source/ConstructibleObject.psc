Scriptname ConstructibleObject extends MiscObject Hidden

; SKSE additions built 2014-07-08 04:02:05.441000 UTC

; Gets/Sets the result of this recipe
Form Function GetResult() native
Function SetResult(Form result) native

; Gets/Sets the amount of results of this recipe
int Function GetResultQuantity() native
Function SetResultQuantity(int quantity) native

; Gets the number of ingredients
int Function GetNumIngredients() native

; Gets/Sets the Nth ingredient required
Form Function GetNthIngredient(int n) native
Function SetNthIngredient(Form required, int n) native

; Gets/Sets the quantity of Nth ingredient required
int Function GetNthIngredientQuantity(int n) native
Function SetNthIngredientQuantity(int value, int n) native

; Gets/Sets the Workbench keyword (Which apparatus creates this)
Keyword Function GetWorkbenchKeyword() native
Function SetWorkbenchKeyword(Keyword aKeyword) native