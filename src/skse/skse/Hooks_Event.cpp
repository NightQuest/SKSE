#include "Hooks_Event.h"

#include "SafeWrite.h"
#include "Utilities.h"
#include "GameInput.h"
#include "GameMenus.h"
#include "PapyrusEvents.h"

PlayerControls * PlayerControls::ctor_Hook(void)
{
	PlayerControls	* result = CALL_MEMBER_FN(this, ctor)();

	MenuManager * mm = MenuManager::GetSingleton();
	if (mm) {
		mm->MenuOpenCloseEventDispatcher()->AddEventSink(&g_menuEventHandler);
	} else {
		_MESSAGE("Failed to register SKSE menuEventHandler!");
	}

	g_modCallbackEventDispatcher.AddEventSink(&g_modCallbackEventHandler);
	g_cameraEventDispatcher.AddEventSink(&g_cameraEventHandler);
	g_crosshairRefEventDispatcher.AddEventSink(&g_crosshairRefEventHandler);

	if (*g_inputEventDispatcher) {
		(*g_inputEventDispatcher)->AddEventSink(&g_inputEventHandler);
	} else {
		_MESSAGE("Failed to register SKSE inputEventHandler");
	}

	return result;
}

void Hooks_Event_Commit(void)
{
	// hook ctor of PlayerControls to register SKSE event sinks
	WriteRelCall(0x0069BFE0 + 0x838, GetFnAddr(&PlayerControls::ctor_Hook));
}
