#pragma once

#include "skse/GameTypes.h"
#include "skse/GameFormComponents.h"

// 9C
class BSNavmesh
{
public:
	// 28
	struct Data50
	{
		UInt32	unk00;	// 00 - init'd to 0
		UInt32	unk04;	// 04
		UInt32	unk08;	// 08
		UInt32	unk0C;	// 0C - init'd to 7F7FFFFF
		UInt32	unk10;	// 10
		UInt32	unk14;	// 14
		UInt32	unk18;	// 18
		UInt32	unk1C;	// 1C
		UInt32	unk20;	// 20
		UInt32	unk24;	// 24 - init'd to 0
	};

	// 10
	class Data84
	{
	public:
		virtual	~Data84();

		//		void	** _vtbl;	// 00
		UInt32	unk04;		// 04 - ctor arg, prime?
		void	* unk08;	// 08 - buf, len = unk04 * 4
		UInt32	unk0C;		// 0C
	};

	virtual ~BSNavmesh();

	//	void	** _vtbl;						// 00
	BSIntrusiveRefCounted		refCount;	// 04
	TESActorBaseData::Data2C	unk08;		// 08
	TESActorBaseData::Data2C	unk14;		// 14
	TESActorBaseData::Data2C	unk20;		// 20
	TESActorBaseData::Data2C	unk2C;		// 2C
	TESActorBaseData::Data2C	unk38;		// 38
	TESActorBaseData::Data2C	unk44;		// 44
	Data50						unk50;		// 50
	TESActorBaseData::Data2C	unk78;		// 78
	Data84						* unk84;	// 84
	TESActorBaseData::Data2C	unk88;		// 88
	UInt32						unk94;		// 94
	UInt32						unk98;		// 98
};

STATIC_ASSERT(sizeof(BSNavmesh) == 0x9C);

// 8
class BSNavmeshInfoMap
{
public:
	virtual ~BSNavmeshInfoMap();

	virtual void	Unk_01(void);
	virtual void	Unk_02(void);
	virtual void	Unk_03(void);
	virtual void	Unk_04(void);
	virtual void	Unk_05(void);

//	void	** _vtbl;	// 00
	UInt32	unk04;		// 04
};

// ?
class BSPrecomputedNavmeshInfoPathMap
{
public:
};

// 2C
class PrecomputedNavmeshInfoPathMap : public BSPrecomputedNavmeshInfoPathMap
{
public:
	// 20
	struct Data0C
	{
		UInt32	unk00;		// 00
		UInt32	unk04;		// 04
		UInt32	unk08;		// 08 - 0
		UInt32	unk0C;		// 0C - 0
		UInt32	unk10;		// 10 - 0
		void	* unk14;	// 14 - ptr to 0xDEADBEEF
		UInt32	unk18;		// 18
		UInt32	unk1C;		// 1C
	};

	TESActorBaseData::Data2C	unk00;	// 00
	Data0C						unk0C;	// 0C
};

STATIC_ASSERT(sizeof(PrecomputedNavmeshInfoPathMap) == 0x2C);
