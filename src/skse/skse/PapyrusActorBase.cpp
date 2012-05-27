#include "PapyrusActorBase.h"

#include "GameForms.h"
#include "GameObjects.h"
#include "GameReferences.h"
#include "GameExtraData.h"
#include "GameRTTI.h"

namespace papyrusActorBase
{
	TESCombatStyle* GetCombatStyle(TESNPC* thisNPC)
	{
		return thisNPC ? thisNPC->combatStyle : NULL;
	}

	void SetCombatStyle(TESNPC* thisNPC, TESCombatStyle* cs)
	{
		if (thisNPC && cs) {
			thisNPC->combatStyle = cs;
		}
	}

	BGSOutfit* GetOutfit(TESNPC* thisNPC, bool bSleepOutfit)
	{
		if (!thisNPC)
			return NULL;
		return (bSleepOutfit) ? thisNPC->sleepOutfit : thisNPC->defaultOutfit;
	}

	void SetClass(TESNPC* thisNPC, TESClass* nuClass)
	{
		if (thisNPC && nuClass) {
			thisNPC->npcClass = nuClass;
		}
	}

	float GetWeight(TESNPC* thisNPC)
	{
		return (thisNPC) ? thisNPC->weight : 0.0;
	}

	void SetWeight(TESNPC* thisNPC, float weight)
	{
		if (thisNPC) {
			thisNPC->weight = weight;
			// Invoke Actor Member that updates FaceGen (SetNPCWeight should have it)
			// Alternatively there is probably a member that already does this as the race menu needs a way to do the same thing
		}
	}

	UInt32 GetNumHeadParts(TESNPC* thisNPC)
	{
		return thisNPC ? thisNPC->numHeadParts : 0;
	}

	TESForm* GetNthHeadPart(TESNPC* thisNPC, UInt32 n)
	{
		if (!thisNPC || n >= thisNPC->numHeadParts)
			return NULL;

		return thisNPC->headparts[n];
	}

	void SetNthHeadPart(TESNPC* thisNPC, TESForm* form, UInt32 n )
	{
		if (thisNPC  && n < thisNPC->numHeadParts) {
			BGSHeadPart* headPart = DYNAMIC_CAST(form, TESForm, BGSHeadPart);
			if (headPart) {
				thisNPC->headparts[n] = headPart;
				// Invoke Actor Member that updates FaceGen for head parts
				// Alternatively there is probably a member that already does this as the race menu needs a way to do the same thing
			}
		}
	}

	float GetFaceMorph(TESNPC* thisNPC, UInt32 index)
	{
		return (thisNPC && index < TESNPC::FaceMorphs::kNumOptions) ? thisNPC->faceMorph->option[index] : 0.0;
	}

	void SetFaceMorph(TESNPC* thisNPC, float value, UInt32 index)
	{
		if (thisNPC && index < TESNPC::FaceMorphs::kNumOptions) {
			thisNPC->faceMorph->option[index] = value;
			// Invoke Actor Member that updates FaceGen (SetNPCWeight should have it)
			// Alternatively there is probably a member that already does this as the race menu needs a way to do the same thing
		}
	}

	UInt32 GetFacePreset(TESNPC* thisNPC, UInt32 index)
	{
		return (thisNPC && index < TESNPC::FaceMorphs::kNumPresets) ? thisNPC->faceMorph->presets[index] : 0;
	}

	void SetFacePreset(TESNPC* thisNPC, UInt32 value, UInt32 index)
	{
		if (thisNPC && index < TESNPC::FaceMorphs::kNumPresets) {
			thisNPC->faceMorph->presets[index] = value;
			// Invoke Actor Member that updates FaceGen for presets
			// Alternatively there is probably a member that already does this as the race menu needs a way to do the same thing
		}
	}

	// Hair Color
	BGSColorForm* GetHairColor(TESNPC* thisNPC)
	{
		return thisNPC->headData->hairColor;
	}

	void SetHairColor(TESNPC* thisNPC, BGSColorForm* colorForm)
	{
		if(colorForm) {
			thisNPC->headData->hairColor = colorForm;
		}
	}

	UInt32 GetSpellCount(TESNPC* thisNPC)
	{
		return (thisNPC)? thisNPC->spellList.GetSpellCount() : 0;
	}

	SpellItem* GetNthSpell(TESNPC* thisNPC, UInt32 n)
	{
		return (thisNPC) ? thisNPC->spellList.GetNthSpell(n) : NULL;
	}

}

#include "PapyrusVM.h"
#include "PapyrusNativeFunctions.h"

void papyrusActorBase::RegisterFuncs(VMClassRegistry* registry)
{
	registry->RegisterFunction(
		new NativeFunction0 <TESNPC, TESCombatStyle*>("GetCombatStyle", "ActorBase", papyrusActorBase::GetCombatStyle, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESNPC, void, TESCombatStyle*>("SetCombatStyle", "ActorBase", papyrusActorBase::SetCombatStyle, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESNPC, BGSOutfit*, bool>("GetOutfit", "ActorBase", papyrusActorBase::GetOutfit, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESNPC, void, TESClass*>("SetClass", "ActorBase", papyrusActorBase::SetClass, registry));

	// Character Creation Information

	registry->RegisterFunction(
		new NativeFunction0 <TESNPC, float>("GetWeight", "ActorBase", papyrusActorBase::GetWeight, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESNPC, void, float>("SetWeight", "ActorBase", papyrusActorBase::SetWeight, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESNPC, UInt32>("GetNumHeadParts", "ActorBase", papyrusActorBase::GetNumHeadParts, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESNPC, TESForm*, UInt32>("GetNthHeadPart", "ActorBase", papyrusActorBase::GetNthHeadPart, registry));

	registry->RegisterFunction(
		new NativeFunction2 <TESNPC, void, TESForm*, UInt32>("SetNthHeadPart", "ActorBase", papyrusActorBase::SetNthHeadPart, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESNPC, float, UInt32>("GetFaceMorph", "ActorBase", papyrusActorBase::GetFaceMorph, registry));

	registry->RegisterFunction(
		new NativeFunction2 <TESNPC, void, float, UInt32>("SetFaceMorph", "ActorBase", papyrusActorBase::SetFaceMorph, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESNPC, UInt32, UInt32>("GetFacePreset", "ActorBase", papyrusActorBase::GetFacePreset, registry));

	registry->RegisterFunction(
		new NativeFunction2 <TESNPC, void, UInt32, UInt32>("SetFacePreset", "ActorBase", papyrusActorBase::SetFacePreset, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESNPC, BGSColorForm*>("GetHairColor", "ActorBase", papyrusActorBase::GetHairColor, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESNPC, void, BGSColorForm*>("SetHairColor", "ActorBase", papyrusActorBase::SetHairColor, registry));

	registry->RegisterFunction(
		new NativeFunction0 <TESNPC, UInt32>("GetSpellCount", "ActorBase", papyrusActorBase::GetSpellCount, registry));

	registry->RegisterFunction(
		new NativeFunction1 <TESNPC, SpellItem*, UInt32>("GetNthSpell", "ActorBase", papyrusActorBase::GetNthSpell, registry));

}
