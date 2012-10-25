#include "PapyrusHeadPart.h"

#include "GameObjects.h"
 
namespace papyrusHeadPart
{
    UInt32 GetType(BGSHeadPart* thisPart)
    {
		if(!thisPart)
			return 0;

		return thisPart->type;
    }

    UInt32 GetNumExtraParts(BGSHeadPart* thisPart)
    {
		return (thisPart) ? thisPart->extraParts.count : 0;
    }

    BGSHeadPart* GetNthExtraPart(BGSHeadPart* thisPart, UInt32 n)
    {
		BGSHeadPart* headPart;
		if(!thisPart || !thisPart->extraParts.GetNthItem(n, headPart))
			return NULL;

		return headPart;
    }

    bool HasExtraPart(BGSHeadPart* thisPart, BGSHeadPart* extraPart)
    {
		return (thisPart && thisPart->extraParts.GetItemIndex(extraPart) != -1) ? true : false;
    }

    UInt32 GetIndexOfExtraPart(BGSHeadPart* thisPart, BGSHeadPart* extraPart)
    {
		return (thisPart) ? thisPart->extraParts.GetItemIndex(extraPart) : 0;
    }

    BGSListForm* GetValidRaces(BGSHeadPart* thisPart)
    {
		return (thisPart) ? thisPart->validRaces : NULL;
    }

    void SetValidRaces(BGSHeadPart* thisPart, BGSListForm* raceList)
    {
		if(thisPart && raceList) {
			thisPart->validRaces = raceList;
		}
    }
}

#include "PapyrusVM.h"
#include "PapyrusNativeFunctions.h"

void papyrusHeadPart::RegisterFuncs(VMClassRegistry* registry)
{
	registry->RegisterForm(BGSHeadPart::kTypeID, "HeadPart");

	registry->RegisterFunction(
		new NativeFunction0<BGSHeadPart, UInt32>("GetType", "HeadPart", papyrusHeadPart::GetType, registry));

	registry->RegisterFunction(
		new NativeFunction0<BGSHeadPart, UInt32>("GetNumExtraParts", "HeadPart", papyrusHeadPart::GetNumExtraParts, registry));

	registry->RegisterFunction(
		new NativeFunction1<BGSHeadPart, BGSHeadPart*, UInt32>("GetNthExtraPart", "HeadPart", papyrusHeadPart::GetNthExtraPart, registry));

	registry->RegisterFunction(
		new NativeFunction1<BGSHeadPart, bool, BGSHeadPart*>("HasExtraPart", "HeadPart", papyrusHeadPart::HasExtraPart, registry));

	registry->RegisterFunction(
		new NativeFunction1<BGSHeadPart, UInt32, BGSHeadPart*>("GetIndexOfExtraPart", "HeadPart", papyrusHeadPart::GetIndexOfExtraPart, registry));

	registry->RegisterFunction(
		new NativeFunction0<BGSHeadPart, BGSListForm*>("GetValidRaces", "HeadPart", papyrusHeadPart::GetValidRaces, registry));

	registry->RegisterFunction(
		new NativeFunction1<BGSHeadPart, void, BGSListForm*>("SetValidRaces", "HeadPart", papyrusHeadPart::SetValidRaces, registry));
}