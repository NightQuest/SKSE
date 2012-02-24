#include "GameAPI.h"
#include "Utilities.h"

Heap * g_formHeap = (Heap *)0x01390090;

void * FormHeap_Allocate(UInt32 size)
{
	return CALL_MEMBER_FN(g_formHeap, Allocate)(size, 0, false);
}

void FormHeap_Free(void * ptr)
{
	CALL_MEMBER_FN(g_formHeap, Free)(ptr, false);
}

PlayerCharacter	** g_thePlayer = (PlayerCharacter **)0x0137DBEC;
const UInt32 * g_TlsIndexPtr = (UInt32 *)0x0140CED4;

struct TLSData
{
	// thread local storage

	UInt32	pad000[(0x2F8 - 0x000) >> 2];	// 000
	UInt8	consoleMode;					// 2F8
	UInt8	pad2F9[3];						// 2F9
};

static TLSData * GetTLSData()
{
	UInt32 TlsIndex = *g_TlsIndexPtr;
	TLSData * data = NULL;

	__asm {
		mov		ecx,	[TlsIndex]
		mov		edx,	fs:[2Ch]	// linear address of thread local storage array
		mov		eax,	[edx+ecx*4]
		mov		[data], eax
	}

	return data;
}

class ConsoleManager
{
public:
	MEMBER_FN_PREFIX(ConsoleManager);
	DEFINE_MEMBER_FN(Print, void, 0x00837B50, const char * fmt, va_list args);

	ConsoleManager();
	~ConsoleManager();

	static ConsoleManager * GetSingleton(void)
	{
		return *((ConsoleManager **)0x0135FF40);
	}

	void	* scriptContext;	// 00
};

void Console_Print(const char * fmt, ...)
{
	ConsoleManager	* mgr = ConsoleManager::GetSingleton();
	if(mgr)
	{
		va_list	args;

		va_start(args, fmt);

		CALL_MEMBER_FN(mgr, Print)(fmt, args);

		va_end(args);
	}
}

bool IsConsoleMode(void)
{
	return GetTLSData()->consoleMode != 0;
}

InputManager * InputManager::GetSingleton(void)
{
	return *((InputManager **)0x0135FF48);
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
