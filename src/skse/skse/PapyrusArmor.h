#pragma once

class TESObjectARMO;

namespace papyrusArmor
{
	UInt32 GetArmorRating(TESObjectARMO* thisArmor);
	void SetArmorRating(TESObjectARMO* thisArmor, UInt32 nuAR);
	void ModArmorRating(TESObjectARMO* thisArmor, SInt32 modBy);
}
