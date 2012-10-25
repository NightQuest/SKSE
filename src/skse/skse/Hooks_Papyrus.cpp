#include "Hooks_Papyrus.h"
#include "SafeWrite.h"
#include "PapyrusNativeFunctions.h"
#include "PapyrusVM.h"
#include "PapyrusArgs.h"
#include "GameAPI.h"
#include "GameObjects.h"
#include "GameReferences.h"
#include "PapyrusEvents.h"
#include "Serialization.h"
#ifdef _PPAPI
#include <list>
#endif

#include "PapyrusActiveMagicEffect.h"
#include "PapyrusActor.h"
#include "PapyrusActorBase.h"
#include "PapyrusAlias.h"
#include "PapyrusArmor.h"
#include "PapyrusArmorAddon.h"
#include "PapyrusBook.h"
#include "PapyrusCell.h"
#include "PapyrusColorForm.h"
#include "PapyrusCombatStyle.h"
#include "PapyrusConstructibleObject.h"
#include "PapyrusEnchantment.h"
#include "PapyrusForm.h"
#include "PapyrusGame.h"
#include "PapyrusHeadPart.h"
#include "PapyrusIngredient.h"
#include "PapyrusInput.h"
#include "PapyrusKeyword.h"
#include "PapyrusMath.h"
#include "PapyrusMisc.h"
#include "PapyrusObjectReference.h"
#include "PapyrusPotion.h"
#include "PapyrusQuest.h"
#include "PapyrusRace.h"
#include "PapyrusSKSE.h"
#include "PapyrusSpell.h"
#include "PapyrusSound.h"
#include "PapyrusSoundDescriptor.h"
#include "PapyrusStringUtil.h"
#include "PapyrusUI.h"
#include "PapyrusWeapon.h"
#include "PapyrusWeather.h"
#include "PapyrusShout.h"
#include "PapyrusUtility.h"

#define LOG_PAPYRUS_FUNCTIONS 0

typedef void (* _RegisterPapyrusFunctions)(VMClassRegistry ** registry);
_RegisterPapyrusFunctions RegisterPapyrusFunctions = (_RegisterPapyrusFunctions)0x008F8C10;

#ifdef _PPAPI
typedef std::list <SKSEPapyrusInterface::RegisterFunctions> PapyrusPluginList;
static PapyrusPluginList s_pap_plugins;

bool RegisterPapyrusPlugin(SKSEPapyrusInterface::RegisterFunctions callback)
{
	s_pap_plugins.push_back(callback);
	return true;
}
#endif

#if LOG_PAPYRUS_FUNCTIONS
struct VTableProxy
{
	void	** vtbl;

	void RegisterFunction_Hook(IFunction * fn)
	{
		_MESSAGE("%s %s", fn->GetClassName()->data, fn->GetName()->data);
	}
};
#endif

void RegisterPapyrusFunctions_Hook(VMClassRegistry ** registryPtr)
{
#if LOG_PAPYRUS_FUNCTIONS
	// this is all kinds of bad
	VTableProxy	** vtableProxy = (VTableProxy **)registryPtr;
	void		* oldRegisterFunction = (*vtableProxy)->vtbl[0x16 + 1];
	SafeWrite32((UInt32)&(*vtableProxy)->vtbl[0x16 + 1], GetFnAddr(&VTableProxy::RegisterFunction_Hook));
#endif

	// call original code
	RegisterPapyrusFunctions(registryPtr);

#if LOG_PAPYRUS_FUNCTIONS
	SafeWrite32((UInt32)&(*vtableProxy)->vtbl[0x16 + 1], (UInt32)oldRegisterFunction);
#endif

	VMClassRegistry * registry = *registryPtr;

	// SKSE
	papyrusSKSE::RegisterFuncs(registry);

	// TESForm
	papyrusForm::RegisterEventSinks();
	papyrusForm::RegisterFuncs(registry);

	// ColorForm
	papyrusColorComponent::RegisterFuncs(registry);
	papyrusColorForm::RegisterFuncs(registry);

	// HeadPart
	papyrusHeadPart::RegisterFuncs(registry);

	// TESObjectCELL
	papyrusCell::RegisterFuncs(registry);

	// ArmorAddon (TESObjectARMA)
	papyrusArmorAddon::RegisterFuncs(registry);

	// TESObjectARMO
	papyrusArmor::RegisterFuncs(registry);

	// TESSoulGem
	papyrusSoulGem::RegisterFuncs(registry);

	// BGSApparatus
	papyrusApparatus::RegisterFuncs(registry);

	// Math
	papyrusMath::RegisterFuncs(registry);

	// Input
	papyrusInput::RegisterFuncs(registry);

	// ObjectReference
	papyrusObjectReference::RegisterFuncs(registry);

	// Weapon
	papyrusWeapon::RegisterFuncs(registry);

	// CombatStyle
	papyrusCombatStyle::RegisterFuncs(registry);

	// Actor
	papyrusActor::RegisterFuncs(registry);

	// ActorBase (TESNPC)
	papyrusActorBase::RegisterFuncs(registry);

	// Outfit
	papyrusOutfit::RegisterFuncs(registry);

	// Potion
	papyrusPotion::RegisterFuncs(registry);

	// Race
	papyrusRace::RegisterFuncs(registry);

	// Spell
	papyrusSpell::RegisterFuncs(registry);

	// Enchantment
	papyrusEnchantment::RegisterFuncs(registry);

	// Ingredient
	papyrusIngredient::RegisterFuncs(registry);

	// StringUtil
	papyrusStringUtil::RegisterFuncs(registry);

	// Keyword
	papyrusKeyword::RegisterFuncs(registry);

	// TESObjectBOOK
	papyrusBook::RegisterFuncs(registry);

	// ConstructibleObject
	papyrusConstructibleObject::RegisterFuncs(registry);

	// Game
	papyrusGame::RegisterFuncs(registry);

	// UI
	papyrusUI::RegisterFuncs(registry);

	// Alias
	papyrusAlias::RegisterFuncs(registry);

	// Quest
	papyrusQuest::RegisterFuncs(registry);

	// Shout
	papyrusShout::RegisterFuncs(registry);

	// Utility
	papyrusUtility::RegisterFuncs(registry);

	// ActiveMagicEffect
	papyrusActiveMagicEffect::RegisterFuncs(registry);

	// SoundDescriptor
	papyrusSoundDescriptor::RegisterFuncs(registry);

	// Sound
	papyrusSound::RegisterFuncs(registry);

	// Weather
	papyrusWeather::RegisterFuncs(registry);

#ifdef _PPAPI
	// Plugins
	for(PapyrusPluginList::iterator iter = s_pap_plugins.begin(); iter != s_pap_plugins.end(); ++iter)
	{
		(*iter)(registry);
	}
#endif
}

//// Event registration hooks

void SkyrimVM::OnFormDelete_Hook(UInt64 handle)
{
	CALL_MEMBER_FN(this, UnregisterFromSleep_Internal)(handle);

	g_menuOpenCloseRegs.UnregisterAll(handle);
	g_inputKeyEventRegs.UnregisterAll(handle);
	g_inputControlEventRegs.UnregisterAll(handle);
	g_modCallbackRegs.UnregisterAll(handle);
}

void SkyrimVM::RevertGlobalData_Hook(void)
{
	CALL_MEMBER_FN(this, RevertGlobalData_Internal)();

	Serialization::HandleRevertGlobalData();

	// For now, this is a suitable place to do this.
	if (*g_inputEventDispatcher)
		(*g_inputEventDispatcher)->AddEventSink(&g_inputEventHandler);
}

bool SkyrimVM::SaveGlobalData_Hook(void * handleReaderWriter, void * saveStorageWrapper)
{
	bool success = CALL_MEMBER_FN(this, SaveRegSleepEventHandles_Internal)(handleReaderWriter, saveStorageWrapper);
	Serialization::HandleSaveGlobalData();
	return success;
}

bool SkyrimVM::LoadGlobalData_Hook(void * handleReaderWriter, void * loadStorageWrapper)
{
	bool success = CALL_MEMBER_FN(this, LoadRegSleepEventHandles_Internal)(handleReaderWriter, loadStorageWrapper);
	Serialization::HandleLoadGlobalData();
	return success;
}

void Hooks_Papyrus_Init(void)
{
	//
}

void Hooks_Papyrus_Commit(void)
{
	WriteRelCall(0x008D6DA0 + 0x098B, (UInt32)RegisterPapyrusFunctions_Hook);

	// GlobalData / event regs
	WriteRelCall(0x008D56D0 + 0x002A, GetFnAddr(&SkyrimVM::OnFormDelete_Hook));
	WriteRelCall(0x008D5B10 + 0x0017, GetFnAddr(&SkyrimVM::RevertGlobalData_Hook)); // Normal game load
	WriteRelCall(0x008D5E80 + 0x0116, GetFnAddr(&SkyrimVM::RevertGlobalData_Hook)); // New script reload command
	WriteRelCall(0x008D2790 + 0x0101, GetFnAddr(&SkyrimVM::SaveGlobalData_Hook));
	WriteRelCall(0x008D5B40 + 0x01B9, GetFnAddr(&SkyrimVM::LoadGlobalData_Hook));
}
