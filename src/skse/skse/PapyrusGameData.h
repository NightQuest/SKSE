#pragma once

class VMClassRegistry;
struct StaticFunctionTag;

#include "skse/GameTypes.h"

namespace papyrusGameData
{
	void RegisterFuncs(VMClassRegistry* registry);
}