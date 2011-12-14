#pragma once

#include "skse/GameTypes.h"
#include "skse/GameFormComponents.h"
#include "skse/GamePathing.h"

class TESForm;

typedef TESForm * (* _LookupFormByID)(UInt32 id);
extern const _LookupFormByID LookupFormByID;

// everything deriving from TESForm goes here
// TESObject and derivatives are in GameObjects.h

/**** form types ***************************************************************
 *	
 *	id	name
 *	
 *	00	
 *	01	
 *	02	
 *	03	
 *	04	BGSKeyword
 *	05	BGSLocationRefType
 *	06	BGSAction
 *	07	
 *	08	BGSMenuIcon
 *	09	
 *	0A	TESClass
 *	0B	TESFaction
 *	0C	BGSHeadPart
 *	0D	
 *	0E	TESEyes
 *	0F	
 *	10	
 *	11	
 *	12	
 *	13	EffectSetting
 *	14	Script
 *	15	
 *	16	
 *	17	
 *	18	
 *	19	
 *	1A	
 *	1B	
 *	1C	
 *	1D	
 *	1E	
 *	1F	
 *	20	
 *	21	
 *	22	
 *	23	
 *	24	
 *	25	
 *	26	
 *	27	
 *	28	
 *	29	
 *	2A	
 *	2B	
 *	2C	
 *	2D	
 *	2E	
 *	2F	
 *	30	
 *	31	BGSDefaultObjectManager
 *	32	
 *	33	BGSConstructibleObject
 *	34	
 *	35	
 *	36	
 *	37	
 *	38	
 *	39	TESClimate
 *	3A	
 *	3B	BGSReferenceEffect
 *	3C	BGSCollisionLayer
 *	3D	NavMeshInfoMap
 *	3E	
 *	3F	
 *	40	
 *	41	
 *	42	
 *	43	
 *	44	
 *	45	
 *	46	
 *	47	
 *	48	
 *	49	
 *	4A	
 *	4B	NavMesh
 *	4C	
 *	4D	
 *	4E	
 *	4F	TESQuest
 *	50	
 *	51	
 *	52	TESCombatStyle
 *	53	
 *	54	
 *	55	
 *	56	
 *	57	TESEffectShader
 *	58	
 *	59
 *	5A	BGSDebris
 *	5B	
 *	5C	
 *	5D	BGSListForm
 *	5E	BGSPerk
 *	5F	BGSBodyPartData
 *	60	
 *	61	ActorValueInfo
 *	62	BGSCameraShot
 *	63	BGSCameraPath
 *	64	BGSVoiceType
 *	65	BGSMaterialType
 *	66	BGSImpactData
 *	67	BGSImpactDataSet
 *	68	
 *	69	BGSEncounterZone
 *	6A	BGSLocation
 *	6B	BGSMessage
 *	6C	BGSRagdoll
 *	6D	
 *	6E	BGSLightingTemplate
 *	6F	BGSMusicType
 *	70	BGSFootstep
 *	71	BGSFootstepSet
 *	72	BGSStoryManagerBranchNode
 *	73	BGSStoryManagerQuestNode
 *	74	BGSStoryManagerEventNode
 *	75	BGSDialogueBranch
 *	76	BGSMusicTrackFormWrapper
 *	77	
 *	78	
 *	79	
 *	7A	BGSEquipSlot
 *	7B	BGSRelationship
 *	7C	BGSScene
 *	7D	BGSAssociationType
 *	7E	BGSOutfit
 *	7F	
 *	80	BGSMaterialObject
 *	81	BGSMovementType
 *	82	BGSSoundDescriptorForm
 *	83	
 *	84	BGSSoundCategory
 *	85	BGSSoundOutput
 *	86	
 *	87	BGSColorForm
 *	88	BGSReverbParameters
 *	
 */

// 14
class TESForm : public BaseFormComponent
{
public:
	virtual void			Unk_04(void);		// reset/init? would leak pointers if called on a live object
	virtual void			Unk_05(void);		// release pointers?
	virtual bool			LoadForm(UInt32 arg);
	virtual bool			Unk_07(UInt32 arg);
	virtual bool			Unk_08(UInt32 arg);	// calls LoadForm
	virtual TESForm *		Unk_09(UInt32 arg1, void * arg2);
	virtual bool			Unk_0A(UInt32 changed);	// mark as changed?
	virtual void			Unk_0B(UInt32 arg);
	virtual bool			Unk_0C(UInt32 arg);
	virtual void			Unk_0D(UInt32 arg);
	virtual void			Unk_0E(UInt32 arg);
	virtual void			Unk_0F(void * arg);
	virtual void			Unk_10(UInt32 arg);
	virtual void			Unk_11(UInt32 arg);
	virtual void			Unk_12(UInt32 arg);
	virtual void			PostLoadInit(void);	// called once all dependent forms are loaded
												// might be called InitItem
	virtual void			Unk_14(void);
	virtual UInt32			GetFormType(void);
	virtual void			GetFormDesc(char * buf, UInt32 bufLen);
	virtual bool			GetFlag00000040(void);
	virtual bool			GetFlag00010000(void);
	virtual bool			GetFlag00020000(void);
	virtual bool			GetFlag00080000(void);
	virtual bool			GetFlag02000000(void);
	virtual bool			Unk_1B(void);
	virtual bool			GetFlag00000200(void);
	virtual bool			GetFlag00000100(void);
	virtual void			SetFlag00000200(bool set);
	virtual bool			Unk_20(void);
	virtual void			SetFlag00000020(bool set);
	virtual void			SetFlag00000002(bool set);
	virtual void			Unk_23(void);
	virtual void			Unk_24(UInt32 arg);
	virtual bool			Unk_25(void);
	virtual bool			Unk_26(void);
	virtual bool			Unk_27(void);
	virtual bool			Unk_28(void);
	virtual UInt32			Unk_29(void);
	virtual UInt32			Unk_2A(void);
	virtual UInt32			Unk_2B(void);
	virtual const char *	GetFullName(void);
	virtual void			CopyFrom(TESForm * srcForm);
	virtual bool			Compare(TESForm * rhs);
	virtual void			Unk_2F(void * dst, UInt32 unk);
	virtual const char *	GetName(void);
	virtual bool			SetName(const char * str);
	virtual bool			Unk_32(void);
	virtual bool			Unk_33(void);
	virtual bool			Unk_34(UInt32 arg);
	virtual bool			Unk_35(UInt32 arg0, UInt32 arg1, UInt32 arg2, UInt32 arg3, UInt32 arg4);
	virtual void			SetFormID(UInt32 id, UInt32 generateID);
	virtual const char *	Unk_37(void);
	virtual bool			Unk_38(void);

	void	* unk04;	// 04
	UInt32	flags;		// 08
	UInt32	formID;		// 0C
	UInt16	unk10;		// 10
	UInt8	formType;	// 12
	UInt8	pad13;		// 13
};

// C8
class ActorValueInfo : public TESForm
{
public:
	// parents
	TESFullName			fullName;		// 14
	TESDescription		description;	// 1C
	TESIcon				icon;			// 28

	// members
	const char *		name;			// 30 - second ctor argument
	StringCache::Ref	unk34;			// 34
	UInt32				unk38;			// 38
	UInt32				unk3C;			// 3C
	UInt32				unk40;			// 40
	UInt32				unk44;			// 44
	UInt32				unk48[0x0F];	// 48 - init'd to 0xA4
	UInt32				unk84;			// 84
	UInt32				unk88[0x0A];	// 88 - init'd to 0
	void				* unkB0;		// B0
	UInt32				unkB4;			// B4
	UInt32				unkB8;			// B8
	UInt32				unkBC;			// BC

	UInt8	padC0[8];	// C0 - ? not initialized
};

// 28
class BGSAssociationType : public TESForm
{
public:
	StringCache::Ref	unk14[4];	// 14
	UInt32				unk28;		// 28
};

// 44
class BGSBodyPartData : public TESForm
{
public:
	// parents
	TESModel		model;			// 14
	BGSPreloadable	preloadable;	// 28

	// members
	struct Data
	{
		StringCache::Ref	unk00;		// 00
		StringCache::Ref	unk04;		// 04
		StringCache::Ref	unk08;		// 08
		StringCache::Ref	unk0C;		// 0C
		StringCache::Ref	unk10;		// 10
		TESModel			model;		// 14
		TESModelRDT			modelRDT;	// 28
	};

	Data	* part[5];		// 2C - init'd to 0
	UInt32	unk40;			// 40 - init'd to 0
};

// 30
class BGSCameraPath : public TESForm
{
public:
	UInt32	unk14;		// 14
	UInt32	unk18;		// 18
	UInt32	unk1C;		// 1C
	UInt8	unk20;		// 20
	UInt8	pad21[3];	// 21
	UInt32	unk24;		// 24
	UInt32	unk28;		// 28
	UInt32	unk2C;		// 2C
};

// 74
class BGSCameraShot : public TESForm
{
public:
	// parents
	TESModel					model;			// 14
	TESImageSpaceModifiableForm	imageSpaceMod;	// 28

	// members
	UInt32	unk30;		// 30
	UInt32	unk34;		// 34
	UInt32	unk38;		// 38
	UInt32	unk40;		// 40
	UInt32	unk44;		// 44
	float	globalTimeMultiplier;	// 48
	UInt32	unk4C;		// 4C
	UInt32	unk50;		// 50
	UInt32	unk54;		// 54

	UInt32	unk58;		// 58
	UInt32	unk5C;		// 5C
	UInt32	unk60;		// 60
	UInt32	unk64;		// 64
	UInt32	unk68;		// 68
	UInt8	unk6C;		// 6C
	UInt8	pad6D[3];	// 6D
	UInt32	unk70;		// 70
};

// 3C
class BGSCollisionLayer : public TESForm
{
	// parents
	TESDescription				description;	// 14

	// members
	UInt32						unk20;	// 20
	UInt32						unk24;	// 24
	UInt32						unk28;	// 28
	StringCache::Ref			unk2C;	// 2C
	TESActorBaseData::Data2C	unk30;	// 30 - really?
};

// 24
class BGSColorForm : public TESForm
{
	// parents
	TESFullName	fullName;	// 14

	// members
	UInt32		unk1C;	// 1C
	UInt32		unk20;	// 20
};

// 30
class BGSConstructibleObject : public TESForm
{
public:
	// members
	TESContainer	container;	// 14 - not inherited
	UInt32			unk20;		// 20 - linked list
	UInt32			unk24;		// 24
	UInt32			unk28;		// 28
	UInt16			unk2C;		// 2C
	UInt8			pad2E[2];	// 2E
};

// 20
class BGSDebris : public TESForm
{
public:
	struct Data
	{
		UInt32	unk0;
		UInt32	unk4;
	};

	// parents
	BGSPreloadable	preloadable;	// 14
	
	// members
	Data	unk18;	// 18 - linked list
};

// ?? - singleton, ID 00000031
class BGSDefaultObjectManager : public TESForm
{
public:
	// cleared to 0 in ctor
	TESForm	* objects[0xD9];			// 14
	UInt8	pad[0x4BC - (0xD9 * 4)];	// just pad out the rest of the space
};

// 24
class BGSDialogueBranch : public TESForm
{
public:
	UInt32	unk14;		// 14 - init'd to 1
	TESForm	* unk18;	// 18 - init'd to 0, TESQuest
	TESForm	* unk1C;	// 1C - init'd to 0, starting topic (type 4D)
	UInt32	unk20;		// 20 - init'd to 0
};

// 30
class BGSEncounterZone : public TESForm
{
public:
	UInt8	unk14[0x0C];	// 14
	UInt8	unk20[0x10];	// 20

	// +14 - TESForm * owner?
	// +18 - TESForm * location?
};

// 24
class BGSEquipSlot : public TESForm
{
public:
	TESActorBaseData::Data2C	unk14;
	UInt32						unk20;
};

// 1C
class BGSFootstep : public TESForm
{
public:
	StringCache::Ref	unk14;	// 14
	UInt32				unk18;	// 18
};

// 50
class BGSFootstepSet : public TESForm
{
public:
	TESActorBaseData::Data2C	unk14[5];	// 14
};

// 98
class BGSHeadPart : public TESForm
{
public:
	// 0C
	struct Data
	{
		void	* unk00;	// 00
		UInt32	unk04;		// 04
	};

	// parents
	TESFullName			fullName;	// 14
	TESModelTextureSwap	model;		// 1C

	// members
	UInt8		unk38;		// 38
	UInt8		pad39[3];	// 39
	UInt32		unk3C;		// 3C
	Data		unk40;		// 40
	UInt32		unk4C;		// 4C
	TESModelTri	unk50[3];	// 50
	UInt32		unk8C;		// 8C
	UInt32		unk90;		// 90
	StringCache::Ref	unk94;	// 94
};

// 78
class BGSImpactData : public TESForm
{
public:
	// 20
	struct Data54
	{
		float	unk00;		// 00 - init'd to 8
		float	unk04;		// 04 - init'd to 32
		float	unk08;		// 08 - init'd to 8
		float	unk0C;		// 0C - init'd to 32
		float	unk10;		// 10 - init'd to 32
		float	unk14;		// 14 - init'd to 4
		float	unk18;		// 18 - init'd to 1
		UInt8	unk1C;		// 1C - init'd to 4
		UInt8	unk1D;		// 1D - init'd to 0
		UInt8	pad1E[2];	// 1E
	};

	// parents
	TESModel	model;		// 14

	// members
	float	unk28;			// 28 - init'd to .25
	UInt32	unk2C;			// 2C - init'd to 2
	float	unk30;			// 30 - init'd to 15
	float	unk34;			// 34 - init'd to 16
	UInt32	unk38;			// 38 - init'd to 1
	UInt8	pad3C[4];		// 3C - init'd to 0 via memset (block from 28-40)

	TESForm	* textures[2];	// 40 - texture set
	TESForm	* sounds[2];	// 48 - sound
	TESForm	* hazard;		// 50 - hazard

	Data54	unk54;			// 54
	
	UInt32	pad74;			// 74
};

// 1C
class BGSKeyword : public TESForm
{
public:
	BSString	keyword;	// 14
};

// 20
class BGSAction : public BGSKeyword
{
public:
	UInt32	idx;	// 1C - ctor sets to a unique value
};

// 1C
class BGSLocationRefType : public BGSKeyword
{
public:
};

// 94
class BGSLightingTemplate : public TESForm
{
public:
	// 5C
	struct Data
	{
		// 20 - used elsewhere
		struct Data28
		{
			UInt32	unk00[6];	// 00 - init'd to 00FFFFFF
			UInt32	unk18;		// 18 - init'd to 0
			float	unk1C;		// 1C - init'd to 1
		};

		UInt32	unk00;			// 00 - init'd to 0
		UInt32	unk04;			// 04 - init'd to 0
		UInt32	unk08;			// 08 - init'd to 0
		UInt32	unk0C;			// 0C - init'd to 0
		UInt32	unk10;			// 10 - init'd to 0
		UInt32	unk14;			// 14 - init'd to 0
		UInt32	unk18;			// 18 - init'd to 0
		float	unk1C;			// 1C - init'd to 1
		UInt32	unk20;			// 20 - init'd to 0
		float	unk24;			// 24 - init'd to 1
		Data28	unk28;			// 28
		UInt32	unk48;			// 48 - init'd to 0
		float	unk4C;			// 4C - init'd to 1
		float	lodStartFade;	// 50 - fLightLODStartFade
		float	lodStopFade;	// 54 - fLightLODStartFade + fLightLODRange
		UInt32	unk58;			// 58 - init'd to 0000079F
	};

	Data			unk14;	// 14
	UInt32			pad70;	// 70
	Data::Data28	unk74;	// 74
};

STATIC_ASSERT(sizeof(BGSLightingTemplate) == 0x94);

// 28
class BGSListForm : public TESForm
{
public:
	TESActorBaseData::Data2C	unk14;	// 14
	UInt32	unk20;	// 20
	UInt32	unk24;	// 24
};

// 88
class BGSLocation : public TESForm
{
public:
	// parents
	TESFullName		fullName;	// 14
	BGSKeywordForm	keyword;	// 1C

	// members
	UInt32						unk28;		// 28 - init'd to 0
	UInt32						unk2C;		// 2C - init'd to 0
	UInt32						unk30;		// 30 - init'd to 0
	UInt32						unk34;		// 34 - init'd to 0
	UInt32						unk38;		// 38 - init'd to 0
	UInt32						unk3C;		// 3C - init'd to 0
	TESActorBaseData::Data2C	unk40;		// 40
	TESActorBaseData::Data2C	unk4C;		// 4C
	UInt32						unk58;		// 58 - init'd to 0
	UInt32						unk5C;		// 5C - init'd to 0
	TESActorBaseData::Data2C	unk60;		// 60
	UInt32						unk6C;		// 6C - init'd to 0
	UInt32						unk70;		// 70 - init'd to 0
	TESActorBaseData::Data2C	unk74;		// 74
	UInt32						unk80;		// 80 - init'd to 0
	UInt8						unk84;		// 84 - init'd to 0
	UInt8						unk85;		// 85 - init'd to 0
	UInt8						pad86[2];	// 86
};

STATIC_ASSERT(sizeof(BGSLocation) == 0x88);

// 74
class BGSMaterialObject : public TESForm
{
public:
	// parents
	TESModel			model;			// 14
	BSMaterialObject	materialObject;	// 28

	// members
	TESActorBaseData::Data2C	unk68;	// 68
};

// 38
class BGSMaterialType : public TESForm
{
public:
	// C
	struct Data20
	{
		float	unk0;
		float	unk4;
		float	unk8;
	};

	TESForm				* parentType;		// 14 - init'd to 0
	StringCache::Ref	unk18;				// 18 - init'd to 0
	UInt32				unk1C;				// 1C - init'd to 0
	Data20				unk20;				// 20
	float				unk2C;				// 2C - init'd to 1
	UInt32				unk30;				// 30 - init'd to 0
	TESForm				* impactDataSet;	// 34 - init'd to 0
};

// 1C
class BGSMenuIcon : public TESForm
{
public:
	// parents
	TESIcon	icon;	// 14
};

// 40
class BGSMessage : public TESForm
{
public:
	struct Data
	{
		UInt32	unk0;
		UInt32	unk4;
	};

	// parents
	TESFullName		fullName;		// 14
	TESDescription	description;	// 1C

	// members
	TESForm	* icon;		// 28 - init'd to 0
	TESForm	* quest;	// 2C - init'd to 0
	Data	unk30;		// 30
	UInt32	unk38;		// 38 - init'd to 1
	UInt32	unk3C;		// 3C - init'd to 2
};

// 50
class BGSMovementType : public TESForm
{
public:
	// 8
	struct Data
	{
		UInt32	unk0;
		UInt32	unk4;
	};

	StringCache::Ref	unk14;	// 14
	Data	unk18[4];	// 18
	float	unk38;		// 38 - init'd to pi
	float	unk3C;		// 3C - init'd to pi
	float	unk40;		// 40 - init'd to pi
	UInt32	unk44[3];	// 44 - read from INAM chunk
};

// 20
class BGSMusicTrackFormWrapper : public TESForm
{
public:
	// parents
	BSIMusicTrack	track;	// 14

	// members
	UInt32	unk1C;			// 1C
};

// 4C
class BGSMusicType : public TESForm
{
public:
	// parents
	BSIMusicType		type;	// 14

	// members
	StringCache::Ref	unk48;	// 48
};

// 20
class BGSOutfit : public TESForm
{
public:
	TESActorBaseData::Data2C	unk14;	// 14
};

// 4C
class BGSPerk : public TESForm
{
public:
	// parents
	TESFullName		fullName;		// 14
	TESDescription	description;	// 1C
	TESIcon			icon;			// 28

	// members
	UInt8	unk30;		// 30
	UInt8	unk31;		// 31
	UInt8	unk32;		// 32
	UInt8	unk33;		// 33
	UInt8	unk34;		// 34
	UInt8	pad35[3];	// 35
	void	* unk38;	// 38
	TESActorBaseData::Data2C	unk3C;	// 3C
	UInt32	unk48;		// 48
};

// 124
class BGSRagdoll : public TESForm
{
public:
	// parents
	TESModel	model;	// 14

	// members

	// 4C
	struct Data38
	{
		// 3C
		struct Data
		{
			float	unk00;	// 00 - init'd to .9
			float	unk04;	// 04 - init'd to .8
			float	unk08;	// 08 - init'd to .4
			float	unk0C;	// 0C - init'd to .2
			float	unk10;	// 10 - init'd to .1
			float	unk14;	// 14 - init'd to .3
			float	unk18;	// 18 - init'd to 0
			float	unk1C;	// 1C - init'd to 50
			float	unk20;	// 20 - init'd to 50
			float	unk24;	// 24 - init'd to 25
			float	unk28;	// 28 - init'd to 25
			float	unk2C;	// 2C - init'd to 50
			float	unk30;	// 30 - init'd to 50
			UInt32	unk34;	// 34 - init'd to 10000
			UInt32	unk38;	// 38 - init'd to 30000
		};

		UInt8						unk00;		// 00
		UInt8						pad01[3];	// 01
		Data						unk04;		// 04
		TESActorBaseData::Data2C	unk40;		// 40
	};

	// 38
	struct Data84
	{
		// 1C
		struct Data
		{
			UInt32	unk00;	// 00
			UInt32	unk04;	// 04
			UInt32	unk08;	// 08
			UInt32	unk0C;	// 0C
			UInt32	unk10;	// 10
			UInt32	unk14;	// 14
			UInt32	unk18;	// 18
		};

		UInt8						unk00;		// 00
		UInt8						pad01[3];	// 01
		Data						unk04;		// 04
		TESActorBaseData::Data2C	unk20;		// 20
		TESActorBaseData::Data2C	unk2C;		// 2C
	};

	// 1C
	struct DataBC
	{
		UInt8						unk00;		// 00
		UInt8						pad01[3];	// 01
		TESActorBaseData::Data2C	unk04;		// 04
		TESActorBaseData::Data2C	unk10;		// 10
	};

	// 24
	struct DataF4
	{
		// 18
		struct Data
		{
			UInt16	unk00;	// 00 - init'd to FFFF
			UInt16	unk02;	// 02 - init'd to FFFF
			UInt16	unk04;	// 04 - init'd to FFFF
			UInt8	unk06;	// 06 - init'd to 0
			UInt8	pad07;	// 07
			UInt32	unk08;	// 08 - init'd to 0
			UInt32	unk0C;	// 0C - init'd to 0
			float	unk10;	// 10 - init'd to 0.1
			UInt32	unk14;	// 14 - init'd to 0
		};

		UInt8		unk00;		// 00
		UInt8		pad01[3];	// 01
		BSString	unk04;		// 04
		Data		unk0C;		// 0C
	};

	UInt8	pad28[0x10];	// 028

	Data38	unk38;			// 038
	Data84	unk84;			// 084
	DataBC	unkBC;			// 0BC
	DataBC	unkD8;			// 0D8
	DataF4	unkF4;			// 0F4
	UInt8	pad118[4];		// 118
	UInt32	unk11C;			// 11C
	UInt32	unk120;			// 120
};

STATIC_ASSERT(sizeof(BGSRagdoll) == 0x124);

// 20
class BGSReferenceEffect : public TESForm
{
public:
	// C
	struct Data
	{
		UInt32	unk0;
		UInt32	unk4;
		UInt32	unk8;
	};

	Data	unk14;
};

// 24
class BGSRelationship : public TESForm
{
public:
	UInt32	unk14;	// 14
	UInt32	unk18;	// 18
	UInt32	unk1C;	// 1C
	UInt32	unk20;	// 20
};

// 28
class BGSReverbParameters : public TESForm
{
public:
	BSIReverbType	reverbType;	// 14

	UInt16	unk18;	// 18 - init'd to 1250
	UInt16	unk1A;	// 1A - init'd to 800
	UInt8	unk1C;	// 1C - init'd to 100
	UInt8	unk1D;	// 1D - init'd to 100
	UInt8	unk1E;	// 1E - init'd to 0
	UInt8	unk1F;	// 1F - init'd to 0
	UInt8	unk20;	// 20 - init'd to 100
	UInt8	unk21;	// 21 - init'd to 0
	UInt8	unk22;	// 22 - init'd to 0
	UInt8	unk23;	// 23 - init'd to 100
	UInt32	unk24;	// 24 - ???
};

// 70
class BGSScene : public TESForm
{
public:
	TESActorBaseData::Data2C	unk14;	// 14
	TESActorBaseData::Data2C	unk20;	// 20
	TESActorBaseData::Data2C	unk2C;	// 2C
	TESActorBaseData::Data2C	unk38;	// 38
	TESActorBaseData::Data2C	unk44;	// 44
	TESForm	* quest;	// 50
	UInt32	unk54;		// 54
	void	* unk58;	// 58 - linked list
	UInt8	unk5C;		// 5C
	UInt8	unk5D;		// 5D
	UInt8	unk5E;		// 5E
	UInt8	unk5F;		// 5F
	UInt8	unk60;		// 60
	UInt8	unk61;		// 61
	UInt8	unk62;		// 62
	UInt8	unk63;		// 63
	UInt8	unk64;		// 64
	UInt8	pad65[3];	// 65
	UInt32	unk68;		// 68
	UInt32	unk6C;		// 6C
};

// 28
class BGSShaderParticleGeometryData : public TESForm
{
public:
	TESActorBaseData::Data2C	unk14;		// 14
	TESTexture					texture;	// 20
};

// 38
class BGSSoundCategory : public TESForm
{
public:
	// parents
	TESFullName			fullName;		// 14
	BSISoundCategory	soundCategory;	// 1C

	// members
	UInt32	unk20;	// 20 - init'd to 0
	UInt32	unk24;	// 24 - init'd to 0 
	UInt16	unk28;	// 28 - init'd to 0
	UInt16	unk2A;	// 2A - init'd to 0
	UInt16	unk2C;	// 2C - init'd to FFFF
	UInt16	unk2E;	// 2E - init'd to FFFF
	float	unk30;	// 30 - init'd to 1
	float	unk34;	// 34 - init'd to 1
};

// 20
class BGSSoundDescriptorForm : public TESForm
{
public:
	virtual void	Unk_39(void);	// calls something on unk18

	// parents
	BSISoundDescriptor	soundDescriptor;	// 14

	// members
	void				* unk18;	// 18
	StringCache::Ref	unk1C;		// 1C
};

// 28
class BGSSoundOutput : public TESForm
{
public:
	// parents
	BSISoundOutputModel	soundOutputModel;	// 14

	// members
	UInt32	unk18;		// 18
	UInt32	unk1C;		// 1C
	UInt32	unk20;		// 20
	void	* unk24;	// 24
};

// 18
class BGSStoryManagerTreeForm : public TESForm
{
public:
	virtual UInt32	Unk_39(void);
	virtual UInt32	Unk_3A(UInt32 arg);
	virtual void *	Unk_3B(void);	// pure
	virtual void	Unk_3C(void);	// pure

	UInt32	unk14;	// 14
};

class BGSStoryManagerBranchNode;

// 2C
class BGSStoryManagerNodeBase : public BGSStoryManagerTreeForm
{
public:
	BGSStoryManagerBranchNode	* unk18;	// 18
	BGSStoryManagerNodeBase		* unk1C;	// 1C
	UInt32	unk20;							// 20
	UInt32	unk24;							// 24
	void	* unk28;						// 28 - linked list
};

// 38
class BGSStoryManagerBranchNode : public BGSStoryManagerNodeBase
{
public:
	TESActorBaseData::Data2C	unk2C;	// 2C
};

// 3C
class BGSStoryManagerEventNode : public BGSStoryManagerBranchNode
{
public:
	UInt32	unk38;	// 38
};

// 88
class BGSStoryManagerQuestNode : public BGSStoryManagerNodeBase
{
public:
	// 20
	struct Data38
	{
		UInt8	data[0x20];	// ###
	};

	// 20
	struct Data58
	{
		UInt8	data[0x20];	// ###
	};

	TESActorBaseData::Data2C	unk2C;	// 2C
	Data38						unk38;	// 38
	Data58						unk58;	// 58
	UInt32						unk78;	// 78
	TESActorBaseData::Data2C	unk7C;	// 7C
};

STATIC_ASSERT(sizeof(BGSStoryManagerQuestNode) == 0x88);

// 158
class TESQuest : public BGSStoryManagerTreeForm
{
public:
	// parents
	TESFullName	fullName;	// 18

	// members

	// 20
	struct Data03C
	{
		UInt8	data[0x20];	// ### todo
	};

	// 20
	struct Data05C
	{
		UInt8	data[0x20];	// ### todo
	};

	// 8
	struct Data07C
	{
		UInt32	unk0;
		UInt16	unk4;
		UInt8	unk6;
		UInt8	unk7;
	};

	// 8
	struct Data088
	{
		UInt32	unk0;
		UInt32	unk4;
	};

	// 20
	struct Data0A0
	{
		UInt8	data[0x20];	// ### todo
	};

	TESActorBaseData::Data2C	unk020;		// 020
	UInt32						unk02C;		// 02C
	TESActorBaseData::Data2C	unk030;		// 030
	Data03C						unk03C;		// 03C
	Data05C						unk05C;		// 05C
	Data07C						unk07C;		// 07C
	UInt32						unk084;		// 084
	Data088						unk088;		// 088
	Data088						unk090;		// 090
	void						* unk098;	// 098 - linked list
	void						* unk09C;	// 09C - linked list
	Data0A0						unk0A0[2];	// 0A0
	TESActorBaseData::Data2C	unk0E0[6];	// 0E0
	TESActorBaseData::Data2C	unk128;		// 128
	void						* unk134;	// 134 - linked list
	UInt16						unk138;		// 138
	UInt8						unk13A;		// 13A
	UInt8						pad13B;		// 13B
	BSString					unk13C;		// 13C
	UInt32						unk144;		// 144
	UInt32						unk148;		// 148
	TESActorBaseData::Data2C	unk14C;		// 14C
};

STATIC_ASSERT(sizeof(TESQuest) == 0x158);

// 20
class BGSVoiceType : public TESForm
{
public:
	UInt8		unk14;		// 14
	UInt8		pad15[3];	// 15
	BSString	unk18;		// 18
};

// F4
class EffectSetting : public TESForm
{
public:
	// parents
	TESFullName				fullName;			// 14
	BGSMenuDisplayObject	menuDisplayObject;	// 1C
	BGSKeywordForm			keywordForm;		// 24

	// members
	
	// 98
	struct Data38
	{
		UInt32	unk00;		// 00 - init'd to 0
		UInt32	unk04;		// 04 - init'd to 0
		UInt32	unk08;		// 08 - init'd to 0
		UInt32	unk0C;		// 0C - init'd to FFFFFFFF
		UInt32	unk10;		// 10 - init'd to FFFFFFFF
		UInt16	unk14;		// 14 - init'd to 0
		UInt8	pad16[2];	// 16
		UInt32	unk18;		// 18 - init'd to 0
		UInt32	unk1C;		// 1C - init'd to 0
		UInt32	unk20;		// 20 - init'd to 0
		UInt32	unk24;		// 24 - init'd to 0
		UInt32	unk28;		// 28 - init'd to 0
		UInt32	unk2C;		// 2C - init'd to 0
		UInt32	unk30;		// 30 - init'd to 0
		UInt32	unk34;		// 34 - init'd to 0
		UInt32	unk38;		// 38 - init'd to 0
		UInt32	unk3C;		// 3C - init'd to 0
		UInt32	unk40;		// 40 - init'd to 0
		UInt32	unk44;		// 44 - init'd to FFFFFFFF
		UInt32	unk48;		// 48 - init'd to 0
		UInt32	unk4C;		// 4C - init'd to 0
		UInt32	unk50;		// 50 - init'd to 3
		UInt32	unk54;		// 54 - init'd to 5
		UInt32	unk58;		// 58 - init'd to FFFFFFFF
		UInt32	unk5C;		// 5C - init'd to 0
		UInt32	unk60;		// 60 - init'd to 0
		UInt32	unk64;		// 64 - init'd to 0
		UInt32	unk68;		// 68 - init'd to 0
		UInt32	unk6C;		// 6C - init'd to 0
		float	unk70;		// 70 - init'd to 1
		UInt32	unk74;		// 74 - init'd to 0
		UInt32	unk78;		// 78 - init'd to 0
		UInt32	unk7C;		// 7C - init'd to 0
		UInt32	unk80;		// 80 - init'd to 0
		UInt32	unk84;		// 84 - init'd to 0
		UInt32	unk88;		// 88 - init'd to 0
		UInt32	unk8C;		// 8C - init'd to 1
		UInt32	unk90;		// 90 - init'd to 0
		UInt32	unk94;		// 94 - init'd to 0
	};

	// 8
	struct DataD0
	{
		UInt32	unk0;
		UInt32	unk4;
	};

	UInt32						unk30;		// 30
	UInt32						unk34;		// 34
	Data38						unk38;		// 38
	DataD0						unkD0;		// D0
	TESActorBaseData::Data2C	unkD8;		// D8
	StringCache::Ref			unkE4;		// E4
	UInt32						unkE8;		// E8
	UInt32						unkEC;		// EC
	void						* unkF0;	// F0 - linked list
};

// B4
class NavMesh : public TESForm
{
public:
	// parents
	TESChildCell	childCell;	// 14
	BSNavmesh		navmesh;	// 18
};

STATIC_ASSERT(sizeof(NavMesh) == 0xB4);

// 98
class NavMeshInfoMap : public TESForm
{
public:
	// parents
	BSNavmeshInfoMap				infoMap;	// 14
	PrecomputedNavmeshInfoPathMap	pathMap;	// 1C

	// members

	// 20
	struct Data4C
	{
		UInt32	unk00;		// 00
		UInt32	unk04;		// 04
		UInt32	unk08;		// 08 - 0
		UInt32	unk0C;		// 0C - 0
		void	* unk10;	// 10 - ptr to 0xDEADBEEF
		UInt32	unk14;		// 14 - 0
		UInt32	unk18;		// 18
		UInt32	unk1C;		// 1C - 0
	};

	// 20
	struct Data6C
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

	// 8
	struct Data8C
	{
		UInt32	unk0;
		UInt32	unk4;
	};

	UInt8	unk48;		// 48
	UInt8	pad49[3];	// 49
	Data4C	unk4C;		// 4C
	Data6C	unk6C;		// 6C
	Data8C	unk8C;		// 8C
	UInt8	unk94;		// 94
	UInt8	pad95[3];	// 95
};

STATIC_ASSERT(sizeof(NavMeshInfoMap) == 0x98);

// 50
class Script : public TESForm
{
public:
	// 14
	struct Data
	{
		UInt32	unk00;	// 00
		UInt32	unk04;	// 04 - numRefs?
		UInt32	unk08;	// 08 - dataLength?
		UInt32	unk0C;	// 0C - varCount?
		UInt32	unk10;	// 10 - type?
	};

	struct RefListEntry
	{
		void			* data;
		RefListEntry	* next;
	};

	struct VarInfoEntry
	{
		void			* data;
		VarInfoEntry	* next;
	};

	Data			unk14;				// 14
	void			* unk28;			// 28
	void			* unk2C;			// 2C
	UInt32			unk30;				// 30
	float			questDelayTimer;	// 34
	float			secondsPassed;		// 38
	TESForm			* parentQuest;		// 3C
	RefListEntry	refList;			// 40
	VarInfoEntry	varList;			// 48
};

// 54
class TESClass : public TESForm
{
public:
	// parents
	TESFullName		fullName;		// 14
	TESDescription	description;	// 1C
	TESTexture		texture;		// 28

	// members

	// 24
	struct Data30
	{
		UInt8	unk00[0x18];	// 00
		float	bleedout;		// 18
		UInt32	voicePoints;	// 1C
		UInt8	unk20[0x04];	// 20
	};

	// 30
	Data30	unk30;				// 30
};

STATIC_ASSERT(sizeof(TESClass) == 0x54);

// 48
class TESClimate : public TESForm
{
public:
	struct Data28
	{
		UInt32	unk0;
		UInt32	unk4;
	};

	TESModel	model;			// 14
	Data28		unk28;			// 28
	TESTexture	textures[2];	// 30
	UInt8		unk40[6];		// 40
	UInt8		pad46[2];		// 46
};

// 94
class TESCombatStyle : public TESForm
{
public:
	// 28
	struct Data14	// CSGD
	{
		float	unk00;	// 00 - init'd to 0.5
		float	unk04;	// 04 - init'd to 0.5
		float	unk08;	// 08 - init'd to 1
		float	unk0C;	// 0C - init'd to 1
		float	unk10;	// 10 - init'd to 1
		float	unk14;	// 14 - init'd to 1
		float	unk18;	// 18 - init'd to 1
		float	unk1C;	// 1C - init'd to 1
		float	unk20;	// 20 - init'd to 1
		float	unk24;	// 24 - init'd to 0.2
	};

	// 20
	struct Data3C	// CSME
	{
		float	unk00;	// 00 - init'd to 1
		float	unk04;	// 04 - init'd to 1
		float	unk08;	// 08 - init'd to 1
		float	unk0C;	// 0C - init'd to 1
		float	unk10;	// 10 - init'd to 1
		float	unk14;	// 14 - init'd to 1
		float	unk18;	// 18 - init'd to 1
		float	unk1C;	// 1C - init'd to 0.1
	};

	// 10
	struct Data5C	// CSCR
	{
		float	unk00;	// 00 - init'd to 0.2
		float	unk04;	// 04 - init'd to 0.2
		float	unk08;	// 08 - init'd to 0.2
		float	unk0C;	// 0C - init'd to 0.2
	};

	// 4
	struct Data6C	// CSLR
	{
		float	unk00;	// 00 - init'd to 0.2
	};

	// 20
	struct Data70	// CSFL
	{
		float	unk00;	// 00 - init'd to 0.5
		float	unk04;	// 04 - init'd to 1
		float	unk08;	// 08 - init'd to 0.5
		float	unk0C;	// 0C - init'd to 0.5
		float	unk10;	// 10 - init'd to 0.5
		float	unk14;	// 14 - init'd to 0.5
		float	unk18;	// 18 - init'd to 0.5
		float	unk1C;	// 1C - init'd to 0.75
	};

	Data14	unk14;		// 14 - CSGD
	Data3C	unk3C;		// 3C - CSME
	Data5C	unk5C;		// 5C - CSCR
	Data6C	unk6C;		// 6C - CSLR
	Data70	unk70;		// 70 - CSFL
	UInt8	unk90;		// 90 - DATA
	UInt8	pad91[3];	// 91
};

// 1D4
class TESEffectShader : public TESForm
{
public:
	// 190?
	struct Data
	{
		UInt8	pad[0x190];	// ###
	};

	Data		unk14;
	TESTexture	unk1A4;
	TESTexture	unk1AC;
	TESTexture	unk1B4;
	TESTexture	unk1BC;
	TESTexture	unk1C4;
	UInt32		unk1CC;	// BSIntrusiveRefCounted *
	UInt32		unk1D0;	// BSIntrusiveRefCounted *
};

// 28
class TESEyes : public TESForm
{
public:
	// parents
	TESFullName	fullName;	// 14
	TESTexture	texture;	// 1C

	// members
	UInt8		unk24;		// 24
	UInt8		pad25[3];	// 25
};

// 98
class TESFaction : public TESForm
{
public:
	// parents
	TESFullName		fullName;	// 14
	TESReactionForm	reaction;	// 1C

	// members

	// 2C
	struct Data34
	{
		UInt32	pad[0x2C / 4];
	};

	// 8
	struct Data80
	{
		UInt32	unk0;	// 0
		UInt32	unk4;	// 4
	};

	UInt32	unk2C;	// 2C
	UInt32	unk30;	// 30
	Data34	unk34;	// 34
	// 60

	Data80	unk80;	// 80
	UInt32	unk88;	// 88
	UInt32	unk8C;	// 8C
	float	unk90;	// 90
};
