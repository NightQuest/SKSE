#include "PapyrusTextureSet.h"

#include "GameObjects.h"

namespace papyrusTextureSet
{
	UInt32 GetNumTexturePaths(BGSTextureSet * thisTextureSet)
	{
		if(thisTextureSet)
			return BGSTextureSet::kNumTextures;

		return 0;
	}

	BSFixedString GetNthTexturePath(BGSTextureSet * thisTextureSet, UInt32 n)
	{
		if(thisTextureSet && n >= 0 && n < BGSTextureSet::kNumTextures)
			return thisTextureSet->texturePaths[n].str;

		return NULL;
	}

	void SetNthTexturePath(BGSTextureSet * thisTextureSet, UInt32 n, BSFixedString texturePath)
	{
		if(thisTextureSet && n >= 0 && n < BGSTextureSet::kNumTextures) {
			thisTextureSet->texturePaths[n].str = texturePath;
		}
	}
}

#include "PapyrusVM.h"
#include "PapyrusNativeFunctions.h"

void papyrusTextureSet::RegisterFuncs(VMClassRegistry* registry)
{
	registry->RegisterFunction(
		new NativeFunction0<BGSTextureSet, UInt32>("GetNumTexturePaths", "TextureSet", papyrusTextureSet::GetNumTexturePaths, registry));

	registry->RegisterFunction(
		new NativeFunction1<BGSTextureSet, BSFixedString, UInt32>("GetNthTexturePath", "TextureSet", papyrusTextureSet::GetNthTexturePath, registry));

	registry->RegisterFunction(
		new NativeFunction2<BGSTextureSet, void, UInt32, BSFixedString>("SetNthTexturePath", "TextureSet", papyrusTextureSet::SetNthTexturePath, registry));
}