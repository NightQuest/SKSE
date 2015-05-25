#include "Hooks_Data.h"
#include "SafeWrite.h"
#include "GameData.h"
#include "PluginManager.h"

UInt32 DataHandler::LoadScripts_Hook()
{
	UInt32 ret = CALL_MEMBER_FN(this, LoadScripts)();
	PluginManager::Dispatch_Message(0, SKSEMessagingInterface::kMessage_DataLoaded, (void*)NULL, 0, NULL);
	return ret;
}

void Hooks_Data_Commit(void)
{
	WriteRelCall(0x00699100 + 0x280, GetFnAddr(&DataHandler::LoadScripts_Hook));
}
