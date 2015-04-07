#pragma once

#include "skse/Utilities.h"
#include "skse/ScaleformAPI.h"

// not sure why they nest it like this, but whatever
class GRefCountImplCore
{
public:
	GRefCountImplCore() :refCount(1) { }
	virtual ~GRefCountImplCore() { }

//	void	** _vtbl;			// 00
	volatile SInt32	refCount;	// 04

	// redirect new/delete to the scaleform heap
	static void * operator new(std::size_t size)
	{
		return ScaleformHeap_Allocate(size);
	}

	static void * operator new(std::size_t size, const std::nothrow_t &)
	{
		return ScaleformHeap_Allocate(size);
	}

	// placement new
	static void * operator new(std::size_t size, void * ptr)
	{
		return ptr;
	}

	static void operator delete(void * ptr)
	{
		ScaleformHeap_Free(ptr);
	}

	// placement delete
	static void operator delete(void *, void *)
	{
		//
	}

	void	AddRef(void)
	{
		InterlockedIncrement(&refCount);
	}

	void	Release(void)
	{
		if(InterlockedDecrement(&refCount) == 0)
		{
			delete this;
		}
	}
};

class GRefCountImpl : public GRefCountImplCore
{
public:
	GRefCountImpl() { }
	virtual ~GRefCountImpl() { }
};

class GRefCountBaseStatImpl : public GRefCountImpl
{
public:
	GRefCountBaseStatImpl() { }
	virtual ~GRefCountBaseStatImpl() { }
};

class GRefCountBase : public GRefCountBaseStatImpl
{
public:
	GRefCountBase() { }
	virtual ~GRefCountBase() { }
};

#pragma warning (push)
#pragma warning (disable : 4200)

class GString
{
public:
	GString()	{ }
	~GString()	{ }

	enum
	{
		kHeapInfoMask =	3,
	};

	struct Data
	{
		UInt32	len;
		SInt32	refCount;
		char	data[0];

		void	IncRef(void);
		void	Release(void);
	};

	union
	{
		Data	* ptr;		// do not use directly, clear lower 3 bits first
		UInt32	heapInfo;
	} data;

	Data *	GetData(void);
	UInt32	GetHeapInfo(void);

	void	Destroy(void);

	MEMBER_FN_PREFIX(GString);
};

#pragma warning (pop)

template <typename T>
class GArray
{
public:
	// ### todo
};
