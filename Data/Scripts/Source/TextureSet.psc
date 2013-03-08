Scriptname TextureSet extends Form Hidden

; SKSE additions built 2013-03-04 23:31:36.509000 UTC

; Returns the number of texture paths
int Function GetNumTexturePaths() native

; Returns the path of the texture
string Function GetNthTexturePath(int n) native

; Sets the path of the texture
Function SetNthTexturePath(int n, string texturePath) native