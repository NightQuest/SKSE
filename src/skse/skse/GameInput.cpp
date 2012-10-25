#include "GameInput.h"

bool InputEventDispatcher::IsGamepadEnabled(void)
{
	return (gamepad != NULL) && gamepad->IsEnabled();
}

InputEventDispatcher ** g_inputEventDispatcher = (InputEventDispatcher**) 0x01AD5DD4;

InputManager * InputManager::GetSingleton(void)
{
	return *((InputManager **)0x0128EAB8);
}

UInt8 InputManager::AllowTextInput(bool allow)
{
	if(allow)
	{
		if(allowTextInput == 0xFF)
			_WARNING("InputManager::AllowTextInput: counter overflow");
		else
			allowTextInput++;
	}
	else
	{
		if(allowTextInput == 0)
			_WARNING("InputManager::AllowTextInput: counter underflow");
		else
			allowTextInput--;
	}

	if(IsConsoleMode())
		Console_Print("%s text input, count = %d", allow ? "allowed" : "disallowed", allowTextInput);

	return allowTextInput;
}

UInt32 InputManager::GetMappedKey(const char * name, UInt32 deviceType, UInt32 contextIdx)
{
	ASSERT(contextIdx < kContextCount);

	tArray<InputContext::Mapping> * mappings;
	if (deviceType == kDeviceType_Mouse)
		mappings = &context[contextIdx]->mouseMap;
	else if (deviceType == kDeviceType_Gamepad)
		mappings = &context[contextIdx]->gamepadMap;
	else
		mappings = &context[contextIdx]->keyboardMap;

	for (UInt32 i=0; i < mappings->count; i++)
	{
		InputContext::Mapping m;
		if (!mappings->GetNthItem(i, m))
			break;
		if (m.name == name)
			return m.buttonID;
	}

	// Unbound
	return 0xFF;
}