#include "Hooks_ObScript.h"
#include "CommandTable.h"
#include "GameAPI.h"
#include "skse_version.h"

CommandTable	g_commandTable;

const CommandInfo	* g_blockTypeStart =		(CommandInfo *)0x01412050;
const CommandInfo	* g_blockTypeEnd =			(CommandInfo *)0x014125C8;
const CommandInfo	* g_consoleCommandsStart =	(CommandInfo *)0x014125F0;
const CommandInfo	* g_consoleCommandsEnd =	(CommandInfo *)0x014155C0;
const CommandInfo	* g_scriptCommandsStart =	(CommandInfo *)0x014155E8;
const CommandInfo	* g_scriptCommandsEnd =		(CommandInfo *)0x0141C780;

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

// 1.3.10.0 runtime
static const CommandTable::PatchLocation kPatch_ScriptCommands_Start[] =
{
	{	0x005889D2, 0x00 },
	{	0x00589201, 0x00 },
	{	0x0058921E, 0x04 },
	{	0x00589248, 0x08 },
	{	0x005AE4B5, 0x0C },
	{	0x005AE4D8, 0x00 },
	{	0x005AE4FB, 0x04 },
	{	0x005AE51B, 0x0C },
	{	0x005AE531, 0x0C },
	{	0x005AE551, 0x04 },
	{	0x005AE563, 0x04 },
	{	0x005AE57F, 0x0C },
	{	0x005AE58F, 0x04 },
	{	0x005AE59F, 0x00 },
	{	0x005AE5C4, 0x0C },
	{	0x005AE5D4, 0x00 },
	{	0x005AE5FC, 0x04 },
	{	0x005AE60E, 0x04 },
	{	0x005AE62A, 0x04 },
	{	0x005AE63A, 0x00 },
	{	0x005AE65F, 0x00 },
	{	0x006A67ED, 0x20 },
	{	0x006A6804, 0x10 },
	{	0x006A6831, 0x20 },
	{	0x006A6FAC, 0x14 },
	{	0x006A72DF, 0x12 },
	{	0x006A73D3, 0x14 },
	{	0x006A741C, 0x14 },
	{	0x006A74A6, 0x14 },
	{	0x006A74C2, 0x14 },
	{	0x00799A9B, 0x12 },
	{	0x00799ADA, 0x14 },
	{	0 },
};

static const CommandTable::PatchLocation kPatch_ScriptCommands_End[] =
{
	{	0x00586589, 0x08 },
	{	0 },
};

static const CommandTable::PatchLocation kPatch_ScriptCommands_MaxIdx[] =
{
	{	0x0056C039 + 1, 0 },
	{	0x00586587 + 6, 0 },
	{	0x005889BB + 3, 0 },
	{	0x005891F0 + 3, (UInt32)(-0x1000) },
	{	0x005AE488 + 6, (UInt32)(-0x1000) },

	// condition stuff
	{	0x006A5A48 + 3,	0 },
	{	0x006A5A65 + 3, (UInt32)(-0x1000) },
	{	0x006A5A84 + 3, (UInt32)(-0x1000) },

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
}

void Hooks_ObScript_Commit(void)
{
	// patch the exe
	g_commandTable.PatchEXE(&kPatchSet);
}
