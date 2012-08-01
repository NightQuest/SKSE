#include "PapyrusUtility.h"

#include "GameForms.h"
#include "GameObjects.h"
#include "GameReferences.h"
#include "GameExtraData.h"
#include "GameRTTI.h"
#include "GameSettings.h"

#include "PapyrusVM.h"
#include "PapyrusNativeFunctions.h"

namespace papyrusUtility
{
	float GetINIFloat(StaticFunctionTag* base, BSFixedString ini)
	{
		Setting * setting = GetINISetting(ini.data);
		if(!setting || setting->GetType() != Setting::kType_Float)
			return 0.0;

		return setting->data.f32;
	}

	UInt32 GetINIInt(StaticFunctionTag* base, BSFixedString ini)
	{
		Setting * setting = GetINISetting(ini.data);
		if(!setting || setting->GetType() != Setting::kType_Integer)
			return 0;

		return setting->data.s32;
	}

	bool GetINIBool(StaticFunctionTag* base, BSFixedString ini)
	{
		Setting * setting = GetINISetting(ini.data);
		if(!setting || setting->GetType() != Setting::kType_Bool)
			return false;

		return setting->data.u8 >= 1 ? true : false;
	}

	BSFixedString GetINIString(StaticFunctionTag* base, BSFixedString ini)
	{
		Setting * setting = GetINISetting(ini.data);
		if(!setting || setting->GetType() != Setting::kType_String)
			return NULL;

		return setting->data.s;
	}

	void SetGameSettingFloat(StaticFunctionTag * base, BSFixedString name, float value)
	{
		SettingCollectionMap	* settings = *g_gameSettingCollection;

		if(settings)
		{
			Setting	* setting = settings->Get(name.data);
			if(setting)
			{
				if(!setting->SetDouble(value))
				{
					_WARNING("SetGameSettingFloat: %s is not a float", name.data);
				}
			}
			else
			{
				_WARNING("SetGameSettingFloat: %s not found", name.data);
			}
		}
	}

	void SetGameSettingInt(StaticFunctionTag * base, BSFixedString name, UInt32 value)
	{
		SettingCollectionMap	* settings = *g_gameSettingCollection;

		if(settings)
		{
			Setting	* setting = settings->Get(name.data);
			if(setting)
			{
				if(setting->GetType() == Setting::kType_Integer)
				{
					setting->data.u32 = value;
				}
				else
				{
					_WARNING("SetGameSettingInt: %s is not an int", name.data);
				}	
			}
			else
			{
				_WARNING("SetGameSettingInt: %s not found", name.data);
			}
		}
	}

	void SetGameSettingBool(StaticFunctionTag * base, BSFixedString name, bool value)
	{
		SettingCollectionMap	* settings = *g_gameSettingCollection;

		if(settings)
		{
			Setting	* setting = settings->Get(name.data);
			if(setting)
			{
				if(setting->GetType() == Setting::kType_Bool)
				{
					setting->data.u8 = value;
				}
				else
				{
					_WARNING("SetGameSettingBool: %s is not a bool", name.data);
				}
			}
			else
			{
				_WARNING("SetGameSettingBool: %s not found", name.data);
			}
		}
	}

	void SetGameSettingString(StaticFunctionTag * base, BSFixedString name, BSFixedString value)
	{
		SettingCollectionMap	* settings = *g_gameSettingCollection;

		if(settings)
		{
			Setting	* setting = settings->Get(name.data);
			if(setting)
			{
				if(!setting->SetString(value.data))
				{
					_WARNING("SetGameSettingString: %s is not a string", name.data);
				}
			}
			else
			{
				_WARNING("SetGameSettingString: %s not found", name.data);
			}
		}
	}
}

void papyrusUtility::RegisterFuncs(VMClassRegistry* registry)
{
	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, float, BSFixedString>("GetINIFloat", "Utility", papyrusUtility::GetINIFloat, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, UInt32, BSFixedString>("GetINIInt", "Utility", papyrusUtility::GetINIInt, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, bool, BSFixedString>("GetINIBool", "Utility", papyrusUtility::GetINIBool, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, BSFixedString, BSFixedString>("GetINIString", "Utility", papyrusUtility::GetINIString, registry));

	registry->RegisterFunction(
		new NativeFunction2 <StaticFunctionTag, void, BSFixedString, float>("SetGameSettingFloat", "Utility", papyrusUtility::SetGameSettingFloat, registry));

	registry->RegisterFunction(
		new NativeFunction2 <StaticFunctionTag, void, BSFixedString, UInt32>("SetGameSettingInt", "Utility", papyrusUtility::SetGameSettingInt, registry));

	registry->RegisterFunction(
		new NativeFunction2 <StaticFunctionTag, void, BSFixedString, bool>("SetGameSettingBool", "Utility", papyrusUtility::SetGameSettingBool, registry));

	registry->RegisterFunction(
		new NativeFunction2 <StaticFunctionTag, void, BSFixedString, BSFixedString>("SetGameSettingString", "Utility", papyrusUtility::SetGameSettingString, registry));
}
