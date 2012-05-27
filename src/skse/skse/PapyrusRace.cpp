#include "PapyrusRace.h"

#include "GameObjects.h"
#include "GameFormComponents.h"
#include "GameForms.h"


namespace papyrusRace
{
	UInt32 GetSpellCount(TESRace* thisRace)
	{
		return (thisRace)? thisRace->spellList.GetSpellCount() : 0;
	}

	SpellItem* GetNthSpell(TESRace* thisRace, UInt32 n)
	{
		return (thisRace) ? thisRace->spellList.GetNthSpell(n) : NULL;
	}

}

#include "PapyrusVM.h"
#include "PapyrusNativeFunctions.h"

void papyrusRace::RegisterFuncs(VMClassRegistry* registry)
{

	registry->RegisterFunction(
		new NativeFunction0 <TESRace, UInt32>("GetSpellCount", "Race", papyrusRace::GetSpellCount, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESRace, SpellItem*, UInt32>("GetNthSpell", "Race", papyrusRace::GetNthSpell, registry));

}
