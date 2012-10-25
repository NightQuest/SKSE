#include "Hooks_ObScript.h"
#include "CommandTable.h"
#include "GameAPI.h"
#include "skse_version.h"

CommandTable	g_commandTable;

const CommandInfo	* g_blockTypeStart =		(CommandInfo *)0x0124A348;
const CommandInfo	* g_blockTypeEnd =			(CommandInfo *)0x0124A8C0;
const CommandInfo	* g_consoleCommandsStart =	(CommandInfo *)0x0124A8E8;
const CommandInfo	* g_consoleCommandsEnd =	(CommandInfo *)0x0124D9F8;
const CommandInfo	* g_scriptCommandsStart =	(CommandInfo *)0x0124DA20;
const CommandInfo	* g_scriptCommandsEnd =		(CommandInfo *)0x01254CD0;

static bool IsEmptyStr(const char * data)
{
	return !data || !data[0];
}

void DumpCommands(const CommandInfo * start, const CommandInfo * end)
{
	for(const CommandInfo * iter = start; iter <= end; ++iter)
	{
		std::string	line;

		line = iter->longName;

		if(!IsEmptyStr(iter->shortName))
		{
			line += ", ";
			line += iter->shortName;
		}

		if(iter->numParams)
		{
			ParamInfo	* params = iter->params;

			line += ": ";

			for(UInt32 i = 0; i < iter->numParams; i++)
			{
				ParamInfo	* param = &params[i];

				if(i) line += ", ";

				if(param->isOptional) line += "(";

				line += param->typeStr;

				if(param->isOptional) line += ")";
			}
		}

		_MESSAGE("%04X %04X %s", iter->opcode, iter->execute, line.c_str());

		if(!IsEmptyStr(iter->helpText))
		{
			gLog.Indent();
			_MESSAGE("%s", iter->helpText);
			gLog.Outdent();
		}
	}
}

void ObScript_DumpCommands(void)
{
	_MESSAGE("block types:");
	DumpCommands(g_blockTypeStart, g_blockTypeEnd);
	_MESSAGE("console commands");
	DumpCommands(g_consoleCommandsStart, g_consoleCommandsEnd);
	_MESSAGE("script commands");
	DumpCommands(g_scriptCommandsStart, g_scriptCommandsEnd);
}

static const CommandTable::PatchLocation kPatch_ScriptCommands_Start[] =
{
	{	0x00515FFB, 0x00 },
	{	0x005161C4, 0x04 },
	{	0x0051625D, 0x08 },
	{	0x00517277, 0x00 },
	{	0x0051A82F, 0x00 },
	{	0x005418C9, 0x0C },
	{	0x005418E1, 0x00 },
	{	0x005418F9, 0x04 },
	{	0x00541915, 0x0C },
	{	0x0054192F, 0x04 },
	{	0x0054194D, 0x00 },
	{	0x0054196F, 0x00 },
	{	0x0054198D, 0x04 },
	{	0x005419B3, 0x00 },
	{	0x005419CA, 0x00 },
	{	0x005EA619, 0x20 },
	{	0x005EA625, 0x10 },
	{	0x005EA6EE, 0x12 },
	{	0x005EA731, 0x12 },
	{	0x005EA73D, 0x14 },
	{	0x005EA778, 0x12 },
	{	0x005EA785, 0x14 },
	{	0x005EA7E6, 0x12 },
	{	0x005EA7F2, 0x14 },
	{	0x005EA820, 0x12 },
	{	0x005EA891, 0x12 },
	{	0x005EA8C3, 0x12 },
	{	0x005EA8CF, 0x14 },
	{	0x005EA925, 0x12 },
	{	0x005EA963, 0x12 },
	{	0x005EA96F, 0x14 },
	{	0x005EAA18, 0x12 },
	{	0x005EAA47, 0x14 },
	{	0x005EAB24, 0x12 },
	{	0x005EAB46, 0x14 },
	{	0x005EAC5E, 0x12 },
	{	0x005EACA8, 0x12 },
	{	0x005EACB8, 0x14 },
	{	0x005EAD51, 0x14 },
	{	0x006A2ABC, 0x12 },
	{	0x006A2AE9, 0x14 },
	{	0 },
};

static const CommandTable::PatchLocation kPatch_ScriptCommands_End[] =
{
	{	0x00516102, 0x08 },
	{	0x005161EF, 0x04 },
	{	0 },
};

static const CommandTable::PatchLocation kPatch_ScriptCommands_MaxIdx[] =
{
	{	0x00502120 + 0x0087 + 1,	0 },
	{	0x00515FC0 + 0x0029 + 2,	(UInt32)(-0x1001) },
	{	0x00516100 + 0x0000 + 6,	0 },
	{	0x00517110 + 0x0156 + 1,	(UInt32)(-0x1001) },
	{	0x0051A0D0 + 0x0751 + 2,	(UInt32)(-0x1001) },
	{	0x005E9A60 + 0x000D + 2,	(UInt32)(-0x1001) },
	{	0x005E9A60 + 0x001D + 1,	(UInt32)(-0x1001) },
	{	0x005E9A60 + 0x0029 + 2,	(UInt32)(-0x1001) },

	{	0 },
};

static const CommandTable::PatchSet kPatchSet =
{
	kPatch_ScriptCommands_Start,
	kPatch_ScriptCommands_End,
	kPatch_ScriptCommands_MaxIdx
};

// core commands
static void PrintVersion(void)
{
	if(IsConsoleMode())
	{
		Console_Print("SKSE version: %d.%d.%d, release idx %d, runtime %08X",
			SKSE_VERSION_INTEGER, SKSE_VERSION_INTEGER_MINOR, SKSE_VERSION_INTEGER_BETA,
			SKSE_VERSION_RELEASEIDX, RUNTIME_VERSION);
	}
}

bool Cmd_GetSKSEVersion_Eval(COMMAND_ARGS_EVAL)
{
	*result = SKSE_VERSION_INTEGER;

	PrintVersion();

	return true;
}

bool Cmd_GetSKSEVersion_Execute(COMMAND_ARGS)
{
	return Cmd_GetSKSEVersion_Eval(thisObj, 0, 0, result);
}

bool Cmd_GetSKSEVersionMinor_Eval(COMMAND_ARGS_EVAL)
{
	*result = SKSE_VERSION_INTEGER_MINOR;

	PrintVersion();

	return true;
}

bool Cmd_GetSKSEVersionMinor_Execute(COMMAND_ARGS)
{
	return Cmd_GetSKSEVersionMinor_Eval(thisObj, 0, 0, result);
}

bool Cmd_GetSKSEVersionBeta_Eval(COMMAND_ARGS_EVAL)
{
	*result = SKSE_VERSION_INTEGER;

	PrintVersion();

	return true;
}

bool Cmd_GetSKSEVersionBeta_Execute(COMMAND_ARGS)
{
	return Cmd_GetSKSEVersionBeta_Eval(thisObj, 0, 0, result);
}

bool Cmd_GetSKSERelease_Eval(COMMAND_ARGS_EVAL)
{
	*result = SKSE_VERSION_RELEASEIDX;

	PrintVersion();

	return true;
}

bool Cmd_GetSKSERelease_Execute(COMMAND_ARGS)
{
	return Cmd_GetSKSERelease_Eval(thisObj, 0, 0, result);
}

#include "GameData.h"
#include "GameObjects.h"
#include "GameAPI.h"
#include "GameReferences.h"
#include "GameForms.h"
#include "GameRTTI.h"
#include "GameExtraData.h"

#include "PapyrusKeyword.h"
#include "PapyrusForm.h"
#include "PapyrusObjectReference.h"
#include "PapyrusStringUtil.h"

bool Cmd_SKSETestFunc_Eval(COMMAND_ARGS_EVAL)
{

	if(thisObj) {
		Actor* actor = DYNAMIC_CAST(thisObj, TESObjectREFR, Actor);
		if(actor) {
			tList<ActiveEffect> * effects = actor->magicTarget.GetActiveEffects();
			for(int i = 0; i < effects->Count(); i++)
			{
				ActiveEffect* effect = effects->GetNthItem(i);
				_MESSAGE("%s", effect->item->fullName.name);
				DumpClass(effect, 50);
			}
		}
		/*Console_Print("%f", papyrusObjectReference::GetCharge(thisObj));

		if(TESObjectWEAP* weapon = DYNAMIC_CAST(thisObj->baseForm, TESForm, TESObjectWEAP)) {
			EnchantmentItem* item = weapon->enchantable.enchantment;
			ExtraEnchantment* extraEnch = static_cast<ExtraEnchantment*>(thisObj->extraData.GetByType(kExtraData_Enchantment));
			if(!item && extraEnch) {
				item = extraEnch->enchant;
			}
			if(item) {
				DumpClass(item);
				Console_Print("%f", papyrusObjectReference::GetMaximumCharge(thisObj));
			}
		}*/
	}
//	PlayerCharacter* pPC = *(g_thePlayer);
////	DumpClass(pPC);
//	TESForm* pPlayerForm = pPC->baseForm;
//
//	//UInt32 numItems = papyrusObjectReference::GetNumItems(pPC);
//	//TESForm* pItem = papyrusObjectReference::GetNthForm(pPC, 0);
//
//	UInt8 perkPoints = pPC->numPerkPoints;
//	_MESSAGE("PerkPoints: %d", perkPoints);
//
//	BSFixedString sGold("Gold");
//	BSFixedString sGoldOreVein("Gold Ore Vein");
//
//	_MESSAGE("sGold: %s sGoldOreVein: %s", sGold.data, sGoldOreVein.data);
//	SInt32 pos = papyrusStringUtil::Find(NULL, sGoldOreVein, sGold);
//
//	//Actor* pActor = DYNAMIC_CAST(thisObj, TESObjectREFR, Actor);
//	//if (pActor)
//	//	DumpClass(pActor);
//
//	for (UInt32 n = 0; n < pPC->addedSpells.spellCount; n++)
//	{
//		SpellItem* pSpell = pPC->addedSpells.spells[n];
//		_MESSAGE("%d> %s", n, pSpell->fullName.name.data);
//		//for (UInt32 x = 0; x < pSpell->effectItemList.count; x++) {
//		//	MagicItem::EffectItem* pEI = NULL;
//		//	pSpell->effectItemList.GetNthItem(x, pEI);
//		//	if (pEI)
//		//		DumpClass(pEI->mgef);
//		//}
//		//DumpClass(pSpell);
//	}

	//const char* oldName = papyrusForm::GetName(pPlayerForm).data;
	//papyrusForm::SetName(pPlayerForm, BSFixedString("Bob"));
	//const char* nuName = papyrusForm::GetName(pPlayerForm).data;
	//Console_Print("OldName: %s NuName: %s", oldName, nuName);

	//DataHandler* handler = DataHandler::GetSingleton();
	//
	//UInt32 keywords = handler->keywords.count;
	//for (UInt32 k = 0; k < keywords; k++) {
	//	BGSKeyword* pKeyword = NULL;
	//	handler->keywords.GetNthItem(k, pKeyword);
	//	if (pKeyword) {
	//		_MESSAGE("%d: %s\n", k, pKeyword->keyword.Get());
	//	}
	//}

	//const char* wts = "WeapTypeSword";
	//BSFixedString weapTypeSword("WeapTypeSword");
	//const char* bsf = weapTypeSword.data;
	//BSFixedString bfsWTS(wts);
	//const char* bsf2 = bfsWTS.data;
	//BGSKeyword* pKeyword = papyrusKeyword::GetKeyword(NULL, weapTypeSword);
	//const char* key = pKeyword->keyword.Get();
	//
	//BGSKeyword* pKeywordMissing = papyrusKeyword::GetKeyword(NULL, "BobsYourUncle");

	//Console_Print("wts: %X (%s) bsf: %X (%s) bsf2: %X (%s)", wts, wts, bsf, bsf, bsf2, bsf2); 
	//Console_Print("pKeyword: %X pKeywordMissing: %X", pKeyword, pKeywordMissing);

	//PlayerCharacter *pPC = (*g_thePlayer);


	/*TESForm* pForm = LookupFormByID(0x0010fdd4);
	EffectSetting* pME = DYNAMIC_CAST(pForm, TESForm, EffectSetting);


	TESForm* pForm1 = LookupFormByID(0xe52);
	SpellItem* pSpellF = DYNAMIC_CAST(pForm1, TESForm, SpellItem);
	if (pSpellF) {
		MagicItem::EffectItem* pEI = NULL;
		pSpellF->effectItemList.GetNthItem(0, pEI);
		UInt32 cost = pSpellF->GetMagickaCost();
	}*/


	//TESObjectWEAP* pWeap = DYNAMIC_CAST(pForm, TESForm, TESObjectWEAP);

	//pForm = LookupFormByID(0x58F5E);
	//pWeap = DYNAMIC_CAST(pForm, TESForm, TESObjectWEAP);
	//DumpClass(pWeap, 1024);

	//pForm = LookupFormByID(0x73F4C);
	//AlchemyItem* pPotion = DYNAMIC_CAST(pForm, TESForm, AlchemyItem);
	//DumpClass(pPotion);
	//ASSERT(pPotion->IsFood() == false);

	//TESForm* pForm2 = LookupFormByID(0x3AC2E);
	//AlchemyItem* pPotion2 = DYNAMIC_CAST(pForm2, TESForm, AlchemyItem);
	//ASSERT(pPotion2->IsFood() == false);

	//TESForm* pForm3 = LookupFormByID(0x65C99);
	//AlchemyItem* pPotion3 = DYNAMIC_CAST(pForm3, TESForm, AlchemyItem);
	//ASSERT(pPotion3->IsFood() == true);

	//pForm = LookupFormByID(0x1CE1E);
	//TESClass* pClass = DYNAMIC_CAST(pForm, TESForm, TESClass);
	//if (pClass)
	//	DumpClass(pClass);

	return true;	
}

bool Cmd_SKSETestFunc_Execute(COMMAND_ARGS)
{
	return Cmd_SKSETestFunc_Eval(thisObj, 0, 0, result);
}

DEFINE_CMD_COND(GetSKSEVersion, "returns the major SKSE version number", false, NULL);
DEFINE_CMD_COND(GetSKSEVersionMinor, "returns the minor SKSE version number", false, NULL);
DEFINE_CMD_COND(GetSKSEVersionBeta, "returns the beta SKSE version number", false, NULL);
DEFINE_CMD_COND(GetSKSERelease, "returns the SKSE release number", false, NULL);
DEFINE_CMD_COND(SKSETestFunc, "", false, NULL);

void Hooks_ObScript_Init(void)
{
	// read vanilla commands
	g_commandTable.Init(0x1000, 0x1480);
	g_commandTable.Read(g_scriptCommandsStart, g_scriptCommandsEnd);

	// pad to 0x1400 to give bethesda room
	// pretty sure obscript is dead, but eh be safe

	while(g_commandTable.GetID() < 0x1400)
		g_commandTable.Add();

	// add our commands
#define CMD(name)	g_commandTable.Add(&kCommandInfo_##name)

	CMD(GetSKSEVersion);
	CMD(GetSKSEVersionMinor);
	CMD(GetSKSEVersionBeta);
	CMD(GetSKSERelease);

#ifdef _DEBUG
	CMD(SKSETestFunc);
#endif

#undef CMD

	g_commandTable.Add();	// padding command
}

void Hooks_ObScript_Commit(void)
{
	// patch the exe
	g_commandTable.PatchEXE(&kPatchSet);
}
