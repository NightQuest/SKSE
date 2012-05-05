#pragma once

namespace papyrusMath 
{
	UInt32 LeftShift(UInt32 value, UInt32 shiftBy);
	UInt32 RightShift(UInt32 value, UInt32 shiftBy);
	UInt32 LogicalAnd(UInt32 arg1, UInt32 arg2);
	UInt32 LogicalOr(UInt32 arg1, UInt32 arg2);
	UInt32 LogicalXor(UInt32 arg1, UInt32 arg2);
	UInt32 LogicalNot(UInt32 arg1);
}
