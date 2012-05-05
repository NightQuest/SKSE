#include "Hooks_ObScript.h"
#include "CommandTable.h"
#include "GameAPI.h"
#include "GameData.h"
#include "GameMenus.h"
#include "skse_version.h"
#include "GameReferences.h"

CommandTable	g_commandTable;

const CommandInfo	* g_blockTypeStart =		(CommandInfo *)0x0121A138;
const CommandInfo	* g_blockTypeEnd =			(CommandInfo *)0x0121A6B0;
const CommandInfo	* g_consoleCommandsStart =	(CommandInfo *)0x0121A6D8;
const CommandInfo	* g_consoleCommandsEnd =	(CommandInfo *)0x0121D6D0;
const CommandInfo	* g_scriptCommandsStart =	(CommandInfo *)0x0121D6F8;
const CommandInfo	* g_scriptCommandsEnd =		(CommandInfo *)0x01224890;

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

		_MESSAGE("%04X %s", iter->opcode, line.c_str());

		if(!IsEmptyStr(iter->helpText))
		{
			gLog.Indent();
			_MESSAGE("%s", iter->helpText);
			gLog.Outdent();
		}
	}

	_MESSAGE("stubbed:");
	for(const CommandInfo * iter = start; iter <= end; ++iter)
	{
		if(iter->execute == (Cmd_Execute)0x0078ABD0)
		{
			_MESSAGE("%s", iter->longName);
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

// 1.4.15.0 runtime
static const CommandTable::PatchLocation kPatch_ScriptCommands_Start[] =
{
	{	0x00511ABB, 0x00 },
	{	0x00511C84, 0x04 },
	{	0x00511D1D, 0x08 },
	{	0x00512D07, 0x00 },
	{	0x005162BF, 0x00 },
	{	0x0053D109, 0x0C },
	{	0x0053D121, 0x00 },
	{	0x0053D139, 0x04 },
	{	0x0053D155, 0x0C },
	{	0x0053D16F, 0x04 },
	{	0x0053D18D, 0x00 },
	{	0x0053D1AF, 0x00 },
	{	0x0053D1CD, 0x04 },
	{	0x0053D1F3, 0x00 },
	{	0x0053D20A, 0x00 },
	{	0x005E50D9, 0x20 },
	{	0x005E50E5, 0x10 },
	{	0x005E51AE, 0x12 },
	{	0x005E51F1, 0x12 },
	{	0x005E51FD, 0x14 },
	{	0x005E5238, 0x12 },
	{	0x005E5245, 0x14 },
	{	0x005E52A6, 0x12 },
	{	0x005E52B2, 0x14 },
	{	0x005E52E0, 0x12 },
	{	0x005E5351, 0x12 },
	{	0x005E5383, 0x12 },
	{	0x005E538F, 0x14 },
	{	0x005E53E5, 0x12 },
	{	0x005E5423, 0x12 },
	{	0x005E542F, 0x14 },
	{	0x005E54D8, 0x12 },
	{	0x005E5507, 0x14 },
	{	0x005E55E4, 0x12 },
	{	0x005E5606, 0x14 },
	{	0x005E571E, 0x12 },
	{	0x005E5768, 0x12 },
	{	0x005E5778, 0x14 },
	{	0x005E5811, 0x14 },
	{	0x0069A87C, 0x12 },
	{	0x0069A8A9, 0x14 },
	{	0 },
};

static const CommandTable::PatchLocation kPatch_ScriptCommands_End[] =
{
	{	0x00511BC2, 0x08 },
	{	0x00511CAF, 0x04 },
	{	0 },
};

static const CommandTable::PatchLocation kPatch_ScriptCommands_MaxIdx[] =
{
	{	0x004FE147 + 1, 0 },
	{	0x00511AA9 + 2,	(UInt32)(-0x1001) },
	{	0x00511BC0 + 6, 0 },
	{	0x00512CF6 + 1,	(UInt32)(-0x1001) },
	{	0x005162B1 + 2,	(UInt32)(-0x1001) },
	{	0x005E454D + 2,	(UInt32)(-0x1001) },
	{	0x005E455D + 1,	(UInt32)(-0x1001) },
	{	0x005E4569 + 2,	(UInt32)(-0x1001) },

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

#include "GameForms.h"
#include "GameRTTI.h"
#include "GameObjects.h"

void DumpMagicEffects(MagicItem* pMagic)
{
	_MESSAGE("-- Effects: %d", pMagic->effectItemList.count);
	for (UInt32 n = 0; n < pMagic->effectItemList.count; n++) {
		MagicItem::EffectItem* pEffect = NULL;
		if (pMagic->effectItemList.GetNthItem(n, pEffect))  {
			_MESSAGE("-- %d> %s mag: %f area: %d duration: %d",
				n, pEffect->mgef->fullName.name.data, pEffect->magnitude, 
				pEffect->area, pEffect->duration);
		}
	}
}


void DumpSpell(SpellItem* pSpell)
{
	_MESSAGE("Spell: %s", pSpell->fullName.name.data);
	_MESSAGE("-- cost: %d castTime: %f spellPerk: %s", pSpell->data.unk00.cost, 
		pSpell->data.castTime, pSpell->data.spellPerk ? pSpell->data.spellPerk->fullName.name.data : "none");
	DumpMagicEffects(pSpell);
	_MESSAGE("-----");
}

void DumpAlchemyItem(AlchemyItem* pPotion)
{
	_MESSAGE("AlchemyItem: %s", pPotion->fullName.name.data);
	DumpMagicEffects(pPotion);
	_MESSAGE("-----");
}

typedef UInt32 (* _GetControl)(const char*);
_GetControl GetControl = (_GetControl)0xBFAE20;

bool Cmd_GetSKSEVersion_Eval(COMMAND_ARGS_EVAL)
{
	*result = SKSE_VERSION_INTEGER;
	PrintVersion();

//	PlayerCharacter* pPlayer = *g_thePlayer;
//	Actor* pActor = (Actor*)DYNAMIC_CAST(pPlayer, Actor, PlayerCharacter);

	//UInt32 code = GetControl("Forward");
	//TESForm* pForm = LookupFormByID(0x000E2D3D);
	//AlchemyItem* pPotion = (AlchemyItem*)DYNAMIC_CAST(pForm, AlchemyItem, TESForm);
	//DumpClass(pForm, 512);
	//DumpAlchemyItem(pPotion);

	//TESForm* pForm2 = LookupFormByID(0x000F4314);
	//AlchemyItem* pPotion2 = (AlchemyItem*)DYNAMIC_CAST(pForm2, AlchemyItem, TESForm);
	//DumpClass(pForm2, 512);
	//DumpAlchemyItem(pPotion2);

//	InputManager* pInputMgr = InputManager::GetSingleton();
//	DumpClass(pInputMgr, 512);

	//TESForm* pForm2 = LookupFormByID(0xC44C8);
	//BGSPerk* pPerk2 = (BGSPerk*)DYNAMIC_CAST(pForm2, BGSPerk, TESForm);
	//DumpClass(pForm);

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

DEFINE_CMD_COND(GetSKSEVersion, "returns the major SKSE version number", false, NULL);
DEFINE_CMD_COND(GetSKSEVersionMinor, "returns the minor SKSE version number", false, NULL);
DEFINE_CMD_COND(GetSKSEVersionBeta, "returns the beta SKSE version number", false, NULL);
DEFINE_CMD_COND(GetSKSERelease, "returns the SKSE release number", false, NULL);

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

#undef CMD

	g_commandTable.Add();	// padding command
}

void Hooks_ObScript_Commit(void)
{
	// patch the exe
	g_commandTable.PatchEXE(&kPatchSet);
}
