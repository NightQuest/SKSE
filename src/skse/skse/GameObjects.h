#pragma once

#include "skse/NiObjects.h"
#include "skse/GameForms.h"

// TESObject and children

// 14+
class TESObject : public TESForm
{
public:
	virtual UInt32	Unk_39(void);
	virtual bool	Unk_3A(void);
	virtual UInt32	Unk_3B(void);
	virtual bool	Unk_3C(void);
	virtual void	Unk_3D(UInt32 arg);
	virtual UInt32	Unk_3E(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_3F(void * arg);
	virtual bool	Unk_40(void);
	virtual bool	Unk_41(void);
	virtual void	Unk_42(void);
	virtual void	Unk_43(UInt32 arg0, UInt32 arg1);
	virtual UInt32	Unk_44(void);
	virtual UInt32	Unk_45(void);
	virtual void *	Unk_46(void);
};

// 20
class TESBoundObject : public TESObject
{
public:
	struct Bound
	{
		UInt16	x;
		UInt16	y;
		UInt16	z;
	};

	virtual void	Unk_47(UInt32 arg);
	virtual UInt32	Unk_48(void);
	virtual UInt32	Unk_49(UInt32 arg);	// return Unk_3E(arg, 0);
	virtual bool	Unk_4A(void);
	virtual bool	Unk_4B(void * arg0, BSString * dst);	// steal/take string
	virtual bool	Unk_4C(void * arg0, UInt8 arg1, UInt32 arg2, float arg3);
	virtual void	Unk_4D(UInt32 arg);
	virtual void	Unk_4E(UInt32 arg);
	virtual void	Unk_4F(void);
	virtual void	Unk_50(void);
	virtual void	Unk_51(void);

	Bound	bounds;		// 14
	Bound	bounds2;	// 1A
};

STATIC_ASSERT(sizeof(TESBoundObject) == 0x20);

// 2C
class BGSAcousticSpace : public TESBoundObject
{
public:
	TESForm	* loopingSound;	// 20
	TESForm	* soundRegion;	// 24
	TESForm	* reverbType;	// 28
};

// 4C
class BGSAddonNode : public TESBoundObject
{
public:
	// parents
	TESModelTextureSwap	texSwap;	// 20

	// members
	UInt32	unk3C;		// 3C
	UInt32	unk40;		// 40
	UInt8	unk44[4];	// 44
	UInt32	unk48;		// 48
};

// 40
class BGSArtObject : public TESBoundObject
{
public:
	// parents
	TESModelTextureSwap	texSwap;	// 20

	// members
	UInt32	unk3C;	// 3C
};

// 34
class BGSCloudClusterForm : public TESBoundObject
{
public:
	// parents
	TESModel	model;	// 20
};

// 38
class BGSDualCastData : public TESBoundObject
{
public:
	// 18
	struct Data
	{
		UInt32	unk00;	// 00
		UInt32	unk04;	// 04
		UInt32	unk08;	// 08
		UInt32	unk0C;	// 0C
		UInt32	unk10;	// 10
		UInt32	unk14;	// 14
	};

	Data	unk20;	// 20
};

// 8C
class BGSExplosion : public TESBoundObject
{
public:
	// parents
	TESFullName			fullName;		// 20
	TESModel			model;			// 28
	TESEnchantableForm	enchantment;	// 3C
	BGSPreloadable		preloadable;	// 4C
	TESImageSpaceModifiableForm	imageSpaceModifier;	// 50

	// members

	// 34
	struct Data
	{
		UInt32	unk00;	// 00
		UInt32	unk04;	// 04
		UInt32	unk08;	// 08
		UInt32	unk0C;	// 0C
		UInt32	unk10;	// 10
		UInt32	unk14;	// 14
		UInt32	unk18;	// 18
		UInt32	unk1C;	// 1C
		UInt32	unk20;	// 20
		UInt32	unk24;	// 24
		UInt32	unk28;	// 28
		UInt32	unk2C;	// 2C
		UInt32	unk30;	// 30
	};

	Data	data;	// 58
};

// 70
class BGSHazard : public TESBoundObject
{
public:
	// parents
	TESFullName		fullName;		// 20
	TESModel		model;			// 28
	BGSPreloadable	preloadable;	// 3C
	TESImageSpaceModifiableForm	imageSpaceModifier;	// 40

	// members

	// 28
	struct Data
	{
		UInt32	unk00;	// 00
		UInt32	unk04;	// 04
		UInt32	unk08;	// 08
		UInt32	unk0C;	// 0C
		UInt32	unk10;	// 10
		UInt32	unk14;	// 14
		UInt32	unk18;	// 18
		UInt32	unk1C;	// 1C
		UInt32	unk20;	// 20
		UInt32	unk24;	// 24
	};

	Data	unk48;	// 48
};

// 44
class BGSIdleMarker : public TESBoundObject
{
public:
	// parents
	TESModel			model;	// 20
	BGSIdleCollection	idle;	// 34
};

// 64
class BGSNote : public TESBoundObject
{
public:
	// parents
	TESModel		model;		// 20
	TESFullName		fullName;	// 34
	TESIcon			icon;		// 3C
	BGSPickupPutdownSounds	sounds;	// 44

	// members
	struct Entry
	{
		void	* data;
		Entry	* next;
	};

	UInt32	unk50;		// 50
	UInt32	unk54;		// 54
	Entry	unk58;		// 58
	UInt8	unk60;		// 60
	UInt8	unk61;		// 61
	UInt8	pad62[2];	// 62
};

// BC
class BGSProjectile : public TESBoundObject
{
public:
	// parents
	TESFullName		fullName;		// 20
	TESModel		model;			// 28
	BGSPreloadable	preloadable;	// 3C
	BGSDestructibleObjectForm	destructible;	// 40

	// members

	// 5C
	struct Data
	{
		UInt32	unk00;				// 00
		UInt32	unk04;				// 04
		float	unk08;				// 08
		float	unk0C;				// 0C
		UInt32	unk10;				// 10
		UInt32	unk14;				// 14
		UInt32	unk18;				// 18
		UInt32	unk1C;				// 1C
		UInt32	unk20;				// 20
		UInt32	unk24;				// 24
		UInt32	unk28;				// 28
		UInt32	unk2C;				// 2C
		float	unk30;				// 30
		UInt32	unk34;				// 34
		UInt32	unk38;				// 38
		UInt32	unk3C;				// 3C
		UInt32	unk40;				// 40
		UInt32	unk44;				// 44
		float	unk48;				// 48
		UInt32	unk4C;				// 4C
		float	relaunchInterval;	// 50
		UInt32	unk54;				// 54
		UInt32	unk58;				// 58
	};

	Data		data;		// 48
	TESModel	modelA4;	// A4
	UInt32		unkB8;		// B8
};

// 3C
class BGSStaticCollection : public TESBoundObject
{
public:
	// parents
	TESModelTextureSwap	texSwap;	// 20
};

// 08
class BSTextureSet : public NiObject
{
public:
	virtual void	Unk_21(void);
	virtual void	Unk_22(void);
	virtual void	Unk_23(void);
};

// D0
class BGSTextureSet : public TESBoundObject
{
public:
	// parents
	BSTextureSet	textureSet;	// 20

	// members

	// 0C
	struct Data
	{
		UInt32	unk00;	// 00
		UInt32	unk04;	// 04
		UInt32	unk08;	// 08
	};

	TESTexture		unk28[8];	// 28
	UInt32			unk68;		// 68
	UInt32			unk6C;		// 6C
	Data			unk70[8];	// 70	
};

STATIC_ASSERT(sizeof(BGSTextureSet) == 0xD0);

// 50
class MagicItem : public TESBoundObject
{
public:
	virtual UInt32	Unk_52(void);	// pure
	virtual void	Unk_53(UInt32 arg);
	virtual UInt32	Unk_54(void);	// pure
	virtual void	Unk_55(UInt32 arg);
	virtual UInt32	Unk_56(void);	// pure
	virtual bool	Unk_57(UInt32 arg);
	virtual float	Unk_58(void);
	virtual float	Unk_59(void);
	virtual bool	Unk_5A(void);
	virtual bool	Unk_5B(void);
	virtual bool	Unk_5C(void);
	virtual bool	Unk_5D(void);
	virtual bool	Unk_5E(void);
	virtual bool	Unk_5F(UInt32 arg);
	virtual bool	Unk_60(void);
	virtual bool	Unk_61(void);
	virtual void	Unk_62(UInt32 arg0, UInt32 arg1);
	virtual float	Unk_63(void);
	virtual UInt32	Unk_64(void);
	virtual UInt32	Unk_65(void);
	virtual bool	Unk_66(void);
	virtual UInt32	Unk_67(void);	// pure, returns char code
	virtual void	Unk_68(MagicItem * src);	// pure, copy data if possible?
	virtual void	Unk_69(UInt32 arg0, UInt32 arg1);	// loading-related
	virtual void	Unk_6A(UInt32 arg);
	virtual void *	Unk_6B(void);	// pure, returns data
	virtual void *	Unk_6C(void);	// pure, returns data
	virtual UInt32	Unk_6D(void);	// pure, return size of data
	virtual void	Unk_6E(void);	// pure, byteswap?

	// parents
	TESFullName		fullName;	// 20
	BGSKeywordForm	keyword;	// 28

	// members
	TESActorBaseData::Data2C	unk34;	// 34
	UInt32	unk40;	// 40
	UInt32	unk44;	// 44
	UInt32	unk48;	// 48
	UInt32	unk4C;	// 4C
};

STATIC_ASSERT(sizeof(MagicItem) == 0x50);

// C0
class AlchemyItem : public MagicItem
{
public:
	// parents
	TESModelTextureSwap	texSwap;		// 50
	TESIcon				icon;			// 6C
	BGSMessageIcon		messageIcon;	// 74
	TESWeightForm		weight;			// 80
	BGSEquipType		equipType;		// 88
	BGSDestructibleObjectForm	destructibleObj;	// 90
	BGSPickupPutdownSounds		sounds;	// 98

	// members

	// 14
	struct Data
	{
		struct Data0
		{
			UInt32	unk00;	// 00
			UInt32	unk04;	// 04
		};

		Data0	unk00;	// 00
		UInt32	unk08;	// 08
		UInt32	unk0C;	// 0C
		UInt32	unk10;	// 10
	};

	Data	unkA4;	// A4
	TESIcon	unkB8;	// B8
};

// 74
class EnchantmentItem : public MagicItem
{
public:
	// 24
	struct Data
	{
		struct Data0
		{
			UInt32	unk00;	// 00
			UInt32	unk04;	// 04
		};

		Data0	unk00;	// 00
		UInt32	unk08;	// 08
		UInt32	unk0C;	// 0C
		UInt32	unk10;	// 10
		UInt32	unk14;	// 14
		UInt32	unk18;	// 18
		UInt32	unk1C;	// 1C
		UInt32	unk20;	// 20
	};

	Data	data;	// 50
};

// AC
class IngredientItem : public MagicItem
{
public:
	// parents
	TESModelTextureSwap	texSwap;	// 50
	TESIcon			icon;		// 6C
	TESWeightForm	weight;		// 74
	BGSEquipType	equipType;	// 7C
	BGSDestructibleObjectForm	destructible;	// 84
	BGSPickupPutdownSounds		sounds;			// 8C
	TESValueForm	value;		// 98

	// members
	struct DataA0
	{
		UInt32	unk00;	// 00
		UInt32	unk04;	// 04
	};

	struct DataA8
	{
		UInt16	unk00;	// 00
		UInt16	unk02;	// 02
	};

	DataA0	unkA0;
	DataA8	unkA8;
};

// 90
class SpellItem : public MagicItem
{
public:
	// parents
	BGSEquipType			equipType;		// 50
	BGSMenuDisplayObject	dispObj;		// 58
	TESDescription			description;	// 60

	// members

	// 24
	struct Data
	{
		struct Data0
		{
			UInt32	unk00;	// 00
			UInt32	unk04;	// 04
		};

		Data0	unk00;	// 00
		UInt32	unk08;	// 08
		UInt32	unk0C;	// 0C
		UInt32	unk10;	// 10
		UInt32	unk14;	// 14
		UInt32	unk18;	// 18
		UInt32	unk1C;	// 1C
		UInt32	unk20;	// 20
	};

	Data	data;	// 6C
};

// D0
class ScrollItem : public SpellItem
{
public:
	// parents
	TESModelTextureSwap			texSwap;		// 90
	BGSDestructibleObjectForm	destructible;	// AC
	BGSPickupPutdownSounds		sounds;			// B4
	TESWeightForm				weight;			// C0
	TESValueForm				value;			// C8
};

// 9C
class TESAmmo : public TESBoundObject
{
public:
	// parents
	TESFullName			fullName;		// 20
	TESModelTextureSwap	texSwap;		// 28
	TESIcon				icon;			// 44
	BGSMessageIcon		messageIcon;	// 4C
	TESValueForm		value;			// 58
	BGSDestructibleObjectForm	destructible;	// 50
	BGSPickupPutdownSounds		sounds;			// 68
	TESDescription		description;	// 74
	BGSKeywordForm		keyword;		// 80

	// members

	// 0C
	struct Data8C
	{
		UInt8	unk00[0x0C];	// 00
	};

	Data8C				unk8C;	// 8C
	StringCache::Ref	unk98;	// 98
};

// 20
class TESBoundAnimObject : public TESBoundObject
{
public:
};

// C0
class TESActorBase : public TESBoundAnimObject
{
public:
	// parents
	TESActorBaseData	actorData;	// 20
	TESContainer		container;	// 58
	TESSpellList		spellList;	// 64
	TESAIForm			aiForm;		// 6C
	TESFullName			fullName;	// 84
	ActorValueOwner				actorValueOwner;	// 8C
	BGSDestructibleObjectForm	destructible;		// 90
	BGSSkinForm			skinForm;	// 98
	BGSKeywordForm		keyword;	// A0
	BGSAttackDataForm	attackData;	// AC
	BGSPerkRankArray	perkRanks;	// B4

	virtual bool			Unk_52(void);
	virtual UInt32			Unk_53(void);
	virtual void			Unk_54(UInt32 arg);
	virtual TESActorBase *	Unk_55(void);
};

STATIC_ASSERT(sizeof(TESActorBase) == 0xC0);

// 164
class TESNPC : public TESActorBase
{
public:
	// parents
	TESRaceForm		race;	// 0C0
	BGSOverridePackCollection	overridePacks;	// 0C8
	BSTEventSink <void *>	menuOpenCloseEvent;	// 0DC - MenuOpenCloseEvent

	// members @0E0
	UInt8		unk0E0[0x12];	// 0E0 - init'd to 5
	UInt8		unk0F2[0x12];	// 0F2 - init'd to 0

	UInt8		pad104[0x10A - 0x104];	// 104

	UInt16		unk10A;			// 10A
	UInt32		unk10C;			// 10C
	void		* unk110;		// 110
	UInt32		unk114;			// 114
	UInt32		unk118;			// 118
	UInt32		unk11C;			// 11C
	UInt32		unk120;			// 120
	UInt32		unk124;			// 124
	float		unk128;			// 128
	float		unk12C;			// 12C

	UInt32		pad130;			// 130
	
	StringCache::Ref	unk134;	// 134
	UInt32		unk138;			// 138
	UInt32		unk13C;			// 13C
	UInt32		unk140;			// 140
	UInt32		unk144;			// 144
	UInt32		unk148;			// 148
	UInt32		unk14C;			// 14C
	UInt8		unk150;			// 150
	UInt8		unk151;			// 151
	UInt8		unk152;			// 152
	UInt8		unk153;			// 153
	UInt8		unk154;			// 154
	UInt8		unk155;			// 155
	UInt8		unk156;			// 156
	UInt8		pad157;			// 157
	UInt32		unk158;			// 158
	void		* unk15C;		// 15C
	UInt32		unk160;			// 160
};

STATIC_ASSERT(sizeof(TESNPC) == 0x164);

// 50
class TESLevCharacter : public TESBoundAnimObject
{
public:
	TESLeveledList		leveledList;	// 20
	TESModelTextureSwap	texSwap;		// 34
};

// 6C
class TESObjectACTI : public TESBoundAnimObject
{
public:
	// parents
	TESFullName					fullName;		// 20
	TESModelTextureSwap			texSwap;		// 28
	BGSDestructibleObjectForm	destructible;	// 44
	BGSOpenCloseForm			openClose;		// 4C
	BGSKeywordForm				keyword;		// 50

	// members
	UInt32	unk5C;		// 5C
	UInt32	unk60;		// 60
	UInt32	unk64;		// 64
	UInt16	unk68;		// 68
	UInt8	pad6A[2];	// 6A
};
