#include "GameObjects.h"
#include "GameData.h"
#include "GameRTTI.h"

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

TESNPC * TESNPC::GetRootTemplate()
{
	TESNPC * node = NULL;
	node = nextTemplate;
	if (node) {
		while (node->nextTemplate)
			node = node->nextTemplate;
	}

	return node;
}

void TESObjectARMA::GetNodeName(char * dstBuff, TESObjectREFR * refr, TESObjectARMO * armor, float weightOverride)
{
	float weight = 100.0;
	TESNPC * npc = DYNAMIC_CAST(refr->baseForm, TESForm, TESNPC);
	if(npc && npc->nextTemplate) {
		TESNPC * temp = npc->GetRootTemplate();
		if(temp) {
			weight = temp->weight;
		}
	}
	else
		weight = CALL_MEMBER_FN(refr, GetWeight)();

	weight /= 100.0;
	if(weightOverride >= 0.0) // Determines whether to factor weight into the name, -1 true, 1 false
		weight = weightOverride;

	weight *= 100.0;
	
	UInt32 sex = npc ? CALL_MEMBER_FN(npc, GetSex)() : 0;
	/*sprintf_s(dstBuff, 0x104, "%s (%08X)[%d]/%s (%08X) [%2.0f%%]", 
		this->Unk_32(), // I really have no idea why they used a string here for a boolean value
		this->formID,
		sex,
		armor->Unk_32(), 
		armor->formID, 
		weight);*/
	sprintf_s(dstBuff, MAX_PATH, " (%08X)[%d]/ (%08X) [%2.0f%%]", 
		this->formID,
		sex,
		armor->formID, 
		weight);
}