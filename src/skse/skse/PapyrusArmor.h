#pragma once

class TESObjectARMO;
struct StaticFunctionTag;
class VMClassRegistry;

namespace papyrusArmor
{
	void RegisterFuncs(VMClassRegistry* registry);

	UInt32 GetArmorRating(TESObjectARMO* thisArmor);
	void SetArmorRating(TESObjectARMO* thisArmor, UInt32 nuAR);
	void ModArmorRating(TESObjectARMO* thisArmor, SInt32 modBy);

	UInt32 GetSlotMask(TESObjectARMO* thisArmor);
	void SetSlotMask(TESObjectARMO* thisArmor, UInt32 slotMask);
	UInt32 AddToSlotMask(TESObjectARMO* thisArmor, UInt32 slotMask);
	UInt32 RemoveFromSlotMask(TESObjectARMO* thisArmor, UInt32 slotMask);

	UInt32 GetMaskForSlot(StaticFunctionTag*, UInt32 slot);
}
