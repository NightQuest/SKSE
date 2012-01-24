#include "GameAPI.h"
#include "Utilities.h"

const _FormHeap_Allocate FormHeap_Allocate = (_FormHeap_Allocate)0x00402410;
const _FormHeap_Free FormHeap_Free = (_FormHeap_Free)0x004023D0;

PlayerCharacter	** g_thePlayer = (PlayerCharacter **)0x01570334;
const UInt32 * g_TlsIndexPtr = (UInt32 *)0x016041B8;

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
	DEFINE_MEMBER_FN(Print, void, 0x009A1BB0, const char * fmt, va_list args);

	ConsoleManager();
	~ConsoleManager();

	static ConsoleManager * GetSingleton(void)
	{
		typedef ConsoleManager * (* _GetSingleton)(void);

		return ((_GetSingleton)0x005803D0)();
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
	return *((InputManager **)0x015510EC);
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
