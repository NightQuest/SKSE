#pragma once

#include "skse/Utilities.h"
#include "skse/PapyrusVM.h"

class VMState;
class VMValue;
class PapyrusClassRegistry;

class VMArgList
{
public:
	VMArgList();
	~VMArgList();

	MEMBER_FN_PREFIX(VMArgList);
	DEFINE_MEMBER_FN(GetOffset, UInt32, 0x00C1FB60, VMState * state);
	DEFINE_MEMBER_FN(Get, VMValue *, 0x00C20170, VMState * state, UInt32 idx, UInt32 offset);
};

template <typename T>
void PackValue(VMValue * dst, T * src);

template <typename T>
void UnpackValue(T * dst, VMValue * src, PapyrusClassRegistry * registry);
