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