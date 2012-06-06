#include "Hooks_ObScript.h"
#include "CommandTable.h"
#include "GameAPI.h"
#include "skse_version.h"

CommandTable	g_commandTable;

const CommandInfo	* g_blockTypeStart =		(CommandInfo *)0x01240388;
const CommandInfo	* g_blockTypeEnd =			(CommandInfo *)0x01240900;
const CommandInfo	* g_consoleCommandsStart =	(CommandInfo *)0x01240928;
const CommandInfo	* g_consoleCommandsEnd =	(CommandInfo *)0x01243A38;
const CommandInfo	* g_scriptCommandsStart =	(CommandInfo *)0x01243A60;
const CommandInfo	* g_scriptCommandsEnd =		(CommandInfo *)0x0124ACC0;

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

// 1.6.87.0 runtime
static const CommandTable::PatchLocation kPatch_ScriptCommands_Start[] =
{
	{	0x0051414B, 0x00 },
	{	0x00514314, 0x04 },
	{	0x005143AD, 0x08 },
	{	0x00515397, 0x00 },
	{	0x0051894F, 0x00 },
	{	0x0053FAC9, 0x0C },
	{	0x0053FAE1, 0x00 },
	{	0x0053FAF9, 0x04 },
	{	0x0053FB15, 0x0C },
	{	0x0053FB2F, 0x04 },
	{	0x0053FB4D, 0x00 },
	{	0x0053FB6F, 0x00 },
	{	0x0053FB8D, 0x04 },
	{	0x0053FBB3, 0x00 },
	{	0x0053FBCA, 0x00 },
	{	0x005E9309, 0x20 },
	{	0x005E9315, 0x10 },
	{	0x005E93DE, 0x12 },
	{	0x005E9421, 0x12 },
	{	0x005E942D, 0x14 },
	{	0x005E9468, 0x12 },
	{	0x005E9475, 0x14 },
	{	0x005E94D6, 0x12 },
	{	0x005E94E2, 0x14 },
	{	0x005E9510, 0x12 },
	{	0x005E9581, 0x12 },
	{	0x005E95B3, 0x12 },
	{	0x005E95BF, 0x14 },
	{	0x005E9615, 0x12 },
	{	0x005E9653, 0x12 },
	{	0x005E965F, 0x14 },
	{	0x005E9708, 0x12 },
	{	0x005E9737, 0x14 },
	{	0x005E9814, 0x12 },
	{	0x005E9836, 0x14 },
	{	0x005E994E, 0x12 },
	{	0x005E9998, 0x12 },
	{	0x005E99A8, 0x14 },
	{	0x005E9A41, 0x14 },
	{	0x006A1C6C, 0x12 },
	{	0x006A1C99, 0x14 },
	{	0 },
};

static const CommandTable::PatchLocation kPatch_ScriptCommands_End[] =
{
	{	0x00514252, 0x08 },
	{	0x0051433F, 0x04 },
	{	0 },
};

static const CommandTable::PatchLocation kPatch_ScriptCommands_MaxIdx[] =
{
	{	0x00500480 + 0x0087 + 1,	0 },
	{	0x00514110 + 0x0029 + 2,	(UInt32)(-0x1001) },
	{	0x00514250 + 0x0000 + 6,	0 },
	{	0x00515230 + 0x0156 + 1,	(UInt32)(-0x1001) },
	{	0x005181F0 + 0x0751 + 2,	(UInt32)(-0x1001) },
	{	0x005E8750 + 0x000D + 2,	(UInt32)(-0x1001) },
	{	0x005E8750 + 0x001D + 1,	(UInt32)(-0x1001) },
	{	0x005E8750 + 0x0029 + 2,	(UInt32)(-0x1001) },

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

bool Cmd_SKSETestFunc_Eval(COMMAND_ARGS_EVAL)
{

	PlayerCharacter* pPC = *(g_thePlayer);
	TESForm* pPlayerForm = pPC->baseForm;
	

	for (UInt32 n = 0; n < pPC->addedSpells.spellCount; n++)
	{
		SpellItem* pSpell = pPC->addedSpells.spells[n];
		_MESSAGE("%d> %s", n, pSpell->fullName.name.data);
	}

	//const char* oldName = papyrusForm::GetName(pPlayerForm).data;
	//papyrusForm::SetName(pPlayerForm, BSFixedString("Bob"));
	//const char* nuName = papyrusForm::GetName(pPlayerForm).data;
	//Console_Print("OldName: %s NuName: %s", oldName, nuName);

	//DataHandler* handler = DataHandler::GetSingleton();
	
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


	TESForm* pForm = LookupFormByID(0x2F2F4);
	TESObjectWEAP* pWeap = DYNAMIC_CAST(pForm, TESForm, TESObjectWEAP);

	pForm = LookupFormByID(0x58F5E);
	pWeap = DYNAMIC_CAST(pForm, TESForm, TESObjectWEAP);
	DumpClass(pWeap, 1024);

	//pForm = LookupFormByID(0x73F4C);
	//AlchemyItem* pPotion = DYNAMIC_CAST(pForm, TESForm, AlchemyItem);
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
