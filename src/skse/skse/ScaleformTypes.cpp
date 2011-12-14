#include "ScaleformTypes.h"

GString::Data * GString::GetData(void)
{
	return (Data *)(data.heapInfo & ~kHeapInfoMask);
}

UInt32 GString::GetHeapInfo(void)
{
	return data.heapInfo & kHeapInfoMask;
}
