#pragma once

class TESForm;
class TESObjectWEAP;
class Actor;
class SpellItem;
class ActiveEffect;
class VMClassRegistry;
class BGSHeadPart;

namespace papyrusActor
{
	void RegisterFuncs(VMClassRegistry* registry);

	TESForm* GetWornForm(Actor* thisActor, UInt32 slot);
	void QueueNiNodeUpdate(Actor* thisActor);
	UInt32 GetSpellCount(Actor* thisActor);
	SpellItem* GetNthSpell(Actor* thisActor, UInt32 n);

#ifdef _AEFFECTS
	UInt32 GetNumActiveEffects(Actor* thisActor);
	ActiveEffect* GetNthActiveEffect(Actor* thisActor, UInt32 n);
#endif

	void EquipItemEx(Actor* thisActor, TESForm* item, SInt32 slotId, bool preventUnequip, bool equipSound);
	void UnequipItemEx(Actor* thisActor, TESForm* item, SInt32 slotId, bool preventEquip);

	void ChangeHeadPart(Actor * thisActor, BGSHeadPart * newPart);
}
