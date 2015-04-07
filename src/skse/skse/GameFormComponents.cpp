#include "skse/GameFormComponents.h"

UInt32 BGSBipedObjectForm::AddSlotToMask(UInt32 slot)
{
	data.parts |= slot;
	return data.parts;
}

UInt32 BGSBipedObjectForm::RemoveSlotFromMask(UInt32 slot)
{
	data.parts &= slot;
	return data.parts;
}

UInt32 TESSpellList::GetSpellCount() const
{
	return (unk04) ? unk04->numSpells : 0;
}

SpellItem* TESSpellList::GetNthSpell(UInt32 n) const
{
	if (unk04 && n < unk04->numSpells) {
		return unk04->spells[n];
	}
	else return NULL;
}

UInt32 TESSpellList::GetShoutCount() const
{
	return (unk04) ? unk04->numShouts : 0;
}

TESShout* TESSpellList::GetNthShout(UInt32 n) const
{
	if (unk04 && n < unk04->numShouts) {
		return unk04->shouts[n];
	}
	else return NULL;
}