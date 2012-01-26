#include "Hooks_ObScript.h"
#include "CommandTable.h"
#include "GameAPI.h"
#include "skse_version.h"

CommandTable	g_commandTable;

const CommandInfo	* g_blockTypeStart =		(CommandInfo *)0x0121B138;
const CommandInfo	* g_blockTypeEnd =			(CommandInfo *)0x0121B6B0;
const CommandInfo	* g_consoleCommandsStart =	(CommandInfo *)0x0121B6D8;
const CommandInfo	* g_consoleCommandsEnd =	(CommandInfo *)0x0121E6D0;
const CommandInfo	* g_scriptCommandsStart =	(CommandInfo *)0x0121E6F8;
const CommandInfo	* g_scriptCommandsEnd =		(CommandInfo *)0x01225890;

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

// 1.4.20.0 runtime
static const CommandTable::PatchLocation kPatch_ScriptCommands_Start[] =
{
	{	0x0051127B, 0x00 },
	{	0x00511444, 0x04 },
	{	0x005114DD, 0x08 },
	{	0x005124C7, 0x00 },
	{	0x00515A7F, 0x00 },
	{	0x0053C889, 0x0C },
	{	0x0053C8A1, 0x00 },
	{	0x0053C8B9, 0x04 },
	{	0x0053C8D5, 0x0C },
	{	0x0053C8EF, 0x04 },
	{	0x0053C90D, 0x00 },
	{	0x0053C92F, 0x00 },
	{	0x0053C94D, 0x04 },
	{	0x0053C973, 0x00 },
	{	0x0053C98A, 0x00 },
	{	0x005E5D99, 0x20 },
	{	0x005E5DA5, 0x10 },
	{	0x005E5E6E, 0x12 },
	{	0x005E5EB1, 0x12 },
	{	0x005E5EBD, 0x14 },
	{	0x005E5EF8, 0x12 },
	{	0x005E5F05, 0x14 },
	{	0x005E5F66, 0x12 },
	{	0x005E5F72, 0x14 },
	{	0x005E5FA0, 0x12 },
	{	0x005E6011, 0x12 },
	{	0x005E6043, 0x12 },
	{	0x005E604F, 0x14 },
	{	0x005E60A5, 0x12 },
	{	0x005E60E3, 0x12 },
	{	0x005E60EF, 0x14 },
	{	0x005E6198, 0x12 },
	{	0x005E61C7, 0x14 },
	{	0x005E62A4, 0x12 },
	{	0x005E62C6, 0x14 },
	{	0x005E63DE, 0x12 },
	{	0x005E6428, 0x12 },
	{	0x005E6438, 0x14 },
	{	0x005E64D1, 0x14 },
	{	0x0069AF1C, 0x12 },
	{	0x0069AF49, 0x14 },
	{	0 },
};

static const CommandTable::PatchLocation kPatch_ScriptCommands_End[] =
{
	{	0x00511382, 0x08 },
	{	0x0051146F, 0x04 },
	{	0 },
};

static const CommandTable::PatchLocation kPatch_ScriptCommands_MaxIdx[] =
{
	{	0x004FD917 + 1, 0 },
	{	0x00511269 + 2,	(UInt32)(-0x1001) },
	{	0x00511380 + 6, 0 },
	{	0x005124B6 + 1,	(UInt32)(-0x1001) },
	{	0x00515A71 + 2,	(UInt32)(-0x1001) },
	{	0x005E51ED + 2,	(UInt32)(-0x1001) },
	{	0x005E51FD + 1,	(UInt32)(-0x1001) },
	{	0x005E5209 + 2,	(UInt32)(-0x1001) },

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

	g_commandTable.Add();	// padding command
}

void Hooks_ObScript_Commit(void)
{
	// patch the exe
	g_commandTable.PatchEXE(&kPatchSet);
}
