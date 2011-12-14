#pragma once

#include "skse/Utilities.h"

// core library types (lists, strings, vectors)
// preferably only the ones that bethesda created (non-netimmerse)

class BSIntrusiveRefCounted
{
public:
	UInt32	m_refCount;	// 00
};

class SimpleLock
{
private:
	volatile UInt32	threadID;
	UInt32			lockCount;
};

// refcounted threadsafe string storage
// use StringCache::Ref to access everything, other internals are for documentation only
class StringCache
{
public:
	struct Lock
	{
		SimpleLock	lock;
	};

	struct Entry
	{
		Entry	* next;		// 00
		union
		{
			struct  
			{
				UInt16	refCount;	// invalid if 0x8000 is set
				UInt16	hash;
			};
			UInt32	refCountAndHash;
		} state;	// 04
		UInt32	length;		// 08
		// data follows
	};

	struct Ref
	{
		const char	* data;

		MEMBER_FN_PREFIX(Ref);
		DEFINE_MEMBER_FN(Get, Ref *, 0x00BDA410, const char * buf);
		DEFINE_MEMBER_FN(Release, void, 0x00BEC150);
	};

	StringCache();
	~StringCache();

	static StringCache *	GetSingleton(void);

	Lock *	GetLock(UInt32 crc16);

private:
	Entry	* table[0x10000];	// crc16
	Lock	locks[0x20];		// crc16 & 0x1F
	UInt8	unk;
};
