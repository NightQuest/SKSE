#pragma once

// 4
template <typename T>
class NiPointer
{
public:
	T	* m_pObject;
};

// 10
class NiQuaternion
{
public:
	// w is first

	float	m_fW;	// 0
	float	m_fX;	// 4
	float	m_fY;	// 8
	float	m_fZ;	// C
};

// C
class NiPoint3
{
public:
	float	x;	// 0
	float	y;	// 4
	float	z;	// 8
};

// 10
class NiColorA
{
public:
	float	r;	// 0
	float	g;	// 4
	float	b;	// 8
	float	a;	// C
};

// 24
class NiMatrix33
{
public:
	float	data[9];
};

STATIC_ASSERT(sizeof(NiMatrix33) == 0x24);

// 34
class NiTransform
{
public:
	NiMatrix33	rot;	// 00
	NiPoint3	pos;	// 24
	float		scale;	// 30
};

STATIC_ASSERT(sizeof(NiTransform) == 0x34);

// 10
class NiBound
{
public:
	NiPoint3	pos;
	float		radius;
};

STATIC_ASSERT(sizeof(NiBound) == 0x10);

// 10
// derives from NiTMapBase, we don't bother
template <typename T_key, typename T_data>
class NiTMap
{
public:
	virtual ~NiTMap();

	struct NiTMapItem
	{
		NiTMapItem	* next;
		T_key		key;
		T_data		data;
	};

	T_data	Get(T_key key)
	{
		UInt32	bucket = GetBucket(key);

		for(NiTMapItem * iter = buckets[bucket]; iter; iter = iter->next)
		{
			if(Compare(iter->key, key))
			{
				return iter->data;
			}
		}

		return T_data();
	}

	virtual UInt32	GetBucket(T_key key);					// return hash % numBuckets;
	virtual bool	Compare(T_key lhs, T_key rhs);			// return lhs == rhs;
	virtual void	FillItem(NiTMapItem * item, T_key key, T_data data);
															// item->key = key; item->data = data;
	virtual void	Fn_04(UInt32 arg);	// nop
	virtual NiTMapItem *	AllocItem(void);				// return new NiTMapItem;
	virtual void	FreeItem(NiTMapItem * item);			// item->data = 0; delete item;

//	void		** _vtbl;	// 00
	UInt32		numBuckets;	// 04
	NiTMapItem	** buckets;	// 08
	UInt32		numEntries;	// 0C
};

// 10
template <typename T_key, typename T_data>
class NiTPointerMap : NiTMap <T_key, T_data>
{
public:
};

// 10
template <typename T>
class NiTArray
{
public:
	NiTArray();
	virtual ~NiTArray();

	// sparse array, can have NULL entries that should be skipped
	// iterate from 0 to m_emptyRunStart - 1

//	void	** _vtbl;			// 00
	T		* m_data;			// 04
	UInt16	m_arrayBufLen;		// 08 - max elements storable in m_data
	UInt16	m_emptyRunStart;	// 0A - index of beginning of empty slot run
	UInt16	m_size;				// 0C - number of filled slots
	UInt16	m_growSize;			// 0E - number of slots to grow m_data by
};

STATIC_ASSERT(sizeof(NiTArray <void *>) == 0x10);

// 18
template <typename T>
class NiTLargeArray
{
public:
	NiTLargeArray();
	virtual ~NiTLargeArray();

//	void	** _vtbl;			// 00
	T		* m_data;			// 04
	UInt32	m_arrayBufLen;		// 08 - max elements storable in m_data
	UInt32	m_emptyRunStart;	// 0C - index of beginning of empty slot run
	UInt32	m_size;				// 10 - number of filled slots
	UInt32	m_growSize;			// 14 - number of slots to grow m_data by
};
