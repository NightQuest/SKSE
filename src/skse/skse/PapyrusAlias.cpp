#include "PapyrusAlias.h"

#include "GameForms.h"

#include "PapyrusVM.h"
#include "PapyrusNativeFunctions.h"

namespace papyrusAlias
{
	BSFixedString GetName(BGSBaseAlias* thisAlias)
	{
		return (thisAlias) ? thisAlias->name.data : NULL;
	}

	UInt32 GetId(BGSBaseAlias* thisAlias)
	{
		return (thisAlias) ? thisAlias->aliasId : -1;
	}

	void RegisterFuncs(VMClassRegistry* registry)
	{
		registry->RegisterFunction(
			new NativeFunction0<BGSBaseAlias, BSFixedString> ("GetName", "Alias", papyrusAlias::GetName, registry));

		registry->RegisterFunction(
			new NativeFunction0<BGSBaseAlias, UInt32> ("GetId", "Alias", papyrusAlias::GetId, registry));
	}
}
