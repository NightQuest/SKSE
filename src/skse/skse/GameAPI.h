#pragma once

class PlayerCharacter;

// it seems like there are multiple buckets this time - investigate
typedef void * (* _FormHeap_Allocate)(UInt32 size);
extern const _FormHeap_Allocate FormHeap_Allocate;

typedef void (* _FormHeap_Free)(void * ptr);
extern const _FormHeap_Free FormHeap_Free;

extern PlayerCharacter ** g_thePlayer;

void Console_Print(const char * fmt, ...);
bool IsConsoleMode(void);

// 9C
// ControlMap?
// right now we care about this for the UI allowTextInput so it's called InputManager
class InputManager
{
public:
	UInt8	pad00[0x98];	// 00
	UInt8	allowTextInput;	// 98
	UInt8	pad99[3];		// 99

	static InputManager *	GetSingleton(void);

	UInt8	AllowTextInput(bool allow);
};
