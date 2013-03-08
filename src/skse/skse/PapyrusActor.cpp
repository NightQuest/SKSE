#include "PapyrusActor.h"

#include "GameForms.h"
#include "GameData.h"
#include "GameObjects.h"
#include "GameReferences.h"
#include "GameExtraData.h"
#include "GameRTTI.h"
#include "GameThreads.h"

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

bool CanEquipBothHands(Actor* actor, TESForm * item)
{
	BGSEquipType * equipType = DYNAMIC_CAST(item, TESForm, BGSEquipType);
	if (!equipType)
		return false;

	BGSEquipSlot * equipSlot = equipType->GetEquipSlot();
	if (!equipSlot)
		return false;

	// 2H
	if (equipSlot == GetEitherHandSlot())
	{
		return true;
	}
	// 1H
	else if (equipSlot == GetLeftHandSlot() || equipSlot == GetRightHandSlot())
	{
		return (actor->race->data.raceFlags & TESRace::kRace_CanDualWield) && item->IsWeapon();
	}

	return false;
}

BGSEquipSlot * GetEquipSlotById(SInt32 slotId)
{
	enum
	{
		kSlotId_Default = 0,
		kSlotId_Right = 1,
		kSlotId_Left = 2
	};

	if (slotId == kSlotId_Right)
		return GetRightHandSlot();
	else if (slotId == kSlotId_Left)
		return GetLeftHandSlot();
	else
		return NULL;
}

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

	UInt32 GetSpellCount(Actor* thisActor)
	{
		return (thisActor) ? thisActor->addedSpells.spellCount : 0;
	}

	SpellItem* GetNthSpell(Actor* thisActor, UInt32 n)
	{
		if (thisActor && thisActor->addedSpells.spells && n < thisActor->addedSpells.spellCount)
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

	void EquipItemEx(Actor* thisActor, TESForm* item, SInt32 slotId, bool preventUnequip, bool equipSound)
	{
		if (!item)
			return;

		if (!item->Has3D())
			return;

		EquipManager* equipManager = EquipManager::GetSingleton();
		if (!equipManager)
			return;

		ExtraContainerChanges* containerChanges = static_cast<ExtraContainerChanges*>(thisActor->extraData.GetByType(kExtraData_ContainerChanges));
		ExtraContainerChanges::Data* containerData = containerChanges ? containerChanges->data : NULL;
		if (!containerData)
			return;

		// Copy/merge of extraData and container base. Free after use.
		ExtraContainerChanges::EntryData* entryData = containerData->CreateEquipEntryData(item);
		if (!entryData)
			return;

		BGSEquipSlot * targetEquipSlot = GetEquipSlotById(slotId);

		SInt32 itemCount = entryData->countDelta;

		// For ammo, use count, otherwise always equip 1
		SInt32 equipCount = item->IsAmmo() ? itemCount : 1;

		bool isTargetSlotInUse = false;

		// Need at least 1 (maybe 2 for dual wield, checked later)
		bool hasItemMinCount = itemCount > 0;

		BaseExtraList * rightEquipList = NULL;
		BaseExtraList * leftEquipList = NULL;

		BaseExtraList * curEquipList = NULL;
		BaseExtraList * enchantList = NULL;

		if (hasItemMinCount)
		{
			entryData->GetExtraWornBaseLists(&rightEquipList, &leftEquipList);

			// Case 1: Already equipped in both hands.
			if (leftEquipList && rightEquipList)
			{
				isTargetSlotInUse = true;
				curEquipList = (targetEquipSlot == GetLeftHandSlot()) ? leftEquipList : rightEquipList;
				enchantList = NULL;
			}
			// Case 2: Already equipped in right hand.
			else if (rightEquipList)
			{
				isTargetSlotInUse = targetEquipSlot == GetRightHandSlot();
				curEquipList = rightEquipList;
				enchantList = rightEquipList;
			}
			// Case 3: Already equipped in left hand.
			else if (leftEquipList)
			{
				isTargetSlotInUse = targetEquipSlot == GetLeftHandSlot();
				curEquipList = leftEquipList;
				enchantList = NULL;
			}
			// Case 4: Not equipped yet.
			else
			{
				isTargetSlotInUse = false;
				curEquipList = NULL;
				enchantList = entryData->extendDataList->GetNthItem(0);
			}
		}

		// Free temp equip entryData
		entryData->Delete();

		// Normally EquipManager would update CannotWear, if equip is skipped we do it here
		if (isTargetSlotInUse)
		{
			BSExtraData* xCannotWear = curEquipList->GetByType(kExtraData_CannotWear);
			if (xCannotWear && !preventUnequip)
				curEquipList->Remove(kExtraData_CannotWear, xCannotWear);
			else if (!xCannotWear && preventUnequip)
				curEquipList->Add(kExtraData_CannotWear, ExtraCannotWear::Create());

			// Slot in use, nothing left to do
			return;
		}

		// For dual wield, prevent that 1 item can be equipped in two hands if its already equipped
		bool isEquipped = (rightEquipList || leftEquipList);
		if (targetEquipSlot && isEquipped && CanEquipBothHands(thisActor, item))
			hasItemMinCount = itemCount > 1;

		if (!isTargetSlotInUse && hasItemMinCount)
			CALL_MEMBER_FN(equipManager, EquipItem)(thisActor, item, NULL, equipCount, targetEquipSlot, equipSound, preventUnequip, false, NULL);
	}

	void UnequipItemEx(Actor* thisActor, TESForm* item, SInt32 slotId, bool preventEquip)
	{
		if (!item)
			return;

		if (!item->Has3D())
			return;

		EquipManager* equipManager = EquipManager::GetSingleton();
		if (!equipManager)
			return;

		ExtraContainerChanges* containerChanges = static_cast<ExtraContainerChanges*>(thisActor->extraData.GetByType(kExtraData_ContainerChanges));
		ExtraContainerChanges::Data* containerData = containerChanges ? containerChanges->data : NULL;
		if (!containerData)
			return;

		ExtraContainerChanges::EntryData* entryData = containerData->FindItemEntry(item);
		if (!entryData)
			return;

		BGSEquipSlot * targetEquipSlot = GetEquipSlotById(slotId);

		SInt32 itemCount = entryData->countDelta;

		// For ammo, use count, otherwise always equip 1
		SInt32 equipCount = item->IsAmmo() ? itemCount : 1;

		BaseExtraList * rightEquipList = NULL;
		BaseExtraList * leftEquipList = NULL;

		entryData->GetExtraWornBaseLists(&rightEquipList, &leftEquipList);

		bool unequipRight = false;
		bool unequipLeft = false;

		if (targetEquipSlot == GetRightHandSlot())
			unequipRight = true;
		else if (targetEquipSlot == GetLeftHandSlot())
			unequipLeft = true;
		else
			unequipRight = unequipLeft = true;

		if (rightEquipList && unequipRight)
		{
			BSExtraData* xCannotWear = rightEquipList->GetByType(kExtraData_CannotWear);
			if (xCannotWear)
				rightEquipList->Remove(kExtraData_CannotWear, xCannotWear);
			CALL_MEMBER_FN(equipManager, UnequipItem)(thisActor, item, rightEquipList, equipCount, GetRightHandSlot(), true, preventEquip, true, false, NULL);
		}

		if (leftEquipList && unequipLeft)
		{
			BSExtraData* xCannotWear = leftEquipList->GetByType(kExtraData_CannotWear);
			if (xCannotWear)
				leftEquipList->Remove(kExtraData_CannotWear, xCannotWear);
			CALL_MEMBER_FN(equipManager, UnequipItem)(thisActor, item, leftEquipList, equipCount, GetLeftHandSlot(), true, preventEquip, true, false, NULL);
		}
	}

	void QueueNiNodeUpdate(Actor* thisActor)
	{
		Character * pChar = DYNAMIC_CAST(thisActor, Actor, Character);
		if(pChar) {
			CALL_MEMBER_FN(pChar, QueueNiNodeUpdate)(false); // False makes this allow weapons to not be auto holstered apparently
		}
	}

	void ChangeHeadPart(Actor * thisActor, BGSHeadPart * newPart)
	{
		BSTaskPool * taskPool = BSTaskPool::GetSingleton();
		if(taskPool) {
			taskPool->ChangeHeadPart(thisActor, newPart);
		}
	}
}

#include "PapyrusVM.h"
#include "PapyrusNativeFunctions.h"

void papyrusActor::RegisterFuncs(VMClassRegistry* registry)
{
	registry->RegisterFunction(
		new NativeFunction1 <Actor, TESForm*, UInt32>("GetWornForm", "Actor", papyrusActor::GetWornForm, registry));

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

	registry->RegisterFunction(
		new NativeFunction4 <Actor, void, TESForm*, SInt32, bool, bool>("EquipItemEx", "Actor", papyrusActor::EquipItemEx, registry));

	registry->RegisterFunction(
		new NativeFunction3 <Actor, void, TESForm*, SInt32, bool>("UnequipItemEx", "Actor", papyrusActor::UnequipItemEx, registry));

	registry->RegisterFunction(
		new NativeFunction0 <Actor, void>("QueueNiNodeUpdate", "Actor", papyrusActor::QueueNiNodeUpdate, registry));

	registry->RegisterFunction(
		new NativeFunction1 <Actor, void, BGSHeadPart*>("ChangeHeadPart", "Actor", papyrusActor::ChangeHeadPart, registry));
}
