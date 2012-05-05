#include "Hooks_Papyrus.h"
#include "SafeWrite.h"
#include "PapyrusNativeFunctions.h"
#include "PapyrusVM.h"
#include "PapyrusArgs.h"
#include "GameAPI.h"

typedef void (* _RegisterPapyrusFunctions)(PapyrusClassRegistry ** registry);
_RegisterPapyrusFunctions RegisterPapyrusFunctions = (_RegisterPapyrusFunctions)0x008E2DE0;

void PapyrusFnTest(StaticFunctionTag * base)
{
	//
}

void RegisterPapyrusFunctions_Hook(PapyrusClassRegistry ** registryPtr)
{
	// call original code
	RegisterPapyrusFunctions(registryPtr);

	PapyrusClassRegistry * registry = *registryPtr;

#if 0
	registry->RegisterFunction(
		new NativeFunction0 <StaticFunctionTag, void>("TestFn", "SKSE", PapyrusFnTest));
#endif
}

void Hooks_Papyrus_Init(void)
{
	//
}

void Hooks_Papyrus_Commit(void)
{
	WriteRelCall(0x008C3A71, (UInt32)RegisterPapyrusFunctions_Hook);
}
