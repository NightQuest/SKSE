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

// 1.4.21.0 runtime
static const CommandTable::PatchLocation kPatch_ScriptCommands_Start[] =
{
	{	0x0051148B, 0x00 },
	{	0x00511654, 0x04 },
	{	0x005116ED, 0x08 },
	{	0x00512707, 0x00 },
	{	0x00515CBF, 0x00 },
	{	0x0053CAC9, 0x0C },
	{	0x0053CAE1, 0x00 },
	{	0x0053CAF9, 0x04 },
	{	0x0053CB15, 0x0C },
	{	0x0053CB2F, 0x04 },
	{	0x0053CB4D, 0x00 },
	{	0x0053CB6F, 0x00 },
	{	0x0053CB8D, 0x04 },
	{	0x0053CBB3, 0x00 },
	{	0x0053CBCA, 0x00 },
	{	0x005E52B9, 0x20 },
	{	0x005E52C5, 0x10 },
	{	0x005E538E, 0x12 },
	{	0x005E53D1, 0x12 },
	{	0x005E53DD, 0x14 },
	{	0x005E5418, 0x12 },
	{	0x005E5425, 0x14 },
	{	0x005E5486, 0x12 },
	{	0x005E5492, 0x14 },
	{	0x005E54C0, 0x12 },
	{	0x005E5531, 0x12 },
	{	0x005E5563, 0x12 },
	{	0x005E556F, 0x14 },
	{	0x005E55C5, 0x12 },
	{	0x005E5603, 0x12 },
	{	0x005E560F, 0x14 },
	{	0x005E56B8, 0x12 },
	{	0x005E56E7, 0x14 },
	{	0x005E57C4, 0x12 },
	{	0x005E57E6, 0x14 },
	{	0x005E58FE, 0x12 },
	{	0x005E5948, 0x12 },
	{	0x005E5958, 0x14 },
	{	0x005E59F1, 0x14 },
	{	0x0069A91C, 0x12 },
	{	0x0069A949, 0x14 },
	{	0 },
};

static const CommandTable::PatchLocation kPatch_ScriptCommands_End[] =
{
	{	0x00511592, 0x08 },
	{	0x0051167F, 0x04 },
	{	0 },
};

static const CommandTable::PatchLocation kPatch_ScriptCommands_MaxIdx[] =
{
	{	0x004FDAD7 + 1, 0 },
	{	0x00511479 + 2,	(UInt32)(-0x1001) },
	{	0x00511590 + 6, 0 },
	{	0x005126F6 + 1,	(UInt32)(-0x1001) },
	{	0x00515CB1 + 2,	(UInt32)(-0x1001) },
	{	0x005E470D + 2,	(UInt32)(-0x1001) },
	{	0x005E471D + 1,	(UInt32)(-0x1001) },
	{	0x005E4729 + 2,	(UInt32)(-0x1001) },

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
