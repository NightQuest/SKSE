#include "PapyrusActor.h"

#include "GameForms.h"
#include "GameObjects.h"
#include "GameReferences.h"
#include "GameExtraData.h"
#include "GameRTTI.h"

class MatchBySlot : public FormMatcher
{
	UInt32 m_mask;
public:
	MatchBySlot(UInt32 slot) : 
	  m_mask(BGSBipedObjectForm::MaskForSlot(slot)) 
	{
		
	}

	bool Matches(TESForm* pForm) const {
		if (pForm) {
			BGSBipedObjectForm* pBip = DYNAMIC_CAST(pForm, TESForm, BGSBipedObjectForm);
			if (pBip) {
				return (pBip->data.parts & m_mask) != 0;
			}
		}
		return false;
	}
};


namespace papyrusActor
{
	TESCombatStyle* GetCombatStyle(Actor* thisActor)
	{
		if (!thisActor)
			return NULL;
		TESNPC* pNPC = DYNAMIC_CAST(thisActor->baseForm, TESForm, TESNPC);
		return pNPC ? pNPC->combatStyle : NULL;
	}

	void SetCombatStyle(Actor* thisActor, TESCombatStyle* cs)
	{
		if (thisActor && cs) {
			TESNPC* pNPC = DYNAMIC_CAST(thisActor->baseForm, TESForm, TESNPC);
			if (pNPC)
				pNPC->combatStyle = cs;
		}
	}

	BGSOutfit* GetOutfit(Actor* thisActor, bool bSleepOutfit)
	{
		if (!thisActor)
			return NULL;
		TESNPC* pNPC = DYNAMIC_CAST(thisActor->baseForm, TESForm, TESNPC);
		if (!pNPC)
			return NULL;
		return (bSleepOutfit) ? pNPC->sleepOutfit : pNPC->defaultOutfit;
	}

	TESClass* GetClass(Actor* thisActor)
	{
		if (!thisActor)
			return NULL;
		TESNPC* pNPC = DYNAMIC_CAST(thisActor->baseForm, TESForm, TESNPC);
		if (!pNPC)
			return NULL;
		return pNPC->npcClass;
	}

	void SetClass(Actor* thisActor, TESClass* nuClass)
	{
		if (thisActor && nuClass) {
			TESNPC* pNPC = DYNAMIC_CAST(thisActor->baseForm, TESForm, TESNPC);
			if (pNPC)
				pNPC->npcClass = nuClass;
		}
	}

	TESForm* GetWornForm(Actor* thisActor, UInt32 mask)
	{
		MatchBySlot matcher(mask);	
		ExtraContainerChanges* pContainerChanges = static_cast<ExtraContainerChanges*>(thisActor->extraData.GetByType(kExtraData_ContainerChanges));
		if (pContainerChanges) {
			EquipData eqD = pContainerChanges->FindEquipped(matcher);
			return eqD.pForm;
		}
		return NULL;
	}
}

#include "PapyrusVM.h"
#include "PapyrusNativeFunctions.h"

void papyrusActor::RegisterFuncs(VMClassRegistry* registry)
{
	registry->RegisterFunction(
		new NativeFunction0 <Actor, TESCombatStyle*>("GetCombatStyle", "Actor", papyrusActor::GetCombatStyle, registry));

	registry->RegisterFunction(
		new NativeFunction1 <Actor, void, TESCombatStyle*>("SetCombatStyle", "Actor", papyrusActor::SetCombatStyle, registry));

	registry->RegisterFunction(
		new NativeFunction1 <Actor, BGSOutfit*, bool>("GetOutfit", "Actor", papyrusActor::GetOutfit, registry));

	registry->RegisterFunction(
		new NativeFunction0 <Actor, TESClass*>("Getclass", "Actor", papyrusActor::GetClass, registry));

	registry->RegisterFunction(
		new NativeFunction1 <Actor, void, TESClass*>("SetClass", "Actor", papyrusActor::SetClass, registry));

	registry->RegisterFunction(
		new NativeFunction1 <Actor, TESForm*, UInt32>("GetWornForm", "Actor", papyrusActor::GetWornForm, registry));
}