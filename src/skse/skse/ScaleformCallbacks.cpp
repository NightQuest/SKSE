#include "ScaleformCallbacks.h"

char * GFxValue::GetString(void)
{
	if(GetType() != kType_String)
		return NULL;

	if(IsManaged())
		return *data.managedString;
	else
		return data.string;
}

wchar_t * GFxValue::GetWideString(void)
{
	if(GetType() != kType_WideString)
		return NULL;

	if(IsManaged())
		return *data.managedWideString;
	else
		return data.wideString;
}
