#include "PapyrusCell.h"

#include "GameForms.h"
#include "GameObjects.h"
#include "GameReferences.h"

namespace papyrusCell
{
	UInt32 GetNumRefs(TESObjectCELL* thisCell, UInt32 formType)
	{
		if (!thisCell)
			return 0;

		if (formType == 0)
			return thisCell->objectList.count;

		// match the formType instead
		UInt32 numMatching = 0;
		UInt32 numRefs = thisCell->objectList.count;
		for (UInt32 n = 0; n < numRefs; ++n)
		{
			TESObjectREFR* pRef = NULL;
			thisCell->objectList.GetNthItem(n, pRef);
			if (pRef && pRef->baseForm->formType == formType)
				numMatching++;
		}
		return numMatching;
	}

	TESObjectREFR * GetNthRef(TESObjectCELL * thisCell, UInt32 index, UInt32 formType)
	{
		if (!thisCell)
			return NULL;

		TESObjectREFR* pRef = NULL;
		

		if (formType == 0) {
			thisCell->objectList.GetNthItem(index, pRef);
			return pRef;
		}

		UInt32 numMatching = 0;
		UInt32 numRefs = thisCell->objectList.count;
		for (UInt32 n = 0; n < numRefs; ++n) {
			thisCell->objectList.GetNthItem(n, pRef);
			if (pRef && pRef->baseForm->formType == formType) {
				if (numMatching++ == index) {
					return pRef;
				}
			}
		}
		return NULL;
	}
}
