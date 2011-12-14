#include "Hooks_Scaleform.h"
#include "SafeWrite.h"
#include "GameMenus.h"

void AddedThisCommand(const FxDelegateArgs & args)
{
	_MESSAGE("added command: numArgs = %d", args.numArgs);

	for(UInt32 i = 0; i < args.numArgs; i++)
	{
		GFxValue	* value = &args.args[i];

		_MESSAGE("%d: %d", value->type);
	}

	MessageBox(NULL, *args.args[0].data.managedString, "", MB_OK);
}

void Console::InstallCallbacks_Hooked(AddCallbackVisitor * visitor)
{
	CALL_MEMBER_FN(this, InstallCallbacks_Orig)(visitor);

	GString	name;

	CALL_MEMBER_FN(&name, Init)("AddedThisCommand");
	visitor->Process(name, AddedThisCommand);
	CALL_MEMBER_FN(&name, Destroy)();
}

void Hook_Scaleform_Install(void)
{
	// AAAAARGGGHHH
	union
	{
		Console::InstallCallbacks_Ptr	fn;
		UInt32							ptr;
	} hook;

	hook.fn = &Console::InstallCallbacks_Hooked;

	SafeWrite32(0x012C08C0, hook.ptr);
}
