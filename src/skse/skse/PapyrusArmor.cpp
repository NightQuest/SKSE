#include "PapyrusArmor.h"

#include "GameObjects.h"

namespace papyrusArmor
{
	UInt32 GetArmorRating(TESObjectARMO* thisArmor)
	{	
		if (!thisArmor)
			return 0;
		return thisArmor->armorValTimes100 / 100;
	}

	void SetArmorRating(TESObjectARMO* thisArmor, UInt32 nuAR)
	{
		if (thisArmor) {
			thisArmor->armorValTimes100 = nuAR * 100;
		}
	}

	void ModArmorRating(TESObjectARMO* thisArmor, SInt32 modBy)
	{
		if (thisArmor) {
			UInt32 nuAR = thisArmor->armorValTimes100 + (modBy * 100);
			if (nuAR < 0)
				nuAR = 0;
			thisArmor->armorValTimes100 = nuAR;
		}
	}

	UInt32 GetSlotMask(TESObjectARMO* thisArmor)
	{
		return (thisArmor) ? thisArmor->bipedObject.GetSlotMask() : 0;
	}

	void SetSlotMask(TESObjectARMO* thisArmor, UInt32 slotMask)
	{
		if (thisArmor)
			thisArmor->bipedObject.SetSlotMask(slotMask);
	}

	UInt32 AddSlotToMask(TESObjectARMO* thisArmor, UInt32 slot)
	{
		return (thisArmor) ? thisArmor->bipedObject.AddSlotToMask(slot) : 0;
	
	}
	
	UInt32 RemoveSlotFromMask(TESObjectARMO* thisArmor, UInt32 slot)
	{
		return (thisArmor) ? thisArmor->bipedObject.RemoveSlotFromMask(slot) : 0;
	}

	UInt32 GetMaskForSlot(StaticFunctionTag*, UInt32 slot) 
	{
		if (slot < 29 || slot > 61)
			return 0;

		return (1 << (slot - 30));
	}

}

#include "PapyrusVM.h"
#include "PapyrusNativeFunctions.h"

void papyrusArmor::RegisterFuncs(VMClassRegistry* registry)
{
	registry->RegisterFunction(
		new NativeFunction0 <TESObjectARMO, UInt32>("GetArmorRating", "Armor", papyrusArmor::GetArmorRating, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESObjectARMO, void, UInt32>("SetArmorRating", "Armor", papyrusArmor::SetArmorRating, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESObjectARMO, void, SInt32>("ModArmorRating", "Armor", papyrusArmor::ModArmorRating, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESObjectARMO, UInt32>("GetSlotMask", "Armor", papyrusArmor::GetSlotMask, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESObjectARMO, void, UInt32>("SetSlotMask", "Armor", papyrusArmor::SetSlotMask, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESObjectARMO, UInt32, UInt32>("AddSlotToMask", "Armor", papyrusArmor::AddSlotToMask, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESObjectARMO, UInt32, UInt32>("RemoveSlotFromMask", "Armor", papyrusArmor::RemoveSlotFromMask, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, UInt32, UInt32> ("GetMaskForSlot", "Armor", papyrusArmor::GetMaskForSlot, registry));

}