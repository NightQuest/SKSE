#include "skse/PluginAPI.h"
#include "skse/skse_version.h"
#include "skse/SafeWrite.h"
#include "skse/ScaleformCallbacks.h"
#include "skse/ScaleformMovie.h"
#include "skse/GameAPI.h"

IDebugLog	gLog("skse_example_plugin.log");

PluginHandle	g_pluginHandle = kPluginHandle_Invalid;

SKSEScaleformInterface	* scaleform = NULL;

void ApplyPatch(UInt32 base, UInt8 * buf, UInt32 len)
{
	for(UInt32 i = 0; i < len; i++)
		SafeWrite8(base + i, buf[i]);
}

void GameplayPatches(void)
{
	// originally supposed to be 100 /decimal/ but oops
	UInt8	kPickpocketChance[] =
	{
		0xB8, 0x00, 0x01, 0x00, 0x00,	// mov eax, 0x0100
		0xC3							// retn
	};

	ApplyPatch(0x00739F40, kPickpocketChance, sizeof(kPickpocketChance));
}

class SKSEScaleform_ExampleFunction : public GFxFunctionHandler
{
public:
	virtual void	Invoke(Args * args)
	{
		Console_Print("hello world from example plugin");
	}
};

bool RegisterScaleform(GFxMovieView * view, GFxValue * root)
{
	RegisterFunction <SKSEScaleform_ExampleFunction>(root, view, "ExampleFunction");

	return true;
}

extern "C"
{

bool SKSEPlugin_Query(const SKSEInterface * skse, PluginInfo * info)
{
	_MESSAGE("skse_example_plugin");

	// populate info structure
	info->infoVersion =	PluginInfo::kInfoVersion;
	info->name =		"example plugin";
	info->version =		1;

	// store plugin handle so we can identify ourselves later
	g_pluginHandle = skse->GetPluginHandle();

	if(skse->isEditor)
	{
		_MESSAGE("loaded in editor, marking as incompatible");

		return false;
	}
	else if(skse->runtimeVersion != RUNTIME_VERSION_1_3_10_0)
	{
		_MESSAGE("unsupported runtime version %08X", skse->runtimeVersion);

		return false;
	}

	// get the scaleform interface and query its version
	scaleform = (SKSEScaleformInterface *)skse->QueryInterface(kInterface_Scaleform);
	if(!scaleform)
	{
		_MESSAGE("couldn't get scaleform interface");

		return false;
	}

	if(scaleform->interfaceVersion < SKSEScaleformInterface::kInterfaceVersion)
	{
		_MESSAGE("scaleform interface too old (%d expected %d)", scaleform->interfaceVersion, SKSEScaleformInterface::kInterfaceVersion);

		return false;
	}

	// ### do not do anything else in this callback
	// ### only fill out PluginInfo and return true/false

	// supported runtime version
	return true;
}

bool SKSEPlugin_Load(const SKSEInterface * skse)
{
	_MESSAGE("load");

	// apply patches to the game here
	GameplayPatches();

	// register scaleform callbacks
	scaleform->Register("example_plugin", RegisterScaleform);

	return true;
}

};
