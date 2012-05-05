#pragma once

class TESObjectCELL;
class TESObjectREFR;

namespace papyrusCell
{
	UInt32 GetNumRefs(TESObjectCELL* thisCell, UInt32 formType);
	TESObjectREFR* GetNthRef(TESObjectCELL* thisCell, UInt32 index, UInt32 formType);
}
