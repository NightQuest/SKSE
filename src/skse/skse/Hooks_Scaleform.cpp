#include "Hooks_Scaleform.h"
#include "Hooks_Gameplay.h"
#include "SafeWrite.h"
#include "Utilities.h"
#include "ScaleformCallbacks.h"
#include "ScaleformMovie.h"
#include "ScaleformAPI.h"
#include "ScaleformExtendedData.h"
#include "GameAPI.h"
#include "GameSettings.h"
#include "GameMenus.h"
#include "PluginManager.h"
#include "skse_version.h"
#include "GameForms.h"
#include "GameObjects.h"
#include "GameReferences.h"
#include "GameRTTI.h"
#include <new>
#include <list>
#include "PapyrusEvents.h"

//// plugin API

struct ScaleformPluginInfo
{
	const char	* name;
	SKSEScaleformInterface::RegisterCallback	callback;
};

typedef std::list <ScaleformPluginInfo> PluginList;
static PluginList s_plugins;

bool RegisterScaleformPlugin(const char * name, SKSEScaleformInterface::RegisterCallback callback)
{
	// check for a name collision
	for(PluginList::iterator iter = s_plugins.begin(); iter != s_plugins.end(); ++iter)
	{
		if(!strcmp(iter->name, name))
		{
			_WARNING("scaleform plugin name collision: %s", iter->name);
			return false;
		}
	}

	ScaleformPluginInfo	info;

	info.name = name;
	info.callback = callback;

	s_plugins.push_back(info);

	return true;
}

//// commands

class SKSEScaleform_AllowTextInput : public GFxFunctionHandler
{
public:
	virtual void	Invoke(Args * args)
	{
		ASSERT(args->numArgs >= 1);
		
		bool		enable = args->args[0].GetBool();

		InputManager	* inputManager = InputManager::GetSingleton();
		if(inputManager)
		{
			UInt8	allowCount = inputManager->AllowTextInput(enable);
#if _DEBUG
			_MESSAGE("scaleform: AllowTextInput (counter = %d)", allowCount);
#endif
		}
		else
			_WARNING("input manager not initialized");
	}
};

class SKSEScaleform_Log : public GFxFunctionHandler
{
public:
	virtual void	Invoke(Args * args)
	{
		ASSERT(args->numArgs >= 1);

		const char	* strData = args->args[0].GetString();

		_MESSAGE("%s", strData);
	}
};

class SKSEScaleform_SetINISetting : public GFxFunctionHandler
{
public:
	virtual void	Invoke(Args * args)
	{
		ASSERT(args->numArgs >= 2);

		const char	* settingName = args->args[0].GetString();
		double		settingValue = args->args[1].GetNumber();

#if _DEBUG
		_MESSAGE("scaleform: SetINISetting %s %f", settingName, settingValue);
#endif

		Setting	* setting = GetINISetting(settingName);

		if(setting)
		{
			if(!setting->SetDouble(settingValue))
			{
				_MESSAGE("tried to set a non-floating-point setting (%s)", settingName);
			}
		}
		else
		{
			_MESSAGE("setting not found (%s)", settingName);
		}
	}
};

class SKSEScaleform_GetINISetting : public GFxFunctionHandler
{
public:
	virtual void	Invoke(Args * args)
	{
		ASSERT(args->numArgs >= 1);

		const char	* settingName = args->args[0].GetString();

#if _DEBUG
		_MESSAGE("scaleform: GetINISetting %s", settingName);
#endif

		Setting	* setting = GetINISetting(settingName);

		args->result->SetNull();

		if(setting)
		{
			double	result;

			if(!setting->GetDouble(&result))
			{
				_MESSAGE("tried to get a non-floating-point setting (%s)", settingName);
			}
			else
			{
				args->result->SetNumber(result);
			}
		}
		else
		{
			_MESSAGE("setting not found (%s)", settingName);
		}
	}
};

class SKSEScaleform_OpenMenu : public GFxFunctionHandler
{
public:
	virtual void	Invoke(Args * args)
	{
		ASSERT(args->numArgs >= 1);

		const char	* menuName = args->args[0].GetString();

#if _DEBUG
		_MESSAGE("scaleform: open menu (%s)", menuName);
#endif

		StringCache::Ref	menuNameRef;

		CALL_MEMBER_FN(&menuNameRef, ctor)(menuName);
		CALL_MEMBER_FN(UIManager::GetSingleton(), AddMessage)(&menuNameRef, UIMessage::kMessage_Open, NULL);
		CALL_MEMBER_FN(&menuNameRef, Release)();
	}
};

class SKSEScaleform_CloseMenu : public GFxFunctionHandler
{
public:
	virtual void	Invoke(Args * args)
	{
		ASSERT(args->numArgs >= 1);

		const char	* menuName = args->args[0].GetString();

#if _DEBUG
		_MESSAGE("scaleform: close menu (%s)", menuName);
#endif

		StringCache::Ref	menuNameRef;

		CALL_MEMBER_FN(&menuNameRef, ctor)(menuName);
		CALL_MEMBER_FN(UIManager::GetSingleton(), AddMessage)(&menuNameRef, UIMessage::kMessage_Close, NULL);
		CALL_MEMBER_FN(&menuNameRef, Release)();
	}
};

static bool s_bExtendData = false;

class SKSEScaleform_ExtendData : public GFxFunctionHandler
{
public:
	virtual void	Invoke(Args* args)
	{
		ASSERT(args->numArgs >= 1);

		bool bExtend = args->args[0].GetBool();
		
		s_bExtendData = bExtend;
	}
};

class SKSEScaleform_ForceContainerCategorization : public GFxFunctionHandler
{
public:
	virtual void	Invoke(Args* args)
	{
		ASSERT(args->numArgs >= 1);

		bool enable = args->args[0].GetBool();

		Hooks_Gameplay_EnableForceContainerCategorization(enable);
	}
};


class SKSEScaleform_SendModEvent : public GFxFunctionHandler
{
public:
	virtual void	Invoke(Args* args)
	{
		ASSERT(args->numArgs >= 1);

		const char	* eventName = args->args[0].GetString();
		const char	* strArg = NULL;
		float		numArg = 0.0;

		if (args->numArgs >= 2)
			strArg = args->args[1].GetString();

		if (args->numArgs >= 3)
			numArg = args->args[2].GetNumber();

#if _DEBUG
		_MESSAGE("scaleform: send mod event (%s, %s, %d)", eventName, strArg, numArg);
#endif

		BSFixedString aEventName(eventName);
		BSFixedString aStrArg(strArg);
		SKSEModCallbackEvent evn(aEventName, aStrArg, numArg, NULL);
		g_modCallbackEventDispatcher.SendEvent(&evn);
	}
};

//// item card extensions

// 20
class StandardItemData
{
public:
	virtual ~StandardItemData();

	virtual const char *	GetName(void);
	virtual UInt32			GetCount(void);
	virtual UInt32			GetEquipState(void);
	virtual UInt32			GetFilterFlag(void);
	virtual UInt32			GetFavorite(void);
	virtual bool			GetEnabled(void);

//	void						** _vtbl;	// 00
	PlayerCharacter::ObjDesc	* objDesc;	// 04
	void						* unk08;	// 08
	UInt32						unk0C;		// 0C
	GFxValue					fxValue;	// 10

	MEMBER_FN_PREFIX(StandardItemData);
	DEFINE_MEMBER_FN(ctor_data, StandardItemData *, 0x0083A760, GFxMovieView ** movieView, PlayerCharacter::ObjDesc * objDesc, int unk);

	enum { kCtorHookAddress = 0x0083BAC9 };

	StandardItemData * ctor_Hook(GFxMovieView ** movieView, PlayerCharacter::ObjDesc * objDesc, int unk);
};

STATIC_ASSERT(sizeof(StandardItemData) == 0x20);

StandardItemData * StandardItemData::ctor_Hook(GFxMovieView ** movieView, PlayerCharacter::ObjDesc * objDesc, int unk)
{
	StandardItemData	* result = CALL_MEMBER_FN(this, ctor_data)(movieView, objDesc, unk);

//	_MESSAGE("StandardItemData hook");

	if(s_bExtendData)
	{
		scaleformExtend::CommonItemData(&result->fxValue, objDesc->form);
		scaleformExtend::StandardItemData(&result->fxValue, objDesc->form);
		scaleformExtend::InventoryData(&result->fxValue, *movieView, objDesc);
		// Calling this to set scrolls, potions, ingredients
		// as this function is called for inventory, barter, container
		scaleformExtend::MagicItemData(&result->fxValue, *movieView, objDesc->form);
	}

	return result;
}

// 20
class MagicItemData
{
public:
	virtual ~MagicItemData();

//	void			** _vtbl;	// 00
	UInt32			unk04;		// 04
	UInt16			unk08;		// 08
	UInt16			unk0A;		// 0A
	TESForm			* form;		// 0C
	GFxValue		fxValue;	// 10

	MEMBER_FN_PREFIX(MagicItemData);
	DEFINE_MEMBER_FN(ctor_data, MagicItemData *, 0x0086BF70, GFxMovieView ** movieView, TESForm * pForm, int unk);

	enum { kCtorHookAddress = 0x0086C529 };

	MagicItemData * ctor_Hook(GFxMovieView ** movieView, TESForm * pForm, int unk);
};

STATIC_ASSERT(sizeof(MagicItemData) == 0x20);

MagicItemData * MagicItemData::ctor_Hook(GFxMovieView ** movieView, TESForm * pForm, int unk)
{
	MagicItemData	* result = CALL_MEMBER_FN(this, ctor_data)(movieView, pForm, unk);

//	_MESSAGE("MagicItemData hook");

	if(s_bExtendData)
	{
		scaleformExtend::CommonItemData(&result->fxValue, pForm);
		scaleformExtend::MagicItemData(&result->fxValue, *movieView, pForm);
	}

	return result;
}

// ### todo
class FavItemDataHook
{
public:
	UInt32		unk00;		// 00
	UInt32		unk04;		// 04
	GFxValue	* fxValue;	// 08

	MEMBER_FN_PREFIX(FavItemDataHook);
	DEFINE_MEMBER_FN(Hooked, int, 0x008544F0, TESForm * pForm);

	enum { kCtorHookAddress = 0x00854EDF };

	int Hook(TESForm * pForm);
};

int FavItemDataHook::Hook(TESForm * pForm)
{
	int result = CALL_MEMBER_FN(this, Hooked)(pForm);

	if(s_bExtendData)
	{
		scaleformExtend::CommonItemData(fxValue, pForm);
	}

	return result;
}

//// core hook
void __stdcall InstallHooks(GFxMovieView * view)
{
	// called from a task, must be threadsafe

//	_MESSAGE("got new scaleform menu (view = %08X)", view);

	GFxValue	globals;

	bool	result = view->GetVariable(&globals, "_global");
	if(!result)
	{
		_ERROR("couldn't get _global");
		return;
	}

	GFxValue	skse;
	view->CreateObject(&skse);

	// root functions
	RegisterFunction <SKSEScaleform_AllowTextInput>(&skse, view, "AllowTextInput");
	RegisterFunction <SKSEScaleform_Log>(&skse, view, "Log");
	RegisterFunction <SKSEScaleform_SetINISetting>(&skse, view, "SetINISetting");
	RegisterFunction <SKSEScaleform_GetINISetting>(&skse, view, "GetINISetting");
	RegisterFunction <SKSEScaleform_OpenMenu>(&skse, view, "OpenMenu");
	RegisterFunction <SKSEScaleform_CloseMenu>(&skse, view, "CloseMenu");
	RegisterFunction <SKSEScaleform_ExtendData>(&skse, view, "ExtendData");
	RegisterFunction <SKSEScaleform_ForceContainerCategorization>(&skse, view, "ForceContainerCategorization");
	RegisterFunction <SKSEScaleform_SendModEvent>(&skse, view, "SendModEvent");

	// version
	GFxValue	version;
	view->CreateObject(&version);

	RegisterNumber(&version, "major", SKSE_VERSION_INTEGER);
	RegisterNumber(&version, "minor", SKSE_VERSION_INTEGER_MINOR);
	RegisterNumber(&version, "beta", SKSE_VERSION_INTEGER_BETA);
	RegisterNumber(&version, "releaseIdx", SKSE_VERSION_RELEASEIDX);

	skse.SetMember("version", &version);

	// plugins
	GFxValue	plugins;
	view->CreateObject(&plugins);

	for(PluginList::iterator iter = s_plugins.begin(); iter != s_plugins.end(); ++iter)
	{
		GFxValue	plugin;
		view->CreateObject(&plugin);

		iter->callback(view, &plugin);

		plugins.SetMember(iter->name, &plugin);
	}

	skse.SetMember("plugins", &plugins);

	globals.SetMember("skse", &skse);
}

static const UInt32 kInstallHooks_Base = 0x00A57E10;
static const UInt32 kInstallHooks_Entry_retn = kInstallHooks_Base + 0xBE;

__declspec(naked) void InstallHooks_Entry(void)
{
	__asm
	{
		pushad
		push	esi				// esi contains GFxMovieView
		call	InstallHooks	// stdcall so we don't need to do work
		popad

		// overwritten code
		mov		edx, [edx + 0x6C]
		push	eax
		mov		ecx, esi

		jmp		[kInstallHooks_Entry_retn]
	}
}

void Hooks_Scaleform_Commit(void)
{
	// movie creation hook
	WriteRelJump(kInstallHooks_Base + 0xB8, (UInt32)InstallHooks_Entry);

	// item card data creation hook
	WriteRelCall(StandardItemData::kCtorHookAddress, GetFnAddr(&StandardItemData::ctor_Hook));
	WriteRelCall(MagicItemData::kCtorHookAddress, GetFnAddr(&MagicItemData::ctor_Hook));
	WriteRelCall(FavItemDataHook::kCtorHookAddress, GetFnAddr(&FavItemDataHook::Hook));
}
