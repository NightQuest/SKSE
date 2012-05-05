#pragma once

struct StaticFunctionTag;

class VMClassRegistry;

namespace papyrusInput
{
	void RegisterFuncs(VMClassRegistry* registry);

	bool IsKeyPressed(StaticFunctionTag* thisInput, UInt32 dxKeycode);

	void TapKey(StaticFunctionTag* thisInput, UInt32 dxKeycode);

	void HoldKey(StaticFunctionTag* thisInput, UInt32 dxKeycode);
	void ReleaseKey(StaticFunctionTag* thisInput, UInt32 dxKeycode);
	bool IsKeyHeld(StaticFunctionTag* thisInput, UInt32 dxKeycode);

	void DisableKey(StaticFunctionTag* thisInput, UInt32 dxKeyode);
	void EnableKey(StaticFunctionTag* thisInput, UInt32 dxKeycode);
	bool IsKeyDisabled(StaticFunctionTag* thisInput, UInt32 dxKeycode);

	//UInt32 GetNumKeysPressed(Input* thisInput);
	//UInt32 GetKeyPressed(Input* thisInput, UInt32 which);

	//UInt32 GetNumMouseButtonsPressed(Input* thisInput);
	//UInt32 GetMouseButtonPressed(Input* thisInput, UInt32 which);

	//void DisableMouse(Input* thisInput);
	//void EnableMouse(Input* thisInput);
	//bool IsMouseDisabled(Input* thisInput);
}
