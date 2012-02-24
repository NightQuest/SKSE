#include "PapyrusNativeFunctions.h"

NativeFunction1_static_bool_float::NativeFunction1_static_bool_float(const char * fnName, const char * className, Callback callback, PapyrusClassRegistry ** registry)
{
	CALL_MEMBER_FN(this, Impl_ctor)(fnName, className, callback, registry);

	// call empty ctor to init vtable overwritten by the previous call
	new (this) NativeFunction1_static_bool_float();
}

bool NativeFunction1_static_bool_float::Run(UInt32 arg0, PapyrusClassRegistry * registry, UInt32 arg2, VMValue * resultValue, UInt32 arg4)
{
	return CALL_MEMBER_FN(this, Impl_Run)(arg0, registry, arg2, resultValue, arg4);
}
