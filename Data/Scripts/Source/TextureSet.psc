Scriptname TextureSet extends Form Hidden

; SKSE additions built 2014-12-23 07:36:08.038000 UTC

; Returns the number of texture paths
int Function GetNumTexturePaths() native

; Returns the path of the texture
string Function GetNthTexturePath(int n) native

; Sets the path of the texture
Function SetNthTexturePath(int n, string texturePath) native