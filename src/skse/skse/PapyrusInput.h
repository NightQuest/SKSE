#pragma once

class Input;

namespace papyrusInput
{
	bool IsKeyPressed(Input* thisInput, UInt32 dxKeycode);

	void TapKey(Input* thisInput, UInt32 dxKeycode);

	void HoldKey(Input* thisInput, UInt32 dxKeycode);
	void ReleaseKey(Input* thisInput, UInt32 dxKeycode);
	bool IsKeyHeld(Input* thisInput, UInt32 dxKeycode);

	void DisableKey(Input* thisInput, UInt32 dxKeyode);
	void EnableKey(Input* thisInput, UInt32 dxKeycode);
	bool IsKeyDisabled(Input* thisInput, UInt32 dxKeycode);

	//UInt32 GetNumKeysPressed(Input* thisInput);
	//UInt32 GetKeyPressed(Input* thisInput, UInt32 which);

	//UInt32 GetNumMouseButtonsPressed(Input* thisInput);
	//UInt32 GetMouseButtonPressed(Input* thisInput, UInt32 which);

	//void DisableMouse(Input* thisInput);
	//void EnableMouse(Input* thisInput);
	//bool IsMouseDisabled(Input* thisInput);
}
