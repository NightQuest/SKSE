#pragma once

class TESObjectARMO;
class VMClassRegistry;

namespace papyrusArmor
{
	void RegisterFuncs(VMClassRegistry* registry);

	UInt32 GetArmorRating(TESObjectARMO* thisArmor);
	void SetArmorRating(TESObjectARMO* thisArmor, UInt32 nuAR);
	void ModArmorRating(TESObjectARMO* thisArmor, SInt32 modBy);
}
