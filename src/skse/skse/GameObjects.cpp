#include "GameObjects.h"
#include "GameData.h"

UInt32 TESObjectBOOK::Data::GetSanitizedType(void)
{
	if(flags & kType_Spell)
		return kType_Spell;
	if(flags & kType_Skill)
		return kType_Skill;

	return kType_None;
}

BGSHeadPart * TESNPC::GetHeadPartOverlayByType(UInt32 type)
{
	UInt32 numOverlays = GetNumActorBaseOverlays(this);
	BGSHeadPart ** overlays = GetActorBaseOverlays(this);
	if(overlays) {
		for(UInt32 i = 0; i < numOverlays; i++) {
			if(overlays[i]->type == type) {
				return overlays[i];
			}
		}
	}

	return NULL;
}
