#include "CommandTable.h"

CommandInfo	* g_blockTypeStart =		(CommandInfo *)0x01426170;
CommandInfo	* g_blockTypeEnd =			(CommandInfo *)0x014266E8;
CommandInfo	* g_consoleCommandsStart =	(CommandInfo *)0x01426710;
CommandInfo	* g_consoleCommandsEnd =	(CommandInfo *)0x014297D0;
CommandInfo	* g_scriptCommandsStart =	(CommandInfo *)0x014297F8;
CommandInfo	* g_scriptCommandsEnd =		(CommandInfo *)0x01430990;

bool IsEmptyStr(const char * data)
{
	return !data || !data[0];
}

void DumpCommands(CommandInfo * start, CommandInfo * end)
{
	for(CommandInfo * iter = start; iter <= end; ++iter)
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
	for(CommandInfo * iter = start; iter <= end; ++iter)
	{
		if(iter->execute == (Cmd_Execute)0x005AC770)
		{
			_MESSAGE("%s", iter->longName);
		}
	}
}

void Commands_Dump(void)
{
	_MESSAGE("block types:");
	DumpCommands(g_blockTypeStart, g_blockTypeEnd);
	_MESSAGE("console commands");
	DumpCommands(g_consoleCommandsStart, g_consoleCommandsEnd);
	_MESSAGE("script commands");
	DumpCommands(g_scriptCommandsStart, g_scriptCommandsEnd);
}
