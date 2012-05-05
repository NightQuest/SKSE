#pragma once

#include "skse/Utilities.h"

// core library types (lists, strings, vectors)
// preferably only the ones that bethesda created (non-netimmerse)

class BSIntrusiveRefCounted
{
public:
	volatile UInt32	m_refCount;	// 00
};

// 04
template <typename T>
class BSTSmartPointer
{
public:
	// refcounted
	T	* ptr;
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
	struct Ref
	{
		const char	* data;

		MEMBER_FN_PREFIX(Ref);
		DEFINE_MEMBER_FN(ctor, Ref *, 0x00A38CA0, const char * buf);
		DEFINE_MEMBER_FN(Set, Ref *, 0x00A38CF0, const char * buf);
		DEFINE_MEMBER_FN(Release, void, 0x00A38C90);
	};

	struct Lock
	{
		SimpleLock	lock;
	};

	StringCache();
	~StringCache();

	static StringCache *	GetSingleton(void);

	Lock *	GetLock(UInt32 crc16);

private:
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

	Entry	* table[0x10000];	// crc16
	Lock	locks[0x20];		// crc16 & 0x1F
	UInt8	unk;
};

// 08
class BSString
{
public:
	const char *	Get(void);

private:
	char	* m_data;	// 00
	UInt16	m_dataLen;	// 04
	UInt16	m_bufLen;	// 06
};


template <class T>
class tArray
{
public:
	struct Array {
		T* entries;
		UInt32 unk4;
	};

	Array arr;
	UInt32 count;
	
	bool GetNthItem(UInt32 index, T& pT)
	{
		if (index < count) {
			pT = arr.entries[index];
			return true;
		}
		return false;
	}
};

typedef tArray<UInt32> UnkArray;

template <class T>
class tSimpleArray
{
public:
	T* entries;
	UInt32 count;


	bool GetNthItem(UInt32 index, T& pT)
	{
		if (index < count) {
			pT = entries[index];
			return true;
		}
		return false;
	}
};
