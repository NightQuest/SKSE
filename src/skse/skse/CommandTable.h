#pragma once

struct ParamInfo;
class TESObjectREFR;
class Script;
class ScriptEventList;
class ScriptLineBuffer;
class ScriptBuffer;

#define COMMAND_ARGS		ParamInfo * paramInfo, void * scriptData, TESObjectREFR * thisObj, TESObjectREFR * containingObj, Script * scriptObj, ScriptEventList * eventList, double * result, UInt32 * opcodeOffsetPtr
#define COMMAND_ARGS_EVAL	TESObjectREFR * thisObj, void * arg1, void * arg2, double * result

typedef bool (* Cmd_Execute)(COMMAND_ARGS);
bool Cmd_Default_Execute(COMMAND_ARGS);

typedef bool (* Cmd_Parse)(UInt32 numParams, ParamInfo * paramInfo, ScriptLineBuffer * lineBuf, ScriptBuffer * scriptBuf);
bool Cmd_Default_Parse(UInt32 numParams, ParamInfo * paramInfo, ScriptLineBuffer * lineBuf, ScriptBuffer * scriptBuf);

typedef bool (* Cmd_Eval)(COMMAND_ARGS_EVAL);
bool Cmd_Default_Eval(COMMAND_ARGS_EVAL);


#ifdef RUNTIME
#define HANDLER(x)	x
#define HANDLER_EVAL(x)	x
#else
#define HANDLER(x)	Cmd_Default_Execute
#define HANDLER_EVAL(x)	Cmd_Default_Eval
#endif

struct ParamInfo
{
	const char	* typeStr;
	UInt32		typeID;		// ParamType
	UInt32		isOptional;	// do other bits do things?
};

struct CommandInfo
{
	const char	* longName;		// 00
	const char	* shortName;	// 04
	UInt32		opcode;			// 08
	const char	* helpText;		// 0C
	UInt16		needsParent;	// 10
	UInt16		numParams;		// 12
	ParamInfo	* params;		// 14

	// handlers
	Cmd_Execute	execute;		// 18
	Cmd_Parse	parse;			// 1C
	Cmd_Eval	eval;			// 20

	UInt32		flags;			// 24
};

void Commands_Dump(void);
