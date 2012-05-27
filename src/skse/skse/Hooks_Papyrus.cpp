#include "Hooks_Papyrus.h"
#include "SafeWrite.h"
#include "PapyrusNativeFunctions.h"
#include "PapyrusVM.h"
#include "PapyrusArgs.h"
#include "GameAPI.h"
#include "GameObjects.h"
#include "GameReferences.h"

#include "PapyrusActor.h"
#include "PapyrusActorBase.h"
#include "PapyrusAlias.h"
#include "PapyrusArmor.h"
#include "PapyrusBook.h"
#include "PapyrusCell.h"
#include "PapyrusCombatStyle.h"
#include "PapyrusConstructibleObject.h"
#include "PapyrusEnchantment.h"
#include "PapyrusForm.h"
#include "PapyrusGame.h"
#include "PapyrusIngredient.h"
#include "PapyrusInput.h"
#include "PapyrusKeyword.h"
#include "PapyrusMath.h"
#include "PapyrusMisc.h"
#include "PapyrusObjectReference.h"
#include "PapyrusPotion.h"
#include "PapyrusQuest.h"
#include "PapyrusSKSE.h"
#include "PapyrusSpell.h"
#include "PapyrusStringUtil.h"
#include "PapyrusUI.h"
#include "PapyrusWeapon.h"

typedef void (* _RegisterPapyrusFunctions)(VMClassRegistry ** registry);
_RegisterPapyrusFunctions RegisterPapyrusFunctions = (_RegisterPapyrusFunctions)0x008F2F10;

void RegisterPapyrusFunctions_Hook(VMClassRegistry ** registryPtr)
{
	// call original code
	RegisterPapyrusFunctions(registryPtr);

	VMClassRegistry * registry = *registryPtr;

	// SKSE
	papyrusSKSE::RegisterFuncs(registry);

	// TESForm
	papyrusForm::RegisterFuncs(registry);

	// TESObjectCELL
	papyrusCell::RegisterFuncs(registry);

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

	// Spell
	papyrusSpell::RegisterFuncs(registry);

	// Spell
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
}

void Hooks_Papyrus_Init(void)
{
	//
}

void Hooks_Papyrus_Commit(void)
{
	WriteRelCall(0x008D1E3B, (UInt32)RegisterPapyrusFunctions_Hook);
}
