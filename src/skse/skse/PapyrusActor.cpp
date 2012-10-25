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
	  m_mask(slot) 
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

	// PLB:         Set 'bUseFaceGenPreprocessedHeads:General' to 0
	//              before calling this to ensure it regenerates the head,
	//              this can be done in script. For some reason it
	//              completely disregarded the fact I set the INI at all
	//              when using it here directly, alternatively it might be
	//              a desired result to have only the body update without
	//              completely regenerating the head. I believe increasing
	//              weight would cause the head to not match the body
	//              and 'gaps' may occur, so only decreasing would be
	//              recommended. If the face is regenerated all actors
	//              except for the player will lose their face tint.
	//
	void QueueNiNodeUpdate(Actor* thisActor)
	{
		Character * pChar = DYNAMIC_CAST(thisActor, Actor, Character);
		if(pChar) {
			CALL_MEMBER_FN(pChar, QueueNiNodeUpdate)(true);
		}
	}

	UInt32 GetSpellCount(Actor* thisActor)
	{
		return (thisActor) ? thisActor->addedSpells.spellCount : 0;
	}

	SpellItem* GetNthSpell(Actor* thisActor, UInt32 n)
	{
		if (thisActor && n < thisActor->addedSpells.spellCount)
		{
			return thisActor->addedSpells.spells[n];
		}
		else return NULL;
	}

#ifdef _AEFFECTS
	UInt32 GetNumActiveEffects(Actor* thisActor)
	{
		if(thisActor)
		{
			tList<ActiveEffect> * effects = thisActor->magicTarget.GetActiveEffects();
			if(effects) {
				UInt32 count = effects->Count();
				_MESSAGE("Total Effects: %d", count);
				return count;
			}
		}
		return 0;
	}

	ActiveEffect* GetNthActiveEffect(Actor* thisActor, UInt32 n)
	{
		if(thisActor) {
			tList<ActiveEffect> * effects = thisActor->magicTarget.GetActiveEffects();
			if(effects) {
				UInt32 count = effects->Count();
				ActiveEffect * effect = effects->GetNthItem(n);
				_MESSAGE("Dumping n: %d Total: %d", n, count); // Test
				DumpClass(effect, 20);
				return (effects && n < count) ? effect : NULL;
			}
		}
		
		return NULL;
	}
#endif
}

#include "PapyrusVM.h"
#include "PapyrusNativeFunctions.h"

void papyrusActor::RegisterFuncs(VMClassRegistry* registry)
{
	registry->RegisterFunction(
		new NativeFunction1 <Actor, TESForm*, UInt32>("GetWornForm", "Actor", papyrusActor::GetWornForm, registry));

	registry->RegisterFunction(
		new NativeFunction0 <Actor, void>("QueueNiNodeUpdate", "Actor", papyrusActor::QueueNiNodeUpdate, registry));

	registry->RegisterFunction(
		new NativeFunction0 <Actor, UInt32>("GetSpellCount", "Actor", papyrusActor::GetSpellCount, registry));

	registry->RegisterFunction(
		new NativeFunction1 <Actor, SpellItem*, UInt32>("GetNthSpell", "Actor", papyrusActor::GetNthSpell, registry));

#ifdef _AEFFECTS
	registry->RegisterFunction(
		new NativeFunction0 <Actor, UInt32>("GetNumActiveEffects", "Actor", papyrusActor::GetNumActiveEffects, registry));

	registry->RegisterFunction(
		new NativeFunction1 <Actor, ActiveEffect*, UInt32>("GetNthActiveEffect", "Actor", papyrusActor::GetNthActiveEffect, registry));
#endif
}
