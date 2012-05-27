#pragma once

#include "GameTypes.h"

class BGSBaseAlias;
class VMClassRegistry;

namespace papyrusAlias
{
	void RegisterFuncs(VMClassRegistry* registry);

	BSFixedString GetName(BGSBaseAlias* thisAlias);
	UInt32 GetId(BGSBaseAlias* thisAlias);
}
