#pragma once

class TESSoulGem;
class BGSApparatus;

namespace papyrusSoulGem
{
	UInt8 GetSoulSize(TESSoulGem* thisGem);
	UInt8 GetGemSize(TESSoulGem* thisGem);
}

namespace papyrusApparatus
{
	UInt32 GetQuality(BGSApparatus* thisApparatus);
	void SetQuality(BGSApparatus* thisApparatus, UInt32 nuQuality);
}
