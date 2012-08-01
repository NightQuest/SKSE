#pragma once

struct StaticFunctionTag;
class VMClassRegistry;

#include "GameTypes.h"

namespace papyrusGame
{
	void RegisterFuncs(VMClassRegistry* registry);

	UInt32 GetPerkPoints(StaticFunctionTag*);
	void SetPerkPoints(StaticFunctionTag*, UInt32 perkPoints);
	void ModPerkPoints(StaticFunctionTag*, SInt32 modPerkPointsBy);

	UInt32 GetModCount(StaticFunctionTag*);
	UInt32 GetModByName(StaticFunctionTag*, BSFixedString name);
	BSFixedString GetModName(StaticFunctionTag*, UInt32 index);
	BSFixedString GetModAuthor(StaticFunctionTag*, UInt32 index);
	BSFixedString GetModDescription(StaticFunctionTag*, UInt32 index);
	UInt32 GetModDependencyCount(StaticFunctionTag*, UInt32 index);
	UInt32 GetNthModDependency(StaticFunctionTag*, UInt32 index, UInt32 dep_index);
};
