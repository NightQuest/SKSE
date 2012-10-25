#pragma once

#include "skse/Utilities.h"

// class NiBinaryStream
// class NiFile : public NiBinaryStream
// class NiMemStream : public NiBinaryStream
// class OutputInfoStream : public NiBinaryStream
// class BSResourceNiBinaryStream : public NiBinaryStream
// class BSResourceStreamParser : public BSResourceNiBinaryStream
// class BSStreamParserData

// Not sure if this is right
/*class NiBinaryStream
{
public:
	virtual ~NiBinaryStream() { };

	virtual bool	IsValid(void) = 0;
	virtual void	Seek(SInt32 delta) = 0;
	virtual UInt32	GetOffset(void) { return 0; }
	virtual void	Unk_04(void) { }
	virtual void	EnableEndianSwap(bool swap) = 0;
};*/

class BSResourceNiBinaryStream// : public NiBinaryStream
{
public:
	BSResourceNiBinaryStream();
	BSResourceNiBinaryStream(const char * path);
	virtual ~BSResourceNiBinaryStream();

	// stub implementations
	virtual bool	IsValid(void);
	virtual void	Seek(SInt32 delta);
	virtual UInt32	GetOffset(void);
	virtual void	Unk_04(void) { }
	virtual void	EnableEndianSwap(bool swap);

//	void	** _vtbl;	// 00
//	UInt32	pad04;		// 04 - align for UInt64
	void	* readFn;	// 08
	void	* writeFn;	// 0C
	void	* unk10;	// 10
	void	* unk14;	// 14
	UInt64	offset;		// 18

	MEMBER_FN_PREFIX(BSResourceNiBinaryStream);
	DEFINE_MEMBER_FN(Construct, BSResourceNiBinaryStream *, 0x00AC5D50, const char * filePath, UInt32 unk1, UInt32 unk2);	// unk1 = 0, unk2 = 0
	DEFINE_MEMBER_FN(ReadLine, UInt32, 0x00AC5CD0, char * dst, UInt32 dstLen, UInt32 terminator);
	DEFINE_MEMBER_FN(Read, UInt32, 0x00AC59D0, void * dst, UInt32 len);
	DEFINE_MEMBER_FN(Write, UInt32, 0x00AC5A50, void * src, UInt32 len);
	DEFINE_MEMBER_FN(Destroy, void, 0x00AC5F70);

	DEFINE_MEMBER_FN(IsValid, bool, 0x00AC59C0, void);
	DEFINE_MEMBER_FN(Seek, void, 0x00AC5970, SInt32);
	DEFINE_MEMBER_FN(GetOffset, UInt32, 0x00ECF850, void);
	DEFINE_MEMBER_FN(EnableEndianSwap, void, 0x00AC5CA0, bool);

	UInt32 ReadLine(char * dst, UInt32 dstLen, UInt32 terminator);
	UInt32 Read(char * dst, UInt32 len);
	UInt32 Write(char * src, UInt32 len);
};

STATIC_ASSERT(offsetof(BSResourceNiBinaryStream, readFn) == 0x08);
STATIC_ASSERT(offsetof(BSResourceNiBinaryStream, offset) == 0x18);
STATIC_ASSERT(sizeof(BSResourceNiBinaryStream) == 0x20);
