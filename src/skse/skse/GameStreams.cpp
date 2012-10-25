#include "GameStreams.h"

BSResourceNiBinaryStream::BSResourceNiBinaryStream()
:readFn(NULL), writeFn(NULL), unk10(NULL), unk14(NULL), offset(0)
{
	//
}

BSResourceNiBinaryStream::BSResourceNiBinaryStream(const char * path)
:readFn(NULL), writeFn(NULL), unk10(NULL), unk14(NULL), offset(0)
{
	CALL_MEMBER_FN(this, Construct)(path, 0, 0);
}

BSResourceNiBinaryStream::~BSResourceNiBinaryStream()
{
	CALL_MEMBER_FN(this, Destroy)();
}

bool BSResourceNiBinaryStream::IsValid(void)
{
	return CALL_MEMBER_FN(this, IsValid)();
}

void BSResourceNiBinaryStream::Seek(SInt32 delta)
{
	CALL_MEMBER_FN(this, Seek)(delta);
}

UInt32 BSResourceNiBinaryStream::GetOffset(void)
{
	return CALL_MEMBER_FN(this, GetOffset)();
}

void BSResourceNiBinaryStream::EnableEndianSwap(bool swap)
{
	CALL_MEMBER_FN(this, EnableEndianSwap)(swap);
}

UInt32 BSResourceNiBinaryStream::ReadLine(char * dst, UInt32 dstLen, UInt32 terminator)
{
	return CALL_MEMBER_FN(this, ReadLine)(dst, dstLen, terminator);
}

UInt32 BSResourceNiBinaryStream::Read(char * dst, UInt32 len)
{
	return CALL_MEMBER_FN(this, Read)(dst, len);
}

UInt32 BSResourceNiBinaryStream::Write(char * src, UInt32 len)
{
	return CALL_MEMBER_FN(this, Write)(src, len);
}
