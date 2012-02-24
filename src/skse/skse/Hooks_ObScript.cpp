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

// 1.4.27.0 runtime
static const CommandTable::PatchLocation kPatch_ScriptCommands_Start[] =
{
	{	0x00511C9B, 0x00 },
	{	0x00511E64, 0x04 },
	{	0x00511EFD, 0x08 },
	{	0x00512F17, 0x00 },
	{	0x005164CF, 0x00 },
	{	0x0053D329, 0x0C },
	{	0x0053D341, 0x00 },
	{	0x0053D359, 0x04 },
	{	0x0053D375, 0x0C },
	{	0x0053D38F, 0x04 },
	{	0x0053D3AD, 0x00 },
	{	0x0053D3CF, 0x00 },
	{	0x0053D3ED, 0x04 },
	{	0x0053D413, 0x00 },
	{	0x0053D42A, 0x00 },
	{	0x005E5369, 0x20 },
	{	0x005E5375, 0x10 },
	{	0x005E543E, 0x12 },
	{	0x005E5481, 0x12 },
	{	0x005E548D, 0x14 },
	{	0x005E54C8, 0x12 },
	{	0x005E54D5, 0x14 },
	{	0x005E5536, 0x12 },
	{	0x005E5542, 0x14 },
	{	0x005E5570, 0x12 },
	{	0x005E55E1, 0x12 },
	{	0x005E5613, 0x12 },
	{	0x005E561F, 0x14 },
	{	0x005E5675, 0x12 },
	{	0x005E56B3, 0x12 },
	{	0x005E56BF, 0x14 },
	{	0x005E5768, 0x12 },
	{	0x005E5797, 0x14 },
	{	0x005E5874, 0x12 },
	{	0x005E5896, 0x14 },
	{	0x005E59AE, 0x12 },
	{	0x005E59F8, 0x12 },
	{	0x005E5A08, 0x14 },
	{	0x005E5AA1, 0x14 },
	{	0x0069AE8C, 0x12 },
	{	0x0069AEB9, 0x14 },
	{	0 },
};

static const CommandTable::PatchLocation kPatch_ScriptCommands_End[] =
{
	{	0x00511DA2, 0x08 },
	{	0x00511E8F, 0x04 },
	{	0 },
};

static const CommandTable::PatchLocation kPatch_ScriptCommands_MaxIdx[] =
{
	{	0x004FE290 + 0x0087 + 1,	0 },
	{	0x00511C60 + 0x0029 + 2,	(UInt32)(-0x1001) },
	{	0x00511DA0 + 0x0000 + 6,	0 },
	{	0x00512DB0 + 0x0156 + 1,	(UInt32)(-0x1001) },
	{	0x00515D70 + 0x0751 + 2,	(UInt32)(-0x1001) },
	{	0x005E47B0 + 0x000D + 2,	(UInt32)(-0x1001) },
	{	0x005E47B0 + 0x001D + 1,	(UInt32)(-0x1001) },
	{	0x005E47B0 + 0x0029 + 2,	(UInt32)(-0x1001) },

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
