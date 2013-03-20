Scriptname TextureSet extends Form Hidden

; SKSE additions built 2013-03-19 23:47:10.300000 UTC

; Returns the number of texture paths
int Function GetNumTexturePaths() native

; Returns the path of the texture
string Function GetNthTexturePath(int n) native

; Sets the path of the texture
Function SetNthTexturePath(int n, string texturePath) native