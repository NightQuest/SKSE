#include "Hooks_Papyrus.h"
#include "SafeWrite.h"
#include "PapyrusNativeFunctions.h"
#include "PapyrusVM.h"
#include "GameAPI.h"

typedef void (* _RegisterPapyrusFunctions)(PapyrusClassRegistry ** registry);
_RegisterPapyrusFunctions RegisterPapyrusFunctions = (_RegisterPapyrusFunctions)0x008E09C0;

bool TestFunctionCallback(PapyrusClassRegistry * registry, UInt32 unk1, UInt32 unk2, float arg)
{
	return false;
}

void RegisterPapyrusFunctions_Hook(PapyrusClassRegistry ** registry)
{
	// call original code
	RegisterPapyrusFunctions(registry);

	// register our stuff
	(*registry)->RegisterFunction(
		new NativeFunction1_static_bool_float("TestFunction", "SKSE", &TestFunctionCallback, registry));
}

void Hooks_Papyrus_Init(void)
{
	//
}

void Hooks_Papyrus_Commit(void)
{
	WriteRelCall(0x008C1181, (UInt32)RegisterPapyrusFunctions_Hook);
}
