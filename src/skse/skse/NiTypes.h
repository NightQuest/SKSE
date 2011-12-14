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

	virtual UInt32	GetBucket(UInt32 hash);					// return hash % numBuckets;
	virtual bool	CompareHash(UInt32 lhs, UInt32 rhs);	// return lhs == rhs;
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
