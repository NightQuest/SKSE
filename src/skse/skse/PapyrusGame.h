#pragma once

struct StaticFunctionTag;
class VMClassRegistry;

namespace papyrusGame
{
	void RegisterFuncs(VMClassRegistry* registry);

	UInt32 GetPerkPoints(StaticFunctionTag*);
	void SetPerkPoints(StaticFunctionTag*, UInt32 perkPoints);
	void ModPerkPoints(StaticFunctionTag*, SInt32 modPerkPointsBy);
};
