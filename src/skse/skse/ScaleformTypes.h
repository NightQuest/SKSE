#pragma once

#include "skse/Utilities.h"

// not sure why they nest it like this, but whatever
class GRefCountImplCore
{
public:
	GRefCountImplCore() { }
	virtual ~GRefCountImplCore() { }

//	void	** _vtbl;			// 00
	volatile SInt32	refCount;	// 04
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
	DEFINE_MEMBER_FN(Init, GString *, 0x0090B840, const char * str);
};

#pragma warning (pop)

template <typename T>
class GArray
{
public:
	// ### todo
};
