#pragma once

#include "skse/GameTypes.h"
#include "skse/PapyrusArgs.h"

class BGSListForm;
class VMClassRegistry;

namespace papyrusFormList
{
	void RegisterFuncs(VMClassRegistry* registry);

	VMResultArray<TESForm*> ToArray(BGSListForm * list);
}