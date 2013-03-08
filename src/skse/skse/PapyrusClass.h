#pragma once

#include "skse/GameTypes.h"

// SkyrimScript::Store, derived from BSScript::IStore, derived from BSStorage, derived from BSIntrusiveRefCounted
class VMDataStore
{
public:
	virtual ~VMDataStore();
	virtual void	Unk_01(void);
	virtual void	Unk_02(void);
	virtual bool	Seek(SInt32 offset, UInt32 base);
	virtual bool	Read(UInt32 len, void * buf);
	virtual bool	Write(UInt32 len, void * buf);

	// BSScript::IStore
	virtual bool	Open(const char * name);
	virtual void	Unk_07(void);
	virtual void	Unk_08(void);	// called on error
	virtual void	Unk_09(void);
	virtual void	Unk_0A(void);
	virtual void	Unk_0B(void);

//	void	** _vtbl;		// 00
	UInt32	refCount;		// 04
	UInt8	byteSwapped;	// 08
	UInt8	pad09[3];		// 09
};

// 20
//template <typename Item, typename Key>
struct VMHashTable
{
	typedef void *					Item;
	typedef void *					Key;

	typedef tHashSet <Item, Key>	Table;

	UInt32	unk00;		// 00 - not init'd
	Table	data;		// 04
};

// 130+
class VMClass
{
public:
	// 18
	struct DebugInfo
	{
		// 10
		struct Unk08
		{
			struct Unk00
			{
				UInt32	unk00;		// 00
				UInt32	unk04;		// 04
				void	* unk08;	// 08
				UInt32	unk0C;		// 0C
				UInt32	unk10;		// 10
				UInt32	unk14;		// 14
				UInt32	unk18;		// 18
			};

			Unk00	* unk00;	// 00
			UInt32	unk04;		// 04
			UInt32	unk08;		// 08
			UInt32	unk0C;		// 0C
		};

		time_t	srcModTime;		// 00
		Unk08	unk08;			// 08
	};

	BSFixedString	name;			// 000
	UInt32			unk004;			// 004 - not init'd
	time_t			buildTime;		// 008
	BSFixedString	buildUser;		// 010
	BSFixedString	buildMachine;	// 014
	UInt8			debugFlags;		// 018
	UInt8			pad019[3];		// 019
	UInt32			unk01C;			// 01C - not init'd
	DebugInfo		debugInfo;		// 020
	VMHashTable		userFlags;		// 038
	BSFixedString	unk058;			// 058
	BSFixedString	unk05C;			// 05C
	BSFixedString	unk060;			// 060
	UInt32			unk064;			// 064
	VMHashTable		unk068;			// 068
	VMHashTable		unk088;			// 088
	VMHashTable		unk0A8;			// 0A8
	VMHashTable		unk0C8;			// 0C8
	VMHashTable		unk0E8;			// 0E8
	UInt32			unk108;			// 108
	VMHashTable		unk10C;			// 10C
	BSFixedString	unk12C;			// 12C
};

STATIC_ASSERT(sizeof(time_t) == 8);
STATIC_ASSERT(sizeof(VMClass) == 0x130);
STATIC_ASSERT(offsetof(VMClass, unk058) == 0x058);
STATIC_ASSERT(offsetof(VMClass, unk12C) == 0x12C);

// 20
class VMClassLoader
{
public:
	virtual ~VMClassLoader();
	virtual VMClassLoader *		Create(void);
	virtual void				SetDataStore(VMDataStore ** dataStoreHandle);	// probably a safe ptr
	virtual bool				Load(const char * name, VMClass * out);

	// 10
	struct StringTable
	{
		// 100C
		struct Page
		{
			char	data[0x1000];	// 0000
			char	* begin;		// 1000
			char	* end;			// 1004
			Page	* next;			// 1008
		};

		char			** stringData;	// 00
		Page			* dataPage;		// 04
		BSFixedString	* fixedStrings;	// 08 - populated on lookup
		UInt16			numStrings;		// 0C
		UInt8			pad0E[2];		// 0E
	};

//	void		** _vtbl;		// 00
	void		* unk04;		// 04
	VMDataStore	* dataStore;	// 08
	StringTable	stringTable;	// 0C
	UInt8		verMajor;		// 1C
	UInt8		verMinor;		// 1D
	UInt8		flags;			// 1E
	UInt8		pad1F;			// 1F
};

STATIC_ASSERT(sizeof(VMClassLoader::StringTable::Page) == 0x100C);
STATIC_ASSERT(sizeof(VMClassLoader::StringTable) == 0x10);
