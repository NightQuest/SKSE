Scriptname ArmorAddon extends Form Hidden

; returns the model path of the particular model
string Function GetModelPath(bool firstPerson, bool female) native

; sets the model path of the particular model
Function SetModelPath(string path, bool firstPerson, bool female) native

; returns the number of texturesets for the particular model
int Function GetModelNumTextureSets(bool first, bool female) native

; returns the nth textureset for the particular model
TextureSet Function GetModelNthTextureSet(int n, bool first, bool female) native

; sets the nth textureset for the particular model
Function SetModelNthTextureSet(TextureSet texture, int n, bool first, bool female) native

; returns the number of races this armor addon applies to
int Function GetNumAdditionalRaces() native

; returns the nth race this armor addon applies to
Race Function GetNthAdditionalRace(int n) native