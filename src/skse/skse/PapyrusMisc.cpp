#include "PapyrusMisc.h"

#include "GameForms.h"
#include "GameObjects.h"

namespace papyrusSoulGem
{
	UInt8 GetSoulSize(TESSoulGem* thisGem)
	{
		if (!thisGem)
			return 0;
		return thisGem->soulSize;
	}

	UInt8 GetGemSize(TESSoulGem* thisGem)
	{
		if (!thisGem)
			return 0;
		return thisGem->gemSize;
	}
}

namespace papyrusApparatus
{
	UInt32 GetQuality(BGSApparatus* thisApparatus)
	{
		if (!thisApparatus)
			return 0;
		return thisApparatus->quality.unk04;
	}

	void SetQuality(BGSApparatus* thisApparatus, UInt32 nuQuality)
	{
		if (thisApparatus) {
			thisApparatus->quality.unk04 = nuQuality;
		}
	}
}
