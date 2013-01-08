#include "GameObjects.h"

UInt32 TESObjectBOOK::Data::GetSanitizedType(void)
{
	if(flags & kType_Spell)
		return kType_Spell;
	if(flags & kType_Skill)
		return kType_Skill;

	return kType_None;
}
