#pragma once

#include "skse/GameTypes.h"
#include "skse/GameFormComponents.h"
#include "skse/GamePathing.h"
#include "skse/NiInterpolators.h"

class TESForm;
class TESObjectSTAT;
class TESFile;

typedef TESForm * (* _LookupFormByID)(UInt32 id);
extern const _LookupFormByID LookupFormByID;

// TESObject and derivatives are in GameObjects.h
// TESObjectREFR and derivatives are in GameReferences.h
// everything else deriving from TESForm goes here

/**** form types ***************************************************************
 *	
 *	TESHair and BGSCloudClusterForm were removed in 1.2
 *	
 *	1.1	1.2
 *	id	id	code	name
 *	
 *	00	00	NONE	
 *	01	01	TES4	
 *	02	02	GRUP	
 *	03	03	GMST	
 *	04	04	KYWD	BGSKeyword
 *	05	05	LCRT	BGSLocationRefType
 *	06	06	AACT	BGSAction
 *	07	07	TXST	
 *	08	08	MICN	BGSMenuIcon
 *	09	09	GLOB	TESGlobal
 *	0A	0A	CLAS	TESClass
 *	0B	0B	FACT	TESFaction
 *	0C	0C	HDPT	BGSHeadPart
 *	0D	xx	HAIR	TESHair
 *	0E	0D	EYES	TESEyes
 *	0F	0E	RACE	TESRace
 *	10	0F	SOUN	
 *	11	10	ASPC	
 *	12	11	SKIL	
 *	13	12	MGEF	EffectSetting
 *	14	13	SCPT	Script
 *	15	14	LTEX	TESLandTexture
 *	16	15	ENCH	
 *	17	16	SPEL	
 *	18	17	SCRL	
 *	19	18	ACTI	
 *	1A	19	TACT	
 *	1B	1A	ARMO	
 *	1C	1B	BOOK	
 *	1D	1C	CONT	
 *	1E	1D	DOOR	
 *	1F	1E	INGR	
 *	20	1F	LIGH	
 *	21	20	MISC	
 *	22	21	APPA	
 *	23	22	STAT	
 *	24	23	SCOL	
 *	25	24	MSTT	
 *	26	25	GRAS	
 *	27	26	TREE	
 *	28	xx	CLDC	BGSCloudClusterForm
 *	29	27	FLOR	
 *	2A	28	FURN	
 *	2B	29	WEAP	
 *	2C	2A	AMMO	
 *	2D	2B	NPC_	
 *	2E	2C	LVLN	
 *	2F	2D	KEYM	
 *	30	2E	ALCH	
 *	31	2F	IDLM	BGSDefaultObjectManager? strange
 *	32	30	NOTE	
 *	33	31	COBJ	BGSConstructibleObject
 *	34	32	PROJ	
 *	35	33	HAZD	
 *	36	34	SLGM	
 *	37	35	LVLI	
 *	38	36	WTHR	TESWeather
 *	39	37	CLMT	TESClimate
 *	3A	38	SPGD	
 *	3B	39	RFCT	BGSReferenceEffect
 *	3C	3A	REGN	TESRegion
 *	3D	3B	NAVI	NavMeshInfoMap
 *	3E	3C	CELL	TESObjectCELL
 *	3F	3D	REFR	TESObjectREFR / Actor
 *	40	3E	ACHR	Character / PlayerCharacter
 *	41	3F	PMIS	
 *	42	40	PARW	ArrowProjectile
 *	43	41	PGRE	GrenadeProjectile
 *	44	42	PBEA	BeamProjectile
 *	45	43	PFLA	FlameProjectile
 *	46	44	PCON	ConeProjectile
 *	47	45	PBAR	BarrierProjectile
 *	48	46	PHZD	Hazard
 *	49	47	WRLD	TESWorldSpace
 *	4A	48	LAND	TESObjectLAND
 *	4B	49	NAVM	NavMesh
 *	4C	4A	TLOD	
 *	4D	4B	DIAL	TESTopic
 *	4E	4C	INFO	TESTopicInfo
 *	4F	4D	QUST	TESQuest
 *	50	4E	IDLE	TESIdleForm
 *	51	4F	PACK	TESPackage
 *	52	50	CSTY	TESCombatStyle
 *	53	51	LSCR	TESLoadScreen
 *	54	52	LVSP	
 *	55	53	ANIO	TESObjectANIO
 *	56	54	WATR	TESWaterForm
 *	57	55	EFSH	TESEffectShader
 *	58	56	TOFT	
 *	59	57	EXPL	
 *	5A	58	DEBR	BGSDebris
 *	5B	59	IMGS	TESImageSpace
 *	5C	5A	IMAD	TESImageSpaceModifier
 *	5D	5B	FLST	BGSListForm
 *	5E	5C	PERK	BGSPerk
 *	5F	5D	BPTD	BGSBodyPartData
 *	60	5E	ADDN
 *	61	5F	AVIF	ActorValueInfo
 *	62	60	CAMS	BGSCameraShot
 *	63	61	CPTH	BGSCameraPath
 *	64	62	VTYP	BGSVoiceType
 *	65	63	MATT	BGSMaterialType
 *	66	64	IPCT	BGSImpactData
 *	67	65	IPDS	BGSImpactDataSet
 *	68	66	ARMA	
 *	69	67	ECZN	BGSEncounterZone
 *	6A	68	LCTN	BGSLocation
 *	6B	69	MESH	BGSMessage
 *	6C	6A	RGDL	BGSRagdoll
 *	6D	6B	DOBJ	
 *	6E	6C	LGTM	BGSLightingTemplate
 *	6F	6D	MUSC	BGSMusicType
 *	70	6E	FSTP	BGSFootstep
 *	71	6F	FSTS	BGSFootstepSet
 *	72	70	SMBN	BGSStoryManagerBranchNode
 *	73	71	SMQN	BGSStoryManagerQuestNode
 *	74	72	SMEN	BGSStoryManagerEventNode
 *	75	73	DLBR	BGSDialogueBranch
 *	76	74	MUST	BGSMusicTrackFormWrapper
 *	77	75	DLVW	
 *	78	76	WOOP	TESWordOfPower
 *	79	77	SHOU	TESShout
 *	7A	78	EQUP	BGSEquipSlot
 *	7B	79	RELA	BGSRelationship
 *	7C	7A	SCEN	BGSScene
 *	7D	7B	ASTP	BGSAssociationType
 *	7E	7C	OTFT	BGSOutfit
 *	7F	7D	ARTO	
 *	80	7E	MATO	BGSMaterialObject
 *	81	7F	MOVT	BGSMovementType
 *	82	80	SNDR	BGSSoundDescriptorForm
 *	83	81	DUAL
 *	84	82	SNCT	BGSSoundCategory
 *	85	83	SOPM	BGSSoundOutput
 *	86	84	COLL	BGSCollisionLayer
 *	87	85	CLFM	BGSColorForm
 *	88	86	REVB	BGSReverbParameters
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
	virtual void			InitItem(void);		// called once all dependent forms are loaded
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

	// 20
	struct Data60
	{
		UInt32	pad[0x20 / 4];
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
	Data60	unk60;	// 60
	Data80	unk80;	// 80
	UInt32	unk88;	// 88
	UInt32	unk8C;	// 8C
	float	unk90;	// 90
	UInt32	unk94;	// 94
};

// 24
class TESGlobal : public TESForm
{
public:
	BSString	unk14;	// 14
	UInt8		unk1C;	// 1C - type?
	UInt8		pad[3];	// 1D
	UInt32		unk20;	// 20
};

// 50
class TESHair : public TESForm
{
public:
	// parents
	TESFullName	fullName;	// 14
	TESModel	model;		// 1C
	TESTexture	texture;	// 30

	// members
	UInt8		unk38;		// 38
	UInt8		pad39[3];	// 39
	TESModel	unk40;		// 3C
};

// 3C
class TESIdleForm : public TESForm
{
public:
	void				* unk14;	// 14 - linked list
	UInt8				unk18;		// 18
	UInt8				unk19;		// 19
	UInt8				unk1A;		// 1A
	UInt8				pad1B;		// 1B
	UInt16				unk1C;		// 1C
	UInt8				pad1E[2];	// 1E
	UInt32				unk20;		// 20
	UInt32				unk24;		// 24
	UInt32				unk28;		// 28
	StringCache::Ref	unk2C;		// 2C
	StringCache::Ref	unk30;		// 30
	BSString			unk34;		// 34
};

// 64
class TESImageSpace : public TESForm
{
public:
	// 50
	struct Data14
	{
		float	unk00;	// 00 - init'd to 3
		float	unk04;	// 04 - init'd to 7
		float	unk08;	// 08 - init'd to .6
		float	unk0C;	// 0C - init'd to .5
		float	unk10;	// 10 - init'd to .15
		float	unk14;	// 14 - init'd to .15
		float	unk18;	// 18 - init'd to 1.8
		float	unk1C;	// 1C - init'd to 1.5
		float	unk20;	// 20 - init'd to 3.5, 3
		float	unk24;	// 24 - init'd to 1.8, .8
		float	unk28;	// 28 - init'd to 1.5
		float	unk2C;	// 2C - init'd to 1.1
		float	unk30;	// 30 - init'd to 0
		float	unk34;	// 34 - init'd to 0
		float	unk38;	// 38 - init'd to 0
		float	unk3C;	// 3C - init'd to 0
		float	unk40;	// 40 - init'd to 0
		UInt32	unk44;	// 44 - init'd to 0
		UInt32	unk48;	// 48 - init'd to 0
		float	unk4C;	// 4C - init'd to 2
	};

	Data14	unk14;	// 14
};

// 72C
// ### todo
class TESImageSpaceModifier : public TESForm
{
public:
	// 0F4
	struct Data014
	{
		// 8
		struct Data0CC
		{
			float	unk0;
			float	unk4;
		};

		UInt8	unk000;		// 000
		UInt8	pad001[3];	// 001
		float	unk004;		// 004
		// 008

		UInt8	todo008[0xC8 - 0x08];	// 008

		UInt8	unk0C8;		// 0C8
		UInt8	unk0C9[3];	// 0C9
		Data0CC	unk0CC;		// 0CC
		// 0D4

		UInt8	todo0D4[0xE0 - 0xD4];	// 0D4

		UInt8	unk0E0;		// 0E0
		UInt8	unk0E1;		// 0E1
		UInt8	pad0E2[2];	// 0E2
		// 0E4

		UInt8	todo0E4[0xF4 - 0xE4];	// 0E4
	};

	Data014				unk014;				// 014
	NiFloatInterpolator	unk108[0x15 * 2];	// 108
	NiFloatInterpolator	unk4F8;				// 4F8
	NiFloatInterpolator	unk510;				// 510
	NiColorInterpolator	unk528;				// 528
	NiColorInterpolator	unk54C;				// 54C
	NiFloatInterpolator	unk570;				// 570
	NiFloatInterpolator	unk588;				// 588
	NiFloatInterpolator	unk5A0;				// 5A0
	NiFloatInterpolator	unk5B8;				// 5B8
	NiFloatInterpolator	unk5D0;				// 5D0
	NiFloatInterpolator	unk5E8;				// 5E8
	NiFloatInterpolator	unk600;				// 600
	NiFloatInterpolator	unk618;				// 618
	NiFloatInterpolator	unk630;				// 630
	// 648

	UInt8				todo648[0x724 - 0x648];	// 348

	BSString			unk724;				// 724
};

STATIC_ASSERT(offsetof(TESImageSpaceModifier, unk108) == 0x108);
STATIC_ASSERT(offsetof(TESImageSpaceModifier, unk4F8) == 0x4F8);
STATIC_ASSERT(sizeof(TESImageSpaceModifier) == 0x72C);

// 2C
class TESLandTexture : public TESForm
{
public:
	struct Data24
	{
		UInt32	unk0;	// 0
		UInt32	unk4;	// 4
	};

	UInt32	unk14;		// 14
	UInt8	unk18;		// 18
	UInt8	unk19;		// 19
	UInt8	pad1A[2];	// 1A
	UInt32	unk1C;		// 1C
	UInt8	unk20;		// 20
	UInt8	pad21[3];	// 21
	Data24	unk24;		// 24
};

// 20
class TESLoadScreen : public TESForm
{
public:
	void				* unk14;	// 14 - linked list
	TESObjectSTAT		* object;	// 18
	StringCache::Ref	unk1C;		// 1C
};

// 38
class TESObjectANIO : public TESForm
{
public:
	TESModelTextureSwap	textureSwap;	// 14
	StringCache::Ref	unk30;			// 30
	StringCache::Ref	unk34;			// 34
};

// 8C
class TESObjectCELL : public TESForm
{
public:
	// parents
	TESFullName					fullName;	// 14

	// members

	// 8
	struct Data
	{
		UInt32	unk0;
		UInt32	unk4;
	};

	// 8
	struct Data4C
	{
		void	* unk0;	// BSIntrusiveRefCounted at offset 14
		UInt32	unk4;
	};

	Data						unk1C;		// 1C
	Data						unk24;		// 24
	UInt16						unk2C;		// 2C
	UInt16						unk2E;		// 2E
	UInt8						unk30;		// 30
	UInt8						unk31;		// 31
	UInt8						unk32;		// 32
	UInt8						pad33;		// 33
	TESAIForm::Data				unk34;		// 34 - ExtraDataList
	void						* unk3C;	// 3C
	UInt32						unk40;		// 40
	UInt32						unk44;		// 44
	UInt32						unk48;		// 48
	Data4C						unk4C;		// 4C
	TESActorBaseData::Data2C	unk54;		// 54
	TESActorBaseData::Data2C	unk60;		// 60
	TESActorBaseData::Data2C	unk6C;		// 6C
	Data						unk78;		// 78
	UInt32						unk80;		// 80
	UInt32						unk84;		// 84
	UInt32						unk88;		// 88
};

// 28
class TESObjectLAND : public TESForm
{
public:
	// parents
	TESChildCell	childCell;	// 14

	// members
	UInt32		unk18;	// 18
	UInt32		unk1C;	// 1C
	UInt32		unk20;	// 20
	UInt32		unk24;	// 24
};

// 80
class TESPackage : public TESForm
{
public:
	virtual bool	Unk_39(UInt32 arg0, UInt32 arg1, UInt32 arg2, UInt32 arg3);
	virtual bool	Unk_3A(UInt32 arg0, UInt32 arg1, UInt32 arg2, UInt32 arg3, UInt32 arg4);
	virtual bool	Unk_3B(UInt32 arg0, UInt32 arg1);
	virtual bool	Unk_3C(UInt32 arg0, UInt32 arg1);
	virtual bool	Unk_3D(UInt32 arg0);

	enum
	{
		kPackageType_Find = 0,
		kPackageType_Follow,
		kPackageType_Escort,
		kPackageType_Eat,
		kPackageType_Sleep,
		kPackageType_Wander,
		kPackageType_Travel,
		kPackageType_Accompany,
		kPackageType_UseItemAt,
		kPackageType_Ambush,
		kPackageType_FleeNotCombat,
		kPackageType_CastMagic,
		kPackageType_Sandbox,
		kPackageType_Patrol,
		kPackageType_Guard,
		kPackageType_Dialogue,
		kPackageType_UseWeapon,
		kPackageType_Find2,
		kPackageType_Package,
		kPackageType_PackageTemplate,
		kPackageType_Activate,
		kPackageType_Alarm,
		kPackageType_Flee,
		kPackageType_Trespass,
		kPackageType_Spectator,
		kPackageType_ReactToDead,
		kPackageType_GetUpFromChair,
		kPackageType_DoNothing,
		kPackageType_InGameDialogue,
		kPackageType_Surface,
		kPackageType_SearchForAttacker,
		kPackageType_AvoidPlayer,
		kPackageType_ReactToDestroyedObject,
		kPackageType_ReactToGrenadeOrMine,
		kPackageType_StealWarning,
		kPackageType_PickPocketWarning,
		kPackageType_MovementBlocked
	};

	// C
	struct Data30
	{
		UInt8	unk00;		// 0
		UInt8	unk01;		// 1
		UInt8	unk02;		// 2
		UInt8	unk03;		// 3
		UInt8	unk04;		// 4
		UInt8	pad05[3];	// 5
		UInt32	unk08;		// 8
	};

	// 10
	struct Data
	{
		UInt32	unk00;	// 00
		UInt32	unk04;	// 04
		UInt32	unk08;	// 08
		UInt32	unk0C;	// 0C
	};

	UInt32	packageFlags;	// 14
	UInt8	type;			// 18 - see kPackageType_ enum
	UInt8	unk19;			// 19
	UInt8	unk1A;			// 1A
	UInt8	pad1B;			// 1B
	UInt16	unk1C;			// 1C
	UInt16	unk1E;			// 1E
	UInt32	unk20;			// 20
	UInt32	unk24;			// 24
	UInt32	unk28;			// 28
	UInt32	unk2C;			// 2C
	Data30	unk30;			// 30
	void	* unk3C;		// 3C - linked list
	UInt32	unk40;			// 40
	UInt32	unk44;			// 44
	Data	unk48;			// 48
	Data	unk58;			// 58
	Data	unk68;			// 68
	UInt32	unk78;			// 78
	UInt32	unk7C;			// 7C - incremented in dtor
};

// 8C
class AlarmPackage : public TESPackage
{
public:
	UInt32	unk80;		// 80
	UInt32	unk84;		// 84
	UInt8	unk88;		// 88
	UInt8	pad89[3];	// 89
};

// A0
class DialoguePackage : public TESPackage
{
public:
	UInt32	unk80;		// 80
	UInt32	unk84;		// 84
	UInt32	unk88;		// 88
	UInt32	unk8C;		// 8C
	UInt8	unk90;		// 90
	UInt8	unk91;		// 91
	UInt8	pad92[2];	// 92
	UInt32	unk94;		// 94
	UInt32	unk98;		// 98
	UInt8	unk9C;		// 9C
	UInt8	pad9D[3];	// 9D
};

// AC
class FleePackage : public TESPackage
{
public:
	struct Data8C
	{
		UInt32	unk0;	// 0
		UInt32	unk4;	// 4
		UInt32	unk8;	// 8
	};

	TESActorBaseData::Data2C	unk80;	// 80
	Data8C	unk8C;		// 8C
	float	unk98;		// 98
	UInt32	unk9C;		// 9C
	UInt32	unkA0;		// A0
	UInt8	unkA4;		// A4
	UInt8	unkA5;		// A5
	UInt8	unkA6;		// A6
	UInt8	unkA7;		// A7
	UInt8	unkA8;		// A8
	UInt8	padA9[3];	// A9
};

// B0
class SpectatorPackage : public TESPackage
{
public:
	struct Data94
	{
		UInt32	unk0;	// 0
		UInt32	unk4;	// 4
		UInt32	unk8;	// 8
	};

	UInt32	unk80;		// 80
	UInt32	pad84;		// 84 - not init'd
	UInt32	unk88;		// 88
	UInt32	unk8C;		// 8C
	UInt8	unk90;		// 90
	UInt8	pad91[3];	// 91
	Data94	unk94;		// 94
	TESActorBaseData::Data2C	unkA0;	// A0
	UInt32	padAC;		// AC - not init'd
};

// 98
class TrespassPackage : public TESPackage
{
public:
	UInt32	unk80;	// 80
	UInt32	unk84;	// 84
	UInt32	unk88;	// 88
	UInt32	unk8C;	// 8C
	UInt32	unk90;	// 90
	UInt32	unk94;	// 94
};

// 29C
class TESRace : public TESForm
{
public:
	// parents
	TESFullName			fullName;		// 14
	TESDescription		description;	// 1C
	TESSpellList		spellList;		// 28
	BGSSkinForm			skin;			// 30
	BGSBipedObjectForm	biped;			// 38
	BGSKeywordForm		keyword;		// 48
	BGSAttackDataForm	attackData;		// 54

	// members

	// 80
	struct Data84
	{
		UInt8	unk00[0x0E];		// 00
		UInt8	pad0E[2];			// 0E
		float	unk10[2];			// 10
		float	unk18[2];			// 18
		UInt32	unk20;				// 20 - not init'd
		float	health;				// 24
		float	magicka;			// 28
		float	stamina;			// 2C
		UInt32	unk30;				// 30 - not init'd
		float	mass;				// 34
		float	unk38;				// 38 - init'd to 1
		float	unk3C;				// 3C - init'd to 1
		UInt32	unk40;				// 40 - init'd to 1
		UInt32	unk44;				// 44 - init'd to FFFFFFFF
		UInt32	unk48;				// 48 - init'd to FFFFFFFF
		UInt32	unk4C;				// 4C - not init'd
		UInt32	unk50;				// 50 - init'd to FFFFFFFF
		UInt32	unk54;				// 54
		UInt32	unk58;				// 58
		UInt32	unk5C;				// 5C
		UInt32	unk60;				// 60 - init'd to 0
		float	handReach;			// 64
		UInt32	unk68;				// 68 - init'd to FFFFFFFF
		UInt32	unk6C;				// 6C - init'd to 0
		UInt32	unk70;				// 70 - init'd to 0
		float	unk74;				// 74 - init'd to 0
		float	angleTolerance;		// 78
		float	angleTolerance2;	// 7C
	};

	TESModel					models[2];			// 5C
	Data84						unk84;				// 84
	UInt32						unk104;				// 104
	UInt32						unk108;				// 108
	BGSTextureModel				textureModel[2];	// 10C
	BGSBehaviorGraphModel		behaviorGraph[2];	// 134
	StringCache::Ref			unk15C[2];			// 15C
	StringCache::Ref			unk164[2];			// 164
	BGSVoiceType				* voiceTypes[2];	// 16C
	UInt32						unk174;				// 174
	UInt32						unk178;				// 178
	UInt32						unk17C;				// 17C
	TESActorBaseData::Data2C	unk180[2];			// 180
	void						* unk198[4];		// 198
	void						* unk1A8[2];		// 1A8 - refcounted ptr
	StringCache::Ref			unk1B0;				// 1B0
	UInt32						unk1B4;				// 1B4
	UInt32						unk1B8;				// 1B8
	UInt32						unk1BC;				// 1BC
	UInt32						unk1C0;				// 1C0
	UInt32						unk1C4;				// 1C4
	StringCache::Ref			unk1C8[0x20];		// 1C8
	TESActorBaseData::Data2C	unk248;				// 248
	UInt32						unk254;				// 254
	UInt32						unk258;				// 258
	UInt32						unk25C;				// 25C
	UInt32						unk260;				// 260
	TESActorBaseData::Data2C	unk264;				// 264
	TESActorBaseData::Data2C	unk270;				// 270
	UInt8						unk27C[0x18];		// 27C
	UInt32						unk294;				// 294
	UInt32						unk298;				// 298
};

STATIC_ASSERT(offsetof(TESRace, unk1B0) == 0x1B0);
STATIC_ASSERT(sizeof(TESRace) == 0x29C);

// 30
class TESRegion : public TESForm
{
public:
	virtual bool	Unk_39(void);

	// C
	struct Data14
	{
		UInt32	unk0;		// 0
		UInt32	unk4;		// 4
		UInt8	unk8;		// 8
		UInt8	unk9[3];	// 9
	};

	// 8
	struct Data18
	{
		UInt32	unk0;
		UInt32	unk4;
	};

	// C
	struct Data24
	{
		UInt32	unk0;
		UInt32	unk4;
		UInt32	unk8;
	};

	Data14	* unk14;	// 14
	Data18	* unk18;	// 18
	UInt32	unk1C;		// 1C
	UInt32	unk20;		// 20
	Data24	unk24;		// 24
};

// 5C
class TESShout : public TESForm
{
public:
	// parents
	TESFullName				fullName;		// 14
	BGSMenuDisplayObject	menuDispObject;	// 1C
	BGSEquipType			equipType;		// 24
	TESDescription			description;	// 2C

	// members

	// C
	struct Data38
	{
		UInt32	unk0;
		UInt32	unk4;
		UInt32	unk8;
	};

	Data38	unk38[3];	// 38
};

// 38
class TESTopic : public TESForm
{
public:
	// parents
	TESFullName			fullName;	// 14

	// members
	UInt8				unk1C[4];	// 1C
	UInt32				unk20;		// 20
	UInt32				unk24;		// 24
	UInt32				unk28;		// 28
	void				** unk2C;	// 2C - buf[unk30]
	UInt32				unk30;		// 30 - len
	StringCache::Ref	unk34;		// 34
};

// 34
class TESTopicInfo : public TESForm
{
public:
	struct Data28
	{
		UInt32	unk0;	// 0
		UInt32	unk4;	// 4
	};

	void	* unk1C;	// 1C - linked list
	UInt16	unk20;		// 20
	UInt8	unk22;		// 22
	UInt8	unk23;		// 23
	UInt8	unk24;		// 24
	Data28	unk28;		// 28
	UInt32	unk30;		// 30
};

// 1D4
class TESWaterForm : public TESForm
{
public:
	// parents
	TESFullName			fullName;		// 14
	TESAttackDamageForm	attackDamage;	// 1C

	// members

	// 10
	struct Data2C
	{
		UInt32	unk0;	// 0
		UInt32	unk4;	// 4
		UInt32	unk8;	// 8
		UInt32	unkC;	// C
	};

	// E4
	struct Data80
	{
		float	unk00;		// 00 - init'd to .1
		float	unk04;		// 04 - init'd to 90
		float	unk08;		// 08 - init'd to .5
		float	unk0C;		// 0C - init'd to 1
		float	unk10;		// 10 - init'd to 50
		float	unk14;		// 14 - init'd to .5
		float	unk18;		// 18 - init'd to .025
		UInt32	unk1C;		// 1C - init'd to 0
		UInt32	unk20;		// 20 - init'd to 0
		UInt32	unk24;		// 24 - init'd to 0
		UInt32	unk28;		// 28 - init'd to 00808000
		UInt32	unk2C;		// 2C - init'd to 00190000
		UInt32	unk30;		// 30 - init'd to 00FFFFFF
		UInt8	unk34;		// 34 - init'd to 0
		UInt8	pad35[3];	// 35
		float	unk38;		// 38 - init'd to 0.1
		float	unk3C;		// 3C - init'd to 0.6
		float	unk40;		// 40 - init'd to 0.985
		float	unk44;		// 44 - init'd to 2
		float	unk48;		// 48 - init'd to .01
		float	unk4C;		// 4C - init'd to .4
		float	unk50;		// 50 - init'd to .6
		float	unk54;		// 54 - init'd to .985
		float	unk58;		// 58 - init'd to 10
		float	unk5C;		// 5C - init'd to .05
		float	unk60;		// 60 - init'd to 300
		UInt32	unk64;		// 64 - init'd to 0
		UInt32	unk68;		// 68 - init'd to 0
		UInt32	unk6C;		// 6C - init'd to 0
		UInt32	unk70;		// 70 - init'd to 0
		UInt32	unk74;		// 74 - init'd to 0
		UInt32	unk78;		// 78 - init'd to 0
		float	unk7C;		// 7C - init'd to 300
		float	unk80;		// 80 - init'd to 300
		float	unk84;		// 84 - init'd to 1
		UInt32	unk88;		// 88 - not init'd
		float	unk8C;		// 8C - init'd to 1
		UInt32	unk90;		// 90 - init'd to 0
		float	unk94;		// 94 - init'd to 1000
		float	unk98;		// 98 - init'd to 250
		float	unk9C;		// 9C - init'd to 100
		float	unkA0;		// A0 - init'd to 1
		float	unkA4;		// A4 - init'd to 10000
		float	unkA8;		// A8 - init'd to 1
		float	unkAC;		// AC - init'd to 100
		float	unkB0;		// B0 - init'd to 100
		float	unkB4;		// B4 - init'd to 100
		UInt32	unkB8;		// B8 - init'd to 0
		UInt32	unkBC;		// BC - init'd to 0
		UInt32	unkC0;		// C0 - init'd to 0
		float	unkC4;		// C4 - init'd to 1
		float	unkC8;		// C8 - init'd to 1
		float	unkCC;		// CC - init'd to 1
		float	unkD0;		// D0 - init'd to 1
		float	unkD4;		// D4 - init'd to 1
		float	unkD8;		// D8 - init'd to 1
		float	unkDC;		// DC - init'd to 1
		float	unkE0;		// E0 - init'd to 1
	};

	// C
	struct Data1C8
	{
		UInt32	unk0;	// 0
		UInt32	unk4;	// 4
		UInt32	unk8;	// 8
	};

	UInt8		unk024;		// 024
	UInt8		pad025[3];	// 025
	UInt32		unk028;		// 028
	Data2C		unk02C;		// 02C
	Data2C		unk03C;		// 03C
	Data2C		unk04C;		// 04C
	TESTexture	unk05C;		// 05C
	TESTexture	unk064;		// 064
	TESTexture	unk06C;		// 06C
	UInt8		unk074;		// 074
	UInt8		unk075;		// 075
	UInt8		pad076[2];	// 076
	UInt32		unk078;		// 078
	UInt32		unk07C;		// 07C
	Data80		unk080;		// 080
	UInt32		unk164[3];	// 164
	UInt32		unk170;		// 170
	UInt32		unk174;		// 174
	UInt32		unk178;		// 178
	UInt32		unk17C;		// 17C
	UInt32		unk180;		// 180
	float		unk184;		// 184
	float		unk188;		// 188
	float		unk18C;		// 18C
	float		unk190;		// 190
	UInt32		unk194;		// 194
	UInt32		unk198;		// 198
	UInt32		unk19C;		// 19C
	UInt32		unk1A0;		// 1A0
	UInt32		unk1A4;		// 1A4
	UInt32		unk1A8;		// 1A8
	void		* unk1AC;	// 1AC - refcounted ptr
	UInt32		unk1B0;		// 1B0
	UInt8		unk1B4;		// 1B4
	UInt8		pad1B5[3];	// 1B5
	UInt32		unk1B8;		// 1B8
	Data1C8		unk1BC;		// 1BC
	Data1C8		unk1C8;		// 1C8
};

STATIC_ASSERT(sizeof(TESWaterForm) == 0x1D4);

// 760
class TESWeather : public TESForm
{
public:
	// 110
	struct Data58C
	{
		UInt32	unk000[0xE0 / 4];	// 000 ### todo
		UInt32	unk0E0;				// 0E0 - init'd to 00FFFFFF
		UInt32	unk0E4;				// 0E4 - init'd to 00FFFFFF
		UInt32	unk0E8;				// 0E8 - init'd to 00FFFFFF
		UInt32	unk0EC;				// 0EC - init'd to 00FFFFFF
		UInt32	unk0F0;				// 0F0 - init'd to 00FFFFFF
		UInt32	unk0F4;				// 0F4 - init'd to 00FFFFFF
		UInt32	unk0F8;				// 0F8 - init'd to 00FFFFFF
		UInt32	unk0FC;				// 0FC - init'd to 00FFFFFF
		UInt32	unk100;				// 100 - init'd to 00FFFFFF
		UInt32	unk104;				// 104 - init'd to 00FFFFFF
		UInt32	unk108;				// 108 - init'd to 00FFFFFF
		UInt32	unk10C;				// 10C - init'd to 00FFFFFF
	};

	// 13
	struct Data558
	{
		UInt8	unk00[0x13];			// 00
	};

	// 20
	struct Data56C
	{
		UInt32	unk00[0x10 / 4];		// 00
		float	unk10;					// 10
		float	unk14;					// 14
		float	unk18;					// 18
		float	unk1C;					// 1C
	};

	// 10
	struct Data354
	{
		float	unk0;	// 0
		float	unk4;	// 4
		float	unk8;	// 8
		float	unkC;	// C
	};

	// 10
	struct Data6B4
	{
		UInt32	unk00[0x10 / 4];	// 00
	};

	TESTexture1024	texture[0x20];		// 014
	UInt8			unk114[0x20];		// 114 - cleared to 0x7F
	UInt8			unk134[0x20];		// 134 - cleared to 0x7F
	UInt8			unk154[0x200];		// 154
	Data354			unk354[0x20];		// 354
	UInt32			unk554;				// 554
	Data558			unk558;				// 558
	UInt8			pad56B;				// 56B
	Data56C			unk56C;				// 56C
	Data58C			unk58C;				// 58C
	TESAIForm::Data	unk69C;				// 69C
	TESActorBaseData::Data2C	unk6A4;	// 6A4
	UInt32			pad6B0;				// 6B0 - not init'd
	Data6B4			unk6B4;				// 6B4
	BGSLightingTemplate::Data::Data28	unk6C4[4];	// 6C4
	TESModel		unk744;	// 744
	UInt32			unk758;	// 758
	UInt32			unk75C;	// 75C
};

STATIC_ASSERT(sizeof(TESWeather) == 0x760);

// 20
class TESWordOfPower : public TESForm
{
public:
	// parents
	TESFullName			fullName;	// 14

	// members
	StringCache::Ref	word;		// 1C
};

// 174
class TESWorldSpace : public TESForm
{
public:
	// parents
	TESFullName		fullName;	// 14
	TESTexture		texture;	// 1C

	// members

	// 4
	struct Data038
	{
		UInt16	unk0;
		UInt16	unk2;
	};

	// 020
	struct Data03C
	{
		UInt8	unk0[0x20];
	};

	// ?
	struct OFFSET_DATA { };

	// 40
	struct Data12C
	{
		// this struct keeps showing up everywhere
		struct Entry
		{
			UInt8	pad00[8];	// 00
			UInt32	unk08;		// 08
			UInt32	unk0C;		// 0C
			UInt32	unk10;		// 10
			void	* unk14;	// 14
			UInt8	pad18[4];	// 18
			UInt32	unk1C;		// 1C
		};

		Entry	unk00;
		Entry	unk20;
	};

	typedef NiTPointerMap <int, TESObjectCELL *>	CellMap;

	CellMap	* cellMap;	// 024
	UInt32	unk028;		// 028
	UInt32	unk02C;		// 02C
	UInt32	unk030;		// 030
	UInt8	worldSpaceFlags;	// 034
	UInt8	pad035;		// 035
	UInt16	unk036;		// 036
	Data038	unk038;		// 038
	Data03C	unk03C;		// 03C
	TESActorBaseData::Data2C	unk05C;	// 05C
	UInt32	unk068;		// 068
	UInt32	unk06C;		// 06C
	TESQuest::Data05C	unk070;	// 070
	void	* unk090;	// 090 - refcounted ptr
	UInt32	unk094;		// 094
	UInt32	unk098;		// 098
	UInt32	unk09C;		// 09C
	UInt32	unk0A0;		// 0A0
	UInt32	unk0A4;		// 0A4
	UInt32	unk0A8;		// 0A8
	UInt32	unk0AC;		// 0AC
	UInt32	unk0B0;		// 0B0
	UInt32	unk0B4;		// 0B4
	UInt32	unk0B8;		// 0B8
	UInt8	unk0BC[0x10];	// 0BC
	float	unk0CC;		// 0CC
	UInt32	unk0D0;		// 0D0
	UInt32	unk0D4;		// 0D4
	UInt32	unk0D8;		// 0D8
	UInt32	unk0DC;		// 0DC
	UInt32	unk0E0;		// 0E0
	UInt32	unk0E4;		// 0E4
	UInt32	unk0E8;		// 0E8
	UInt32	unk0EC;		// 0EC
	NiTMap <TESFile *, TESWorldSpace::OFFSET_DATA *>	unk0F0;	// 0F0
	BSString	unk100;	// 100
	void		* unk108;	// 108
	UInt32		unk10C;	// 10C
	float		unk110;	// 110
	UInt32		unk114;	// 114
	UInt32		unk118;	// 118
	TESTexture	unk11C;	// 11C
	TESTexture	unk124;	// 124
	Data12C		unk12C;	// 12C
	UInt32		unk16C;	// 16C
	UInt32		unk170;	// 170
};

STATIC_ASSERT(sizeof(TESWorldSpace) == 0x174);
