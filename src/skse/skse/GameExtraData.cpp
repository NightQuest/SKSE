#include "GameExtraData.h"
#include "GameBSExtraData.h"
#include "GameRTTI.h"
#include "GameAPI.h"
#include "GameData.h"
#include "HashUtil.h"

static const UInt32 s_ExtraHealthVtbl =				0x010791F8;
static const UInt32 s_ExtraChargeVtbl =				0x01079228;
static const UInt32	s_ExtraCountVtbl =				0x010791B8;
static const UInt32 s_ExtraTextDisplayVtbl =		0x01079528;
static const UInt32 s_ExtraSoulVtbl =				0x01079D6C;
static const UInt32 s_ExtraOwnershipVtbl =			0x01079188;
static const UInt32 s_ExtraAliasInstanceArrayVtbl = 0x01079AB8;
static const UInt32 s_ExtraCannotWearVtbl =			0x010791E8;
static const UInt32 s_ExtraHotkeyVtbl =				0x01079258;
static const UInt32 s_ExtraForcedTargetVtbl =		0x010797C0;
static const UInt32 s_ExtraReferenceHandleVtbl =	0x01079740;
static const UInt32 s_ExtraEnchantmentVtbl =		0x01079318;
static const UInt32 s_ExtraRankVtbl =				0x010791A8;
static const UInt32 s_ExtraUniqueIdVtbl =			0x01079548;

ExtraHealth* ExtraHealth::Create() 
{
	ExtraHealth* xHealth = (ExtraHealth*)BSExtraData::Create(sizeof(ExtraHealth), s_ExtraHealthVtbl);
	xHealth->health = 1;
	return xHealth;
}

ExtraCharge* ExtraCharge::Create()
{
	ExtraCharge* xCharge = (ExtraCharge*)BSExtraData::Create(sizeof(ExtraCharge), s_ExtraChargeVtbl);
	xCharge->charge = 0;
	return xCharge;
}

ExtraEnchantment* ExtraEnchantment::Create()
{
	ExtraEnchantment* xEnchantment = (ExtraEnchantment*)BSExtraData::Create(sizeof(ExtraEnchantment), s_ExtraEnchantmentVtbl);
	xEnchantment->enchant = NULL;
	xEnchantment->maxCharge = 0;
	xEnchantment->unk0E = 0;
	return xEnchantment;
}

ExtraCannotWear* ExtraCannotWear::Create() 
{
	ExtraCannotWear* xCannotWear = (ExtraCannotWear*)BSExtraData::Create(sizeof(ExtraCannotWear), s_ExtraCannotWearVtbl);
	xCannotWear->unk08 = 0;
	return xCannotWear;
}

ExtraHotkey* ExtraHotkey::Create()
{
	ExtraHotkey* xHotkey = (ExtraHotkey*)BSExtraData::Create(sizeof(ExtraHotkey), s_ExtraHotkeyVtbl);
	xHotkey->hotkey = -1;
	return xHotkey;
}

ExtraCount* ExtraCount::Create()
{
	ExtraCount* xCount = (ExtraCount*)BSExtraData::Create(sizeof(ExtraCount), s_ExtraCountVtbl);
	return xCount;
}

ExtraSoul* ExtraSoul::Create()
{
	ExtraSoul* xSoul = (ExtraSoul*)BSExtraData::Create(sizeof(ExtraSoul), s_ExtraSoulVtbl);
	return xSoul;
}

ExtraForcedTarget* ExtraForcedTarget::Create()
{
	ExtraForcedTarget* xForcedTarget = (ExtraForcedTarget*)BSExtraData::Create(sizeof(ExtraForcedTarget), s_ExtraForcedTargetVtbl);
	xForcedTarget->handle = (*g_invalidRefHandle);
	return xForcedTarget;
}

ExtraTextDisplayData* ExtraTextDisplayData::Create()
{
	ExtraTextDisplayData* xText = (ExtraTextDisplayData*)BSExtraData::Create(sizeof(ExtraTextDisplayData), s_ExtraTextDisplayVtbl);
	xText->unk14 = -1;
	xText->extraHealthValue = 1.0;
	return xText;
}

ExtraReferenceHandle* ExtraReferenceHandle::Create()
{
	ExtraReferenceHandle* xReference = (ExtraReferenceHandle*)BSExtraData::Create(sizeof(ExtraReferenceHandle), s_ExtraReferenceHandleVtbl);
	return xReference;
}

ExtraRank* ExtraRank::Create() 
{
	ExtraRank* xRank = (ExtraRank*)BSExtraData::Create(sizeof(ExtraRank), s_ExtraRankVtbl);
	xRank->rank = 0;
	return xRank;
}

ExtraUniqueID* ExtraUniqueID::Create() 
{
	ExtraUniqueID* xUniqueId = (ExtraUniqueID*)BSExtraData::Create(sizeof(ExtraUniqueID), s_ExtraUniqueIdVtbl);
	xUniqueId->ownerFormId = 0;
	xUniqueId->uniqueId = 0;
	return xUniqueId;
}

TESObjectREFR * ExtraReferenceHandle::GetReference()
{
	TESObjectREFR * reference = NULL;
	if(handle == (*g_invalidRefHandle) || handle == 0)
		return NULL;

	LookupREFRByHandle(&handle, &reference);
	return reference;
}

TESObjectREFR * ExtraEnableStateParent::GetReference()
{
	TESObjectREFR * reference = NULL;
	if(handle == (*g_invalidRefHandle) || handle == 0)
		return NULL;

	LookupREFRByHandle(&handle, &reference);
	return reference;
}

TESObjectREFR * ExtraForcedTarget::GetReference()
{
	TESObjectREFR * reference = NULL;
	if(handle == (*g_invalidRefHandle) || handle == 0)
		return NULL;

	LookupREFRByHandle(&handle, &reference);
	return reference;
}

const char* ExtraTextDisplayData::GenerateName(TESForm * form, float extraHealthValue)
{
	return CALL_MEMBER_FN(this, GenerateName_Internal)(form, extraHealthValue);
}

struct GetMatchingEquipped
{
	FormMatcher&	m_matcher;
	EquipData		m_found;
	bool			m_isWorn;
	bool			m_isWornLeft;

	GetMatchingEquipped(FormMatcher& matcher, bool isWorn = true, bool isWornLeft = true) : m_matcher(matcher), m_isWorn(isWorn), m_isWornLeft(isWornLeft)
	{
		m_found.pForm = NULL;
		m_found.pExtraData = NULL;
	}

	bool Accept(InventoryEntryData* pEntryData)
	{
		if (pEntryData)
		{
			// quick check - needs an extendData or can't be equipped
			ExtendDataList* pExtendList = pEntryData->extendDataList;
			if (pExtendList && m_matcher.Matches(pEntryData->type))
			{
				for (ExtendDataList::Iterator it = pExtendList->Begin(); !it.End(); ++it)
				{
					BaseExtraList * pExtraDataList = it.Get();

					if (pExtraDataList)
					{
						if ((m_isWorn && pExtraDataList->HasType(kExtraData_Worn)) || (m_isWornLeft && pExtraDataList->HasType(kExtraData_WornLeft)))
						{
							m_found.pForm = pEntryData->type;
							m_found.pExtraData = pExtraDataList;
							return false;
						}
					}
				}
			}
		}
		return true;
	}

	EquipData Found()
	{
		return m_found;
	}
};

EquipData ExtraContainerChanges::FindEquipped(FormMatcher& matcher, bool isWorn, bool isWornLeft) const
{
	FoundEquipData equipData;
	if (data && data->objList) {
		GetMatchingEquipped getEquipped(matcher, isWorn, isWornLeft);
		data->objList->Visit(getEquipped);
		equipData = getEquipped.Found();
	}
	return equipData;
};

class HotkeyDataFinder
{
private:

	// Match by either of those, depending on which ctor was used
	SInt32		m_matchHotkey;
	TESForm *	m_matchForm;

	HotkeyData	m_found;

public:

	HotkeyDataFinder(SInt32 hotkey) : m_matchHotkey(hotkey)
	{
		m_matchForm = NULL;

		m_found.pForm = NULL;
		m_found.pHotkey = NULL;
	}

	HotkeyDataFinder(TESForm * form) : m_matchForm(form)
	{
		m_matchHotkey = -1;

		m_found.pForm = NULL;
		m_found.pHotkey = NULL;
	}

	bool Accept(InventoryEntryData* pEntryData)
	{
		if (!pEntryData)
			return true;

		// If matching by form, skip if this is not the one we're looking for
		if (m_matchForm && m_matchForm != pEntryData->type)
			return true;

		ExtendDataList* pExtendList = pEntryData->extendDataList;
		if (!pExtendList)
			return true;

		SInt32 n = 0;
		BaseExtraList* pExtraDataList = pExtendList->GetNthItem(n);
		while (pExtraDataList)
		{
			if (ExtraHotkey * extraHotkey = static_cast<ExtraHotkey*>(pExtraDataList->GetByType(kExtraData_Hotkey)))
			{
				// Matching by form - found ExtraHotkey?
				if (m_matchForm)
				{
					m_found.pForm = pEntryData->type;
					m_found.pHotkey = extraHotkey;
					return false;
				}
				// Matching by hotkey - compare hotkeys
				else
				{
					if (extraHotkey->hotkey == m_matchHotkey)
					{
						m_found.pForm = pEntryData->type;
						m_found.pHotkey = extraHotkey;
						return false;
					}
				}
			}

			n++;
			pExtraDataList = pExtendList->GetNthItem(n);
		}

		return true;
	}

	HotkeyData& Found()
	{
		return m_found;
	}
};

HotkeyData ExtraContainerChanges::FindHotkey(SInt32 hotkey) const
{
	FoundHotkeyData hotkeyData;
	if (data && data->objList) {
		HotkeyDataFinder getHotkey(hotkey);
		data->objList->Visit(getHotkey);
		hotkeyData = getHotkey.Found();
	}
	return hotkeyData;
}

HotkeyData ExtraContainerChanges::FindHotkey(TESForm * form) const
{
	FoundHotkeyData hotkeyData;
	if (data && data->objList) {
		HotkeyDataFinder getHotkey(form);
		data->objList->Visit(getHotkey);
		hotkeyData = getHotkey.Found();
	}
	return hotkeyData;
}

InventoryEntryData::InventoryEntryData(TESForm * item, UInt32 count)
{
	type = item;
	countDelta = count;
	extendDataList = NULL;
}

InventoryEntryData * InventoryEntryData::Create(TESForm * item, UInt32 count)
{
	InventoryEntryData * p = (InventoryEntryData *)FormHeap_Allocate(sizeof(InventoryEntryData));
	ASSERT(p);

	new (p) InventoryEntryData(item, count);
	p->extendDataList = ExtendDataList::Create();

	return p;
}

void InventoryEntryData::Delete(void)
{
	if (extendDataList)
	{
		extendDataList->Delete();
		extendDataList = NULL;
	}
	FormHeap_Free(this);
}

void InventoryEntryData::GetExtraWornBaseLists(BaseExtraList ** pWornBaseListOut, BaseExtraList ** pWornLeftBaseListOut) const
{
	bool checkWorn = pWornBaseListOut != NULL;
	bool checkWornLeft = pWornLeftBaseListOut != NULL;

	if (!extendDataList)
		return;

	if (!checkWorn && !checkWornLeft)
		return;

	for (ExtendDataList::Iterator it = extendDataList->Begin(); !it.End(); ++it)
	{
		BaseExtraList * xList = it.Get();
		if (!xList)
			continue;

		if (checkWorn && xList->HasType(kExtraData_Worn))
		{
			checkWorn = false;
			*pWornBaseListOut = xList;

			if (!checkWornLeft)
				break;
		}

		if (checkWornLeft && xList->HasType(kExtraData_WornLeft))
		{
			checkWornLeft = false;
			*pWornLeftBaseListOut = xList;

			if (!checkWorn)
				break;
		}
	}
}

InventoryEntryData::EquipData::EquipData() :
	itemCount(0),
	itemExtraList(NULL),
	wornExtraList(NULL),
	wornLeftExtraList(NULL),
	isItemWorn(false),
	isItemWornLeft(false),
	isTypeWorn(false),
	isTypeWornLeft(false)
{
}

void InventoryEntryData::GetEquipItemData(EquipData& stateOut, SInt32 itemId, SInt32 baseCount) const
{
	bool checkDisplayName = itemId != 0;

	// When searching for a specific itemId, start at 0 and count up for every match.
	// When searching for the base item, start at baseCount+delta and subtract 1 for every named item.
	stateOut.itemCount = checkDisplayName ? 0 : (baseCount + countDelta);

	// Search for match based on textDisplayData
	for (ExtendDataList::Iterator it = extendDataList->Begin(); !it.End(); ++it)
	{
		BaseExtraList * xList = it.Get();
		if (!xList)
			continue;

		SInt32 count = 1;

		ExtraCount* xCount = static_cast<ExtraCount*>(xList->GetByType(kExtraData_Count));
		if (xCount)
			count = xCount->count;

		const char * displayName = xList->GetDisplayName(type);

		bool isWorn = xList->HasType(kExtraData_Worn);
		bool isWornLeft = xList->HasType(kExtraData_WornLeft);

		if (isWorn)
		{
			stateOut.isTypeWorn = true;
			stateOut.wornExtraList = xList;
		}

		if (isWornLeft)
		{
			stateOut.isTypeWornLeft = true;
			stateOut.wornLeftExtraList = xList;
		}

		if (checkDisplayName)
		{
			if (displayName)
			{
				SInt32 xItemId = (SInt32) HashUtil::CRC32(displayName, type->formID & 0x00FFFFFF);
				if (itemId == xItemId)
				{
					if (isWorn)
						stateOut.isItemWorn = true;
					else if (isWornLeft)
						stateOut.isItemWornLeft = true;
					else
						stateOut.itemExtraList = xList;

					stateOut.itemCount += count;
				}
			}
		}
		else
		{
			if (!displayName)
			{
				if (isWorn)
					stateOut.isItemWorn = true;
				else if (isWornLeft)
					stateOut.isItemWornLeft = true;
				else
					stateOut.itemExtraList = xList;
			}
			else
			{
				stateOut.itemCount -= count;
			}
		}
	}
}

InventoryEntryData * ExtraContainerChanges::Data::FindItemEntry(TESForm * item) const
{
	typedef EntryDataList::Iterator	EntryDataIterator;

	if (!objList)
		return NULL;

	for (EntryDataIterator it = objList->Begin(); !it.End(); ++it)
	{
		InventoryEntryData * e = it.Get();
		if (e && e->type == item)
			return e;
	}

	return NULL;
}

InventoryEntryData * ExtraContainerChanges::Data::CreateEquipEntryData(TESForm * item)
{
	InventoryEntryData * newEntryData = NULL;

	// Get count from baseForm container
	UInt32 baseCount = 0;
	if (owner && owner->baseForm)
	{
		TESContainer * container = DYNAMIC_CAST(owner->baseForm, TESForm, TESContainer);
		if (container)
			baseCount = container->CountItem(item);
	}

	// Find existing entryData for this item
	InventoryEntryData * curEntryData = FindItemEntry(item);

	if (curEntryData)
	{
		newEntryData = InventoryEntryData::Create(item, baseCount + curEntryData->countDelta);
		
		ExtendDataList * curExtendDataList = curEntryData->extendDataList;
		ExtendDataList * newExtendDataList = newEntryData->extendDataList;

		if (curExtendDataList)
		{
			BaseExtraList * head =  curExtendDataList->GetNthItem(0);
			if (head && (! head->CheckContainerExtraData(true)))
				newExtendDataList->Insert(head);
			else
				newExtendDataList->Append(curExtendDataList->Begin());
		}
		else
		{
			// Native func does this, though the entryData is deleted later anyway...
			newExtendDataList->Delete();
			newEntryData->extendDataList = NULL;
		}
	}
	else
	{
		if (baseCount > 0)
		{
			newEntryData = InventoryEntryData::Create(item, baseCount);
		}
	}

	return newEntryData;
}

void ExtraContainerChanges::Data::GetEquipItemData(InventoryEntryData::EquipData& stateOut, TESForm * item, SInt32 itemId) const
{
	// Get count from baseForm container
	UInt32 baseCount = 0;
	if (owner && owner->baseForm)
	{
		TESContainer * container = DYNAMIC_CAST(owner->baseForm, TESForm, TESContainer);
		if (container)
			baseCount = container->CountItem(item);
	}

	bool matchedBaseForm = false;

	// Test base form name for itemId
	TESFullName* pFullName = DYNAMIC_CAST(item, TESForm, TESFullName);
	if (pFullName)
	{
		const char * name = pFullName->name.data;
		SInt32 baseItemId = (SInt32)HashUtil::CRC32(name, item->formID & 0x00FFFFFF);

		if (baseItemId == itemId)
			matchedBaseForm = true;
	}

	// Find existing entryData for this item
	InventoryEntryData * curEntryData = FindItemEntry(item);

	// Found entryData
	if (curEntryData)
	{
		curEntryData->GetEquipItemData(stateOut, (matchedBaseForm ? 0 : itemId), baseCount);
	}
	else if (matchedBaseForm)
	{
		stateOut.itemCount = baseCount;
	}
}
