#include "Hooks_Papyrus.h"
#include "SafeWrite.h"
#include "PapyrusNativeFunctions.h"
#include "PapyrusVM.h"
#include "GameAPI.h"

typedef void (* _RegisterPapyrusFunctions)(PapyrusClassRegistry ** registry);
_RegisterPapyrusFunctions RegisterPapyrusFunctions = (_RegisterPapyrusFunctions)0x008E2DF0;

bool TestFunctionCallback(PapyrusClassRegistry * registry, UInt32 unk1, UInt32 unk2, float arg)
{
	return false;
}

void RegisterPapyrusFunctions_Hook(PapyrusClassRegistry ** registry)
{
	// call original code
	RegisterPapyrusFunctions(registry);
}

void Hooks_Papyrus_Init(void)
{
	//
}

void Hooks_Papyrus_Commit(void)
{
	WriteRelCall(0x008C3A81, (UInt32)RegisterPapyrusFunctions_Hook);
}

#include "GameForms.h"
#include "GameObjects.h"
#include "GameReferences.h"
#include "GameRTTI.h"

namespace papyrusActor
{
#if 0
	UInt32 GetNumSpells(Actor* thisActor)
	{
		if (!thisActor)
			return 0;

		TESForm* pForm = thisActor->baseForm;
		TESActorBase* pActorBase = DYNAMIC_CAST(pForm, TESForm, TESActorBase);
		if (!pActorBase)
			return 0;

		return pActorBase->spellList.
	}
#endif
}
