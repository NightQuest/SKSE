#include "Hooks_ObScript.h"
#include "CommandTable.h"
#include "GameAPI.h"
#include "skse_version.h"
#include "PapyrusVM.h"

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

bool Cmd_ClearInvalidRegistrations_Eval(COMMAND_ARGS_EVAL)
{

	UInt32 count = (*g_skyrimVM)->ClearInvalidRegistrations();
	

	if(IsConsoleMode())
	{
		Console_Print("Removed %d invalid OnUpdate registration(s)", count);
	}

	*result = count;

	return true;
}

bool Cmd_ClearInvalidRegistrations_Execute(COMMAND_ARGS)
{
	return Cmd_ClearInvalidRegistrations_Eval(thisObj, 0, 0, result);
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
	TESObjectSTAT	* stat = (TESObjectSTAT *)LookupFormByID(0x0005C09F);

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
DEFINE_CMD_COND(ClearInvalidRegistrations, "clears invalid event registrations", false, NULL);
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
	CMD(ClearInvalidRegistrations);

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
