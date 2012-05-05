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
}