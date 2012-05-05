#include "PapyrusInput.h"

#include "Hooks_DirectInput8Create.h"

namespace papyrusInput
{
	bool IsKeyPressed(Input* thisInput, UInt32 dxKeycode)
	{
		return DIHookControl::GetSingleton().IsKeyPressed(dxKeycode);
	}

	void TapKey(Input* thisInput, UInt32 dxKeycode)
	{
		DIHookControl::GetSingleton().TapKey(dxKeycode);
	}

	void HoldKey(Input* thisInput, UInt32 dxKeycode)
	{
		DIHookControl::GetSingleton().SetKeyHeldState(dxKeycode, true);
	}

	void ReleaseKey(Input* thisInput, UInt32 dxKeycode)
	{
		DIHookControl::GetSingleton().SetKeyHeldState(dxKeycode, false);
	}

	bool IsKeyHeld(Input* thisInput, UInt32 dxKeycode)
	{
		return DIHookControl::GetSingleton().IsKeyHeld(dxKeycode);
	}

	void DisableKey(Input* thisInput, UInt32 dxKeycode)
	{
		DIHookControl::GetSingleton().SetKeyDisableState(dxKeycode, true, 0);
	}

	void EnableKey(Input* thisInput, UInt32 dxKeycode)
	{
		DIHookControl::GetSingleton().SetKeyDisableState(dxKeycode, false, 0);
	}
	
	bool IsKeyDisabled(Input* thisInput, UInt32 dxKeycode)
	{
		return DIHookControl::GetSingleton().IsKeyDisabled(dxKeycode);
	}

	//UInt32 GetNumKeysPressed(Input* thisInput);
	//UInt32 GetKeyPressed(Input* thisInput, UInt32 which);

	//UInt32 GetNumMouseButtonsPressed(Input* thisInput);
	//UInt32 GetMouseButtonPressed(Input* thisInput, UInt32 which);

	//void DisableMouse(Input* thisInput);
	//void EnableMouse(Input* thisInput);
	//bool IsMouseDisabled(Input* thisInput);
}
