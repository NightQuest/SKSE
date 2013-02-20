#include "skse/GameFormComponents.h"

UInt32 BGSBipedObjectForm::AddSlotToMask(UInt32 slot)
{
	data.parts |= slot;
	return data.parts;
}

UInt32 BGSBipedObjectForm::RemoveSlotFromMask(UInt32 slot)
{
	data.parts &= ~slot;
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

class ItemCounter
{
	UInt32	m_count;
	TESForm	* m_item;

public:
	ItemCounter(TESForm * item) : m_count(0), m_item(item) {}

	bool Accept(TESContainer::Entry * entry)
	{
		if (entry->form == m_item)
			m_count += entry->count;
		return true;
	}

	UInt32 Count() const	{ return m_count; }
};

UInt32 TESContainer::CountItem(TESForm * item) const
{
	ItemCounter v(item);
	Visit(v);
	return v.Count();
}

UInt32 TintMask::ToARGB()
{
	return MAKE_COLOR((UInt32)(alpha * 255), color.red, color.green, color.blue);
}
