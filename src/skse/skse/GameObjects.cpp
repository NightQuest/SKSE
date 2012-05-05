#include "GameObjects.h"

UInt32 TESObjectBOOK::Data::GetSanitizedType(void)
{
	if(type & kType_Spell)
		return kType_Spell;
	if(type & kType_Skill)
		return kType_Skill;

	return kType_None;
}
