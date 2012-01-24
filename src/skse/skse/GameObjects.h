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
										// model-related?
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

// 74
class BGSTalkingActivator : public TESObjectACTI
{
public:
	void			* unk6C;	// 6C
	BGSVoiceType	* unk70;	// 70
};

// 7C
class TESFlora : public TESObjectACTI
{
public:
	// parents
	TESProduceForm	produce;	// 6C
};

// 84
class TESFurniture : public TESObjectACTI
{
public:
	// 4
	struct Data78
	{
		UInt8	unk0;		// 0
		UInt8	unk1;		// 1
		UInt8	pad2[2];	// 2
	};

	TESActorBaseData::Data2C	unk6C;
	Data78	unk78;	// 78
	UInt32	unk7C;	// 7C
	UInt32	unk80;	// 80
};

// 74
class TESObjectCONT : public TESBoundAnimObject
{
public:
	// parents
	TESContainer				container;		// 20
	TESFullName					fullName;		// 2C
	TESModelTextureSwap			texSwap;		// 34
	TESWeightForm				weight;			// 50
	BGSDestructibleObjectForm	destructible;	// 58
	BGSOpenCloseForm			openClose;		// 60

	// members
	UInt32	unk64;		// 64
	UInt32	unk68;		// 68
	UInt32	unk6C;		// 6C
	UInt8	unk70;		// 70
	UInt8	pad71[3];	// 71
};

// 70
class TESObjectDOOR : public TESBoundAnimObject
{
public:
	// parents
	TESFullName					fullName;		// 20
	TESModelTextureSwap			texSwap;		// 28
	BGSDestructibleObjectForm	destructible;	// 44
	BGSOpenCloseForm			openClose;		// 4C

	// members
	UInt32	unk50;		// 50
	UInt32	unk54;		// 54
	UInt32	unk58;		// 58
	UInt32	unk5C;		// 5C
	UInt8	unk60;		// 60
	UInt8	pad61[3];	// 61
	TESActorBaseData::Data2C	unk64;	// 64
};

// B4
class TESObjectLIGH : public TESBoundAnimObject
{
public:
	// parents
	TESFullName					fullName;		// 20
	TESModelTextureSwap			texSwap;		// 28
	TESIcon						icon;			// 44
	BGSMessageIcon				messageIcon;	// 4C
	TESWeightForm				weight;			// 58
	TESValueForm				value;			// 60
	BGSDestructibleObjectForm	destructible;	// 68
	BGSEquipType				equipType;		// 70

	// members (78)

	// 28
	struct Data78
	{
		UInt32	unk00;	// 00
		UInt32	unk04;	// 04
		UInt32	unk08;	// 08
		UInt32	unk0C;	// 0C
		UInt32	unk10;	// 10
		float	unk14;	// 14 - 90
		float	unk18;	// 18 - .001
		UInt32	unk1C;	// 1C
		UInt32	unk20;	// 20
		UInt32	unk24;	// 24
	};

	struct DataA8
	{
		UInt32	unk0;	// 0
		UInt32	unk4;	// 4
		UInt32	unk8;	// 8
	};

	Data78	unk78;	// 78
	float	unkA0;	// A0 - 1
	UInt32	unkA4;	// A4
	DataA8	unkA8;	// A8
};

STATIC_ASSERT(sizeof(TESObjectLIGH) == 0xB4);

// 2C
class TESSound : public TESBoundAnimObject
{
public:
	BSString	unk20;	// 20
	UInt32		unk28;	// 28
};

// 54
class TESGrass : public TESBoundObject
{
public:
	virtual UInt8	GetUnk34(void);				// return unk34;
	virtual bool	SetUnk34(UInt8 data);		// if(data > 100) return false;
												// unk34 = data; return true;
	virtual UInt8	GetUnk35(void);				// return unk35;
	virtual bool	SetUnk35(UInt8 data);		// if(data > 90) return false;
												// if(data > unk36) return false;
												// unk35 = data; return true;
	virtual UInt8	GetUnk36(void);				// return unk36;
	virtual bool	SetUnk36(UInt8 data);		// if(data > 90) return false;
												// if(data < unk35) return false;
												// unk36 = data; return true;
	virtual float	GetUnk35_Float(void);		// return unk35 * (M_PI / 180);
	virtual float	GetUnk36_Float(void);		// return unk36 * (M_PI / 180);
	virtual UInt16	GetUnk38(void);				// return unk38;
	virtual void	SetUnk38(UInt16 data);		// unk38 = data;
	virtual UInt32	GetUnk3C(void);				// return unk3C;
	virtual void	SetUnk3C(UInt32 data);		// unk3C = data;
	virtual float	GetUnk40(void);				// return unk40;
	virtual bool	SetUnk40(float data);		// if((data < 0) || (data > 512)) return false;
												// unk40 = data; return true;
	virtual float	GetUnk44(void);				// return unk44;
	virtual bool	SetUnk44(float data);		// if((data < 0) || (data > 1)) return false;
												// unk44 = data; return true;
	virtual float	GetUnk48(void);				// return unk48;
	virtual bool	GetUnk48(float data);		// if((data < 0) || (data > 1)) return false;
												// unk48 = data; return true;
	virtual float	GetUnk4C(void);				// return unk4C;
	virtual bool	SetUnk4C(float data);		// if(data <= 0) return false;
												// unk4C = data; return true;
	virtual bool	GetUnk50_01(void);			// return (unk50 & 1) != 0;
	virtual void	SetUnk50_01(UInt8 data);	// if(data) unk50 |= 1; else unk50 &= ~1;
	virtual bool	GetUnk50_02(void);			// return (unk50 & 2) != 0;
	virtual void	SetUnk50_02(UInt8 data);	// if(data) unk50 |= 2; else unk50 &= ~2;
	virtual bool	GetUnk50_04(void);			// return (unk50 & 4) != 0;
	virtual void	SetUnk50_04(UInt8 data);	// if(data) unk50 |= 4; else unk50 &= ~4;

	// parents
	TESModel	model;		// 20

	// members
	UInt8		unk34;		// 34
	UInt8		unk35;		// 35 - degrees
	UInt8		unk36;		// 36 - degrees
	UInt8		pad37;		// 37
	UInt16		unk38;		// 38
	UInt8		pad3A[2];	// 3A
	UInt32		unk3C;		// 3C
	float		unk40;		// 40
	float		unk44;		// 44
	float		unk48;		// 48
	float		unk4C;		// 4C
	UInt8		unk50;		// 50
	UInt8		pad51[3];	// 51
};

// 34
class TESLevItem : public TESBoundObject
{
public:
	// parents
	TESLeveledList	leveledList;	// 20
};

// 34
class TESLevSpell : public TESBoundObject
{
public:
	// parents
	TESLeveledList	leveledList;	// 20
};

// 12C
class TESObjectARMO : public TESBoundObject
{
public:
	// parents
	TESFullName					fullName;		// 020
	TESRaceForm					race;			// 028
	TESEnchantableForm			enchantable;	// 030
	TESValueForm				value;			// 040
	TESWeightForm				weight;			// 048
	BGSDestructibleObjectForm	destructible;	// 050
	BGSPickupPutdownSounds		pickupSounds;	// 058
	TESBipedModelForm			bipedModel;		// 064
	BGSEquipType				equipType;		// 0DC
	BGSBipedObjectForm			bipedObject;	// 0E4
	BGSBlockBashData			blockBash;		// 0F4
	BGSKeywordForm				keyword;		// 100
	TESDescription				description;	// 10C

	// members
	UInt32	unk118;	// 118
	TESActorBaseData::Data2C	unk11C;	// 11C
	UInt32	unk128;	// 128
};

// AC
class TESObjectBOOK : public TESBoundObject
{
public:
	// parents
	TESFullName					fullName;		// 20
	TESModelTextureSwap			texSwap;		// 28
	TESIcon						icon;			// 44
	TESValueForm				value;			// 4C
	TESWeightForm				weight;			// 54
	TESDescription				description;	// 5C
	BGSDestructibleObjectForm	destructible;	// 68
	BGSMessageIcon				messageIcon;	// 70
	BGSPickupPutdownSounds		pickupSounds;	// 7C
	BGSKeywordForm				keyword;		// 88

	// members
	struct Data94
	{
		UInt32	unk0;	// 0
		UInt32	unk4;	// 4
	};

	Data94	unk94;	// 94
	UInt32	unk9C;	// 9C
};

// 88
class TESObjectMISC : public TESBoundObject
{
public:
	// parents
	TESFullName					fullName;		// 20
	TESModelTextureSwap			texSwap;		// 28
	TESIcon						icon;			// 44
	TESValueForm				value;			// 4C
	TESWeightForm				weight;			// 54
	BGSDestructibleObjectForm	destructible;	// 5C
	BGSMessageIcon				messageIcon;	// 64
	BGSPickupPutdownSounds		pickupSounds;	// 70
	BGSKeywordForm				keyword;		// 7C

	virtual void	Unk_52(void);
	virtual void	Unk_53(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_54(void);
};

// 9C
class BGSApparatus : public TESObjectMISC
{
public:
	// parents
	TESQualityForm	quality;		// 88
	TESDescription	description;	// 90
};

// 88
class TESKey : public TESObjectMISC
{
public:
};

// 90
class TESSoulGem : public TESObjectMISC
{
public:
	UInt32	unk88;		// 88
	UInt8	unk8C;		// 8C
	UInt8	unk8D;		// 8D
	UInt8	pad8E[2];	// 8E
};

// 44
class TESObjectSTAT : public TESBoundObject
{
public:
	// parents
	TESModelTextureSwap		texSwap;	// 20
	
	// members
	// 8
	struct Data3C
	{
		float	unk0;
		UInt32	unk4;
	};

	Data3C	unk3C;	// 3C
};

// 5C
// they probably wanted this to derive from TESObjectSTAT first
// doesn't really hurt anything except performance (shims)
class BGSMovableStatic : public TESFullName
{
public:
	// parents
	BGSDestructibleObjectForm	destructible;	// 08
	TESObjectSTAT				staticObj;		// 10

	// members
	UInt8	unk58;		// 58
	UInt8	pad59[3];	// 59
};

// 84
class TESObjectTREE : public TESBoundObject
{
public:
	// parents
	TESModel		model;		// 20
	TESFullName		fullName;	// 34
	TESProduceForm	produce;	// 3C
	
	// members
	// 38
	struct Data4C
	{
		float	unk00;	// 00 - init'd to 1
		float	unk04;	// 04 - init'd to 1
		float	unk08;	// 08 - init'd to .03
		float	unk0C;	// 0C - init'd to .6
		float	unk10;	// 10 - init'd to .2
		float	unk14;	// 14 - init'd to .4
		float	unk18;	// 18 - init'd to .075
		float	unk1C;	// 1C - init'd to .025
		float	unk20;	// 20 - init'd to .035
		float	unk24;	// 24 - init'd to 1
		float	unk28;	// 28 - init'd to 1
		float	unk2C;	// 2C - init'd to 1
		UInt32	unk30;	// 30
		UInt32	unk34;	// 34 - init'd to 2
	};

	Data4C	unk4C;	// 4C
};

// 138
class TESObjectWEAP : public TESBoundObject
{
public:
	// parents
	TESFullName					fullName;		// 020
	TESModelTextureSwap			texSwap;		// 028
	TESIcon						icon;			// 044
	TESEnchantableForm			enchantable;	// 04C
	TESValueForm				value;			// 05C
	TESWeightForm				weight;			// 064
	TESAttackDamageForm			damage;			// 06C
	BGSDestructibleObjectForm	destructible;	// 074
	BGSEquipType				equipType;		// 07C
	BGSPreloadable				preloadable;	// 084
	BGSMessageIcon				messageIcon;	// 088
	BGSPickupPutdownSounds		pickupSounds;	// 094
	BGSBlockBashData			blockBash;		// 0A0
	BGSKeywordForm				keyword;		// 0AC
	TESDescription				description;	// 0B8

	// members

	// 34
	struct DataC4
	{
		enum	// type
		{
			kType_HandToHandMelee = 0,
			kType_OneHandSword,
			kType_OneHandDagger,
			kType_OneHandAxe,
			kType_OneHandMace,
			kType_TwoHandSword,
			kType_TwoHandAxe,
			kType_Bow,
			kType_Staff,
			kType_H2H,
			kType_1HS,
			kType_1HD,
			kType_1HA,
			kType_1HM,
			kType_2HS,
			kType_2HA,
			kType_Bow2,
			kType_Staff2
		};

		UInt32	unk00;	// 00
		float	unk04;	// 04
		float	reach;	// 08
		float	unk0C;	// 0C
		float	unk10;	// 10
		float	unk14;	// 14
		float	unk18;	// 18
		float	unk1C;	// 1C
		UInt32	unk20;	// 20
		UInt32	unk24;	// 24
		UInt32	unk28;	// 28
		UInt16	unk2C;	// 2C
		UInt8	unk2E;	// 2E
		UInt8	unk2F;	// 2F
		UInt8	unk30;	// 30
		UInt8	type;	// 31
		UInt8	unk32;	// 32
		UInt8	unk33;	// 33
	};

	// 0C
	struct DataF8
	{
		float	unk00;			// 00
		TESForm	* spellItem;	// 04
		UInt16	unk08;			// 08
		UInt8	unk0A;			// 0A
		UInt8	pad0B;			// 0B
	};

	DataC4	unk0C4;	// 0C4
	DataF8	unk0F8;	// 0F8
	TESForm	* scopeEffect;		// 104
	TESForm	* attackSound;		// 108
	TESForm	* attackSound2D;	// 10C
	TESForm	* attackLoopSound;	// 110
	TESForm	* attackFailSound;	// 114
	TESForm	* idleSound;		// 118
	TESForm	* equipSound;		// 11C
	TESForm	* unequipSound;		// 120
	TESForm	* impactDataSet;	// 124
	TESForm	* firstPersonModel;	// 128
	TESForm	* templateForm;		// 12C
	UInt32	unk130;				// 130
	UInt32	pad134;				// 134
};

STATIC_ASSERT(sizeof(TESObjectWEAP) == 0x138);

// CC
class TESObjectARMA : public TESObject
{
public:
	// parents
	TESRaceForm			race;	// 14
	BGSBipedObjectForm	biped;	// 1C

	// members

	// 0C
	struct Data2C
	{
		UInt8	unk00;	// 00
		UInt8	unk01;	// 01
		UInt8	unk02;	// 02
		UInt8	unk03;	// 03
		UInt8	unk04;	// 04
		UInt8	unk05;	// 05
		UInt8	unk06;	// 06
		UInt8	pad07;	// 07
		UInt32	unk08;	// 08
	};

	Data2C						unk2C;		// 2C
	TESModelTextureSwap			unk38[2];	// 38
	TESModelTextureSwap			unk70[2];	// 70
	UInt32						unkA8;		// A8
	UInt32						unkAC;		// AC
	UInt32						unkB0;		// B0
	UInt32						unkB4;		// B4
	TESActorBaseData::Data2C	unkB8;		// B8
	UInt32						unkC4;		// C4
	UInt32						unkC8;		// C8
};

STATIC_ASSERT(sizeof(TESObjectARMA) == 0xCC);
