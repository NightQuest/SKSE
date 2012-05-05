#include "skse/GameFormComponents.h"

// use values listed in CK for better or worse
UInt32 BGSBipedObjectForm::MaskForSlot(UInt32 slot)
{
	if (slot >= 30 && slot <= 61)
		return 1 << (slot - 30);
	else
		return 0;
}