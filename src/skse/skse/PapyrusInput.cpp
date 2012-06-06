#include "PapyrusInput.h"

#include "Hooks_DirectInput8Create.h"

namespace papyrusInput
{
	bool IsKeyPressed(StaticFunctionTag* thisInput, UInt32 dxKeycode)
	{
		return DIHookControl::GetSingleton().IsKeyPressed(dxKeycode);
	}

	void TapKey(StaticFunctionTag* thisInput, UInt32 dxKeycode)
	{
		//DIHookControl::GetSingleton().TapKey(dxKeycode);
		DIHookControl::GetSingleton().BufferedKeyTap(dxKeycode);
	}

	void HoldKey(StaticFunctionTag* thisInput, UInt32 dxKeycode)
	{
		//DIHookControl::GetSingleton().SetKeyHeldState(dxKeycode, true);
		DIHookControl::GetSingleton().BufferedKeyPress(dxKeycode);
	}

	void ReleaseKey(StaticFunctionTag* thisInput, UInt32 dxKeycode)
	{
		//DIHookControl::GetSingleton().SetKeyHeldState(dxKeycode, false);
		DIHookControl::GetSingleton().BufferedKeyRelease(dxKeycode);
	}

	bool IsKeyHeld(StaticFunctionTag* thisInput, UInt32 dxKeycode)
	{
		return DIHookControl::GetSingleton().IsKeyHeld(dxKeycode);
	}

	void DisableKey(StaticFunctionTag* thisInput, UInt32 dxKeycode)
	{
		DIHookControl::GetSingleton().SetKeyDisableState(dxKeycode, true, 0);
	}

	void EnableKey(StaticFunctionTag* thisInput, UInt32 dxKeycode)
	{
		DIHookControl::GetSingleton().SetKeyDisableState(dxKeycode, false, 0);
	}
	
	bool IsKeyDisabled(StaticFunctionTag* thisInput, UInt32 dxKeycode)
	{
		return DIHookControl::GetSingleton().IsKeyDisabled(dxKeycode);
	}

	UInt32 GetNumKeysPressed(StaticFunctionTag* thisInput)
	{
		return DIHookControl::GetSingleton().GetNumKeysPressed();
	}

	SInt32 GetNthKeyPressed(StaticFunctionTag* thisInput, UInt32 which)
	{
		return DIHookControl::GetSingleton().GetNthKeyPressed(which);
	}

	//UInt32 GetNumMouseButtonsPressed(StaticFunctionTag* thisInput);
	//UInt32 GetMouseButtonPressed(StaticFunctionTag* thisInput, UInt32 which);

	//void DisableMouse(StaticFunctionTag* thisInput);
	//void EnableMouse(StaticFunctionTag* thisInput);
	//bool IsMouseDisabled(StaticFunctionTag* thisInput);
}

#include "PapyrusVM.h"
#include "PapyrusNativeFunctions.h"

void papyrusInput::RegisterFuncs(VMClassRegistry* registry)
{
	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, bool, UInt32> ("IsKeyPressed", "Input", papyrusInput::IsKeyPressed, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, UInt32> ("TapKey", "Input", papyrusInput::TapKey, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, UInt32> ("HoldKey", "Input", papyrusInput::HoldKey, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, UInt32> ("ReleaseKey", "Input", papyrusInput::ReleaseKey, registry));

	registry->RegisterFunction(
		new NativeFunction0 <StaticFunctionTag, UInt32> ("GetNumKeysPressed", "Input", papyrusInput::GetNumKeysPressed, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, SInt32, UInt32> ("GetNthKeyPressed", "Input", papyrusInput::GetNthKeyPressed, registry));


	//registry->RegisterFunction(
	//	new NativeFunction1 <StaticFunctionTag, bool, UInt32> ("IsKeyHeld", "Input", papyrusInput::IsKeyHeld, registry));

	//registry->RegisterFunction(
	//	new NativeFunction1 <StaticFunctionTag, bool, UInt32> ("IsKeyDisabeld", "Input", papyrusInput::IsKeyDisabled, registry));

	//registry->RegisterFunction(
	//	new NativeFunction1 <StaticFunctionTag, void, UInt32> ("DisableKey", "Input", papyrusInput::DisableKey, registry));

	//registry->RegisterFunction(
	//	new NativeFunction1 <StaticFunctionTag, void, UInt32> ("EnableKey", "Input", papyrusInput::EnableKey, registry));


}
