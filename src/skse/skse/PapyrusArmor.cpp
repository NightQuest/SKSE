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
