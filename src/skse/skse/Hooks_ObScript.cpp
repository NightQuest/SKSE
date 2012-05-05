#include "Hooks_ObScript.h"
#include "CommandTable.h"
#include "GameAPI.h"
#include "skse_version.h"

CommandTable	g_commandTable;

const CommandInfo	* g_blockTypeStart =		(CommandInfo *)0x01221158;
const CommandInfo	* g_blockTypeEnd =			(CommandInfo *)0x012216D0;
const CommandInfo	* g_consoleCommandsStart =	(CommandInfo *)0x012216F8;
const CommandInfo	* g_consoleCommandsEnd =	(CommandInfo *)0x012246F0;
const CommandInfo	* g_scriptCommandsStart =	(CommandInfo *)0x01224718;
const CommandInfo	* g_scriptCommandsEnd =		(CommandInfo *)0x0122B8B0;

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

// 1.5.26.0 runtime
static const CommandTable::PatchLocation kPatch_ScriptCommands_Start[] =
{
	{	0x005114DB, 0x00 },
	{	0x005116A4, 0x04 },
	{	0x0051173D, 0x08 },
	{	0x00512727, 0x00 },
	{	0x00515CDF, 0x00 },
	{	0x0053CBF9, 0x0C },
	{	0x0053CC11, 0x00 },
	{	0x0053CC29, 0x04 },
	{	0x0053CC45, 0x0C },
	{	0x0053CC5F, 0x04 },
	{	0x0053CC7D, 0x00 },
	{	0x0053CC9F, 0x00 },
	{	0x0053CCBD, 0x04 },
	{	0x0053CCE3, 0x00 },
	{	0x0053CCFA, 0x00 },
	{	0x005E54A9, 0x20 },
	{	0x005E54B5, 0x10 },
	{	0x005E557E, 0x12 },
	{	0x005E55C1, 0x12 },
	{	0x005E55CD, 0x14 },
	{	0x005E5608, 0x12 },
	{	0x005E5615, 0x14 },
	{	0x005E5676, 0x12 },
	{	0x005E5682, 0x14 },
	{	0x005E56B0, 0x12 },
	{	0x005E5721, 0x12 },
	{	0x005E5753, 0x12 },
	{	0x005E575F, 0x14 },
	{	0x005E57B5, 0x12 },
	{	0x005E57F3, 0x12 },
	{	0x005E57FF, 0x14 },
	{	0x005E58A8, 0x12 },
	{	0x005E58D7, 0x14 },
	{	0x005E59B4, 0x12 },
	{	0x005E59D6, 0x14 },
	{	0x005E5AEE, 0x12 },
	{	0x005E5B38, 0x12 },
	{	0x005E5B48, 0x14 },
	{	0x005E5BE1, 0x14 },
	{	0x0069BBBC, 0x12 },
	{	0x0069BBE9, 0x14 },
	{	0 },
};

static const CommandTable::PatchLocation kPatch_ScriptCommands_End[] =
{
	{	0x005115E2, 0x08 },
	{	0x005116CF, 0x04 },
	{	0 },
};

static const CommandTable::PatchLocation kPatch_ScriptCommands_MaxIdx[] =
{
	{	0x004FD8D0 + 0x0087 + 1,	0 },
	{	0x005114A0 + 0x0029 + 2,	(UInt32)(-0x1001) },
	{	0x005115E0 + 0x0000 + 6,	0 },
	{	0x005125C0 + 0x0156 + 1,	(UInt32)(-0x1001) },
	{	0x00515580 + 0x0751 + 2,	(UInt32)(-0x1001) },
	{	0x005E48F0 + 0x000D + 2,	(UInt32)(-0x1001) },
	{	0x005E48F0 + 0x001D + 1,	(UInt32)(-0x1001) },
	{	0x005E48F0 + 0x0029 + 2,	(UInt32)(-0x1001) },

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

#include "GameObjects.h"
#include "GameAPI.h"
#include "GameReferences.h"
#include "GameForms.h"
#include "GameRTTI.h"
#include "GameExtraData.h"
bool Cmd_SKSETestFunc_Eval(COMMAND_ARGS_EVAL)
{
	PlayerCharacter *pPC = (*g_thePlayer);

	//TESForm* pForm = LookupFormByID(0xAD247);
	//BGSOutfit* pOutfit = DYNAMIC_CAST(pForm, TESForm, BGSOutfit);
	//if (pOutfit)
	//	DumpClass(pOutfit);


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
