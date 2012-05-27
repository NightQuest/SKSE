#include "PapyrusBook.h"

#include "GameObjects.h"
#include "PapyrusVM.h"
#include "PapyrusNativeFunctions.h"

namespace papyrusBook
{
	UInt32 GetSkill(TESObjectBOOK * thisBook)
	{
		if(thisBook->data.GetSanitizedType() == TESObjectBOOK::Data::kType_Skill)
			return thisBook->data.teaches.skill;

		return 0;
	}

	SpellItem * GetSpell(TESObjectBOOK * thisBook)
	{
		if(thisBook->data.GetSanitizedType() == TESObjectBOOK::Data::kType_Spell)
			return thisBook->data.teaches.spell;

		return NULL;
	}

	void RegisterFuncs(VMClassRegistry* registry)
	{
		//registry->RegisterFunction(
		//	new NativeFunction0<TESObjectBOOK, UInt32>("GetSkill", "Book", papyrusBook::GetSkill, registry));

		registry->RegisterFunction(
			new NativeFunction0<TESObjectBOOK, SpellItem *>("GetSpell", "Book", papyrusBook::GetSpell, registry));
	}
}
