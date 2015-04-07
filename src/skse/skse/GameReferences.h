#pragma once

#include "skse/GameFormComponents.h"
#include "skse/GameForms.h"
#include "skse/GameEvents.h"
#include "skse/NiObjects.h"
#include "GameBSExtraData.h"

class BSAnimationGraphEvent;
class NiNode;
class TESObjectREFR;
class BSFaceGenNiNode;

// TESObjectREFR and child classes

// 08
class BSHandleRefObject : public NiRefObject
{
public:
	enum
	{
		kMask_RefCount = 0x3FF
	};

	UInt32 GetRefCount() const
	{
		return m_uiRefCount & 0x3FF;
	}
};

// The refHandle is stored in BSHandleRefObject.m_uiRefCount
// Bits:
//	01 - 10	ref count
//	11		isHandleSet
//	12 - ??	handle (seems to be divided in two parts, 0xFFFFF and 0x3F00000)

// Adds entry to lookup table if not yet there
typedef void (* _CreateRefHandleByREFR)(UInt32 * refHandleOut, TESObjectREFR * refr);
extern const _CreateRefHandleByREFR CreateRefHandleByREFR;

// Note: May set refHandle to 0
typedef bool (* _LookupREFRByHandle)(UInt32 * refHandle, TESObjectREFR ** refrOut);
extern const _LookupREFRByHandle LookupREFRByHandle;

extern const UInt32 * g_invalidRefHandle;

// 4
class IAnimationGraphManagerHolder
{
public:
	virtual ~IAnimationGraphManagerHolder();

	virtual UInt32			Unk_01(void);
	virtual UInt32			Unk_02(void);
	virtual UInt32			Unk_03(void);
	virtual UInt32			Unk_04(void);
	virtual UInt32			Unk_05(void);
	virtual UInt32			Unk_06(void);
	virtual UInt32			Unk_07(void);
	virtual UInt32			Unk_08(void);
	virtual UInt32			Unk_09(void);
	virtual UInt32			Unk_0A(void);
	virtual UInt32			Unk_0B(void);
	virtual UInt32			Unk_0C(void);
	virtual UInt32			Unk_0D(void);
	virtual UInt32			Unk_0E(void);
	virtual UInt32			Unk_0F(void);
	virtual UInt32			Unk_10(void);
	virtual UInt32			Unk_11(void);
	virtual UInt32			Unk_12(void);

//	void	** _vtbl;
};

// 128
class IPostAnimationChannelUpdateFunctor
{
public:
	virtual ~IPostAnimationChannelUpdateFunctor();
//	void	** _vtbl;
};

// 54
class TESObjectREFR : public TESForm
{
public:
	enum { kTypeID = kFormType_Reference };

	enum
	{
		kFlag_Harvested = 0x2000,
	};

	// currently none of these have been analyzed
	virtual void	Unk_39(void);
	virtual void	Unk_3A(void);
	virtual void	Unk_3B(void);
	virtual void	Unk_3C(void);
	virtual void	Unk_3D(void);
	virtual void	Unk_3E(void);
	virtual void	Unk_3F(void);
	virtual void	Unk_40(void);
	virtual void	Unk_41(void);
	virtual void	Unk_42(void);
	virtual void	Unk_43(void);
	virtual void	Unk_44(void);
	virtual void	Unk_45(void);
	virtual void	Unk_46(void);
	virtual void	Unk_47(void);
	virtual void	Unk_48(void);
	virtual void	Unk_49(void);
	virtual void	Unk_4A(void);
	virtual void	Unk_4B(void);
	virtual void	Unk_4C(void);
	virtual void	Unk_4D(void);
	virtual void	Unk_4E(void);
	virtual void	Unk_4F(void);
	virtual void	Unk_50(void);
	virtual void	GetStartingPos(float * pos);
	virtual void	Unk_52(void);
	virtual void	Unk_53(void);
	virtual void	Unk_54(void);
	virtual void	Unk_55(void);
	virtual void	Unk_56(void);
	virtual void	Unk_57(void);
	virtual void	Unk_58(void);
	virtual void	Unk_59(void);
	virtual void	Unk_5A(void);
	virtual void	Unk_5B(void);
	virtual void	Unk_5C(void);
	virtual void	Unk_5D(void);
	virtual void	Unk_5E(void);
	virtual void	Unk_5F(void);
	virtual void	Unk_60(void);
	virtual BSFaceGenNiNode *	GetFaceGenNiNode(void);
	virtual void	Unk_62(void);
	virtual void	Unk_63(void);
	virtual void	Unk_64(void);
	virtual void	Unk_65(void);
	virtual void	Unk_66(void);
	virtual void	Unk_67(void);
	virtual void	Unk_68(void);
	virtual void	Unk_69(void);
	virtual void	Unk_6A(void);
	virtual void *	Unk_6B(void);	// tested in HasLoaded3D, possibly NiNode * Get3D()
	virtual void	Unk_6C(void);
	virtual void	Unk_6D(void);
	virtual void	Unk_6E(void);
	virtual void	Unk_6F(void);
	virtual NiNode *	GetNiNode(void);	// Root of the skeleton
	virtual void	Unk_71(void);
	virtual void	Unk_72(void);
	virtual void	Unk_73(void);
	virtual void	Unk_74(void);
	virtual void	Unk_75(void);
	virtual void	Unk_76(void);
	virtual void	Unk_77(void);
	virtual void	Unk_78(void);
	virtual void	Unk_79(void);
	virtual void	Unk_7A(void);
	virtual void	Unk_7B(void);
	virtual void	Unk_7C(void);
	virtual void	Unk_7D(void);
	virtual void	Unk_7E(void);
	virtual void	Unk_7F(void);
	virtual void	Unk_80(void);
	virtual void	Unk_81(void);
	virtual void	Unk_82(void);
	virtual void	Unk_83(void);
	virtual void	Unk_84(void);
	virtual void	Unk_85(void);
	virtual void	Unk_86(void);
	virtual void	Unk_87(void);
	virtual void	Unk_88(void);
	virtual void	ResetInventory(bool unk);
	virtual void	Unk_8A(void);
	virtual void	Unk_8B(void);
	virtual void	Unk_8C(void);
	virtual void	Unk_8D(void);
	virtual void	Unk_8E(void);
	virtual void	Unk_8F(void);
	virtual void	Unk_90(void);
	virtual void	Unk_91(void);
	virtual void	Unk_92(void);
	virtual void	Unk_93(void);
	virtual void	Unk_94(void);
	virtual void	Unk_95(void);
	virtual void	Unk_96(void);
	virtual void	Unk_97(void);
	virtual void	Unk_98(void);
	virtual void	Unk_99(void);
	virtual void	Unk_9A(void);
	virtual void	Unk_9B(void);

	struct LoadedState
	{
		UInt32	unk00;	// 00
		UInt32	unk04;	// 04
		UInt32	unk08;	// 08
		UInt32	unk0C;	// 0C
		UInt32	unk10;	// 10
		UInt32	unk14;	// 14
		UInt32	unk18;	// 18
		UInt32	unk1C;	// 1C
		NiNode	* node;	// 20
		// ... probably more
	};

	// parents
	BSHandleRefObject	handleRefObject;	// 14
	BSTEventSink <BSAnimationGraphEvent>	animGraphEventSink;	// 1C
	IAnimationGraphManagerHolder			animGraphHolder;	// 20

	// members
	TESForm* baseForm;	// 24
	float	rotX;		// 28
	float	rotY;		// 2C
	float	rotZ;		// 30
	float	posX;		// 34
	float	posY;		// 38
	float	posZ;		// 3C
	
	TESObjectCELL	* parentCell;	// 40
	LoadedState		* loadedState;	// 44
	BaseExtraList	extraData;		// 48
	UInt32			unk50;			// flags?

	UInt32 CreateRefHandle(void);

	MEMBER_FN_PREFIX(TESObjectREFR);
	DEFINE_MEMBER_FN(GetBaseScale, float, 0x004D5230);
};
STATIC_ASSERT(sizeof(TESObjectREFR) == 0x54);
STATIC_ASSERT(offsetof(TESObjectREFR, handleRefObject) == 0x14);

// 04
class IMovementInterface
{
public:
	virtual ~IMovementInterface();
//	void	** _vtbl;	// 00
};

// 04
class IMovementState : public IMovementInterface
{
public:
	virtual ~IMovementState();
};

// 0C
class ActorState : public IMovementState
{
public:
	virtual ~ActorState();

//	void	** _vtbl;	// 00

	// older versions of this class stored flags in a UInt64
	// this forced the addition of 4 useless padding bytes
	// current and future versions store flags as two UInt32s

	enum {
		kState_Sprinting = 0x100,
		kState_Sneaking = 0x200,
		kState_Swimming = 0x400
	};

	UInt32	flags04;
	UInt32	flags08;
};

//STATIC_ASSERT(sizeof(ActorState) == 0x10);

// 19C
class Actor : public TESObjectREFR
{
public:
	enum { kTypeID = kFormType_Character };

	virtual ~Actor();

	// 0C
	struct SpellArray
	{
		UInt16		allocatedCount;	// 00
		UInt16		flags;			// Invalid objects appeared when this was anything other than zero
		SpellItem	** spells;		// 04
		UInt32		spellCount;		// 08
	};

	enum Flags1 {
		kFlags_IsPlayerTeammate = 0x4000000
	};
	enum Flags2 {
		kFlags_CanDoFavor = 0x80
	};

	MagicTarget		magicTarget;					// 054
	ActorValueOwner	actorValueOwner;				// 060
	ActorState		actorState;						// 064
	BSTEventSink<void*>	transformDeltaEvent;		// 070 .?AV?$BSTEventSink@VBSTransformDeltaEvent@@@@
	BSTEventSink<void*>	characterMoveFinishEvent;	// 074 .?AV?$BSTEventSink@VbhkCharacterMoveFinishEvent@@@@
	IPostAnimationChannelUpdateFunctor	unk078;		// 078 IPostAnimationChannelUpdateFunctor
	UInt32	flags1;									// 07C
	UInt32	unk080[(0x0FC - 0x080) >> 2];			// 080
	SpellArray	addedSpells;						// 0FC
	UInt32	unk108[(0x130 - 0x108) >> 2];			// 108
	TESRace			* race;							// 130
	UInt32	unk134;									// 134
	UInt32	flags2;									// 138
	UInt32	unk13C[(0x19C - 0x13C) >> 2];
};

STATIC_ASSERT(offsetof(Actor, magicTarget) == 0x54);
STATIC_ASSERT(offsetof(Actor, actorValueOwner) == 0x60);
STATIC_ASSERT(offsetof(Actor, actorState) == 0x64);
STATIC_ASSERT(offsetof(Actor, transformDeltaEvent) == 0x70);
STATIC_ASSERT(offsetof(Actor, addedSpells) == 0xFC);
STATIC_ASSERT(sizeof(Actor) == 0x19C);

// 19C
class Character : public Actor
{
public:
	enum { kTypeID = kFormType_Character };

	MEMBER_FN_PREFIX(Character);
	DEFINE_MEMBER_FN(QueueNiNodeUpdate, void, 0x00730EE0, bool);
};

STATIC_ASSERT(sizeof(Character) == 0x19C);

// 720
class PlayerCharacter : public Character
{
public:
	virtual ~PlayerCharacter();

	// parents
	BSTEventSink <void *>	menuOpenCloseEvent;			// 19C .?AV?$BSTEventSink@VMenuOpenCloseEvent@@@@
	BSTEventSink <void *>	menuModeChangeEvent;		// 1A0 .?AV?$BSTEventSink@VMenuModeChangeEvent@@@@
	BSTEventSink <void *>	userEventEnabledEvent;		// 1A4 .?AV?$BSTEventSink@VUserEventEnabledEvent@@@@
	BSTEventSource <void *>	actorCellEventSource;		// 1A8 .?AV?$BSTEventSource@UBGSActorCellEvent@@@@
	BSTEventSource <void *>	actorDeathEventSource;		// 1D8 .?AV?$BSTEventSource@UBGSActorDeathEvent@@@@
	BSTEventSource <void *>	positionPlayerEventSource;	// 208 .?AV?$BSTEventSource@UPositionPlayerEvent@@@@

	UInt32	pad238[(0x58C - 0x238) >> 2];	// 238
	NiNode	* firstPersonSkeleton;			// 58C
	UInt32	pad590[(0x5AC - 0x590) >> 2];
	UInt32	lastRiddenHorseHandle;			// 5AC
	UInt32	pad5B0[(0x614 - 0x5B0) >> 2];
	PlayerSkills *	skills;
	UInt32	pad618[(0x648 - 0x618) >> 2];
	UInt32	numTeammates;					// 648
	UInt32	pad64C[(0x6E0 - 0x64C) >> 2];
	UInt8	unk6E0;							// 6E0
	UInt8	numPerkPoints;					// 6E1
	UInt16  unk6E2;							// 6E2
	UInt32	unk6E4;							// 6E4

	tArray <TintMask *>	tintMasks;			// 6E8		// These are the actual tints
	tArray <TintMask *>	* overlayTintMasks;	// 6F4		// These apply when overlay head parts is enabled

	// Overlayed tints should be the same as original tints
	// occasionally they can have no type so index matching
	// is required to set anything on the tint
	TintMask * GetOverlayTintMask(TintMask * original);

	void UpdateSkinColor();
	void UpdateHairColor();

	// Confirmed - Same as ExtraContainerChanges::EntryData
	// This type is used by scaleform to extend data
	// It can be used to extend more of the "ExtraData"
	struct ObjDesc
	{
		TESForm					* form;
		tList<BaseExtraList>	* extraData;
		SInt32					countDelta;
	};

	MEMBER_FN_PREFIX(PlayerCharacter);
	DEFINE_MEMBER_FN(GetTintList, tArray <TintMask *> *, 0x0055FF90);
	DEFINE_MEMBER_FN(GetNumTints, UInt32, 0x00735F40, UInt32 tintType);
	DEFINE_MEMBER_FN(GetTintMask, TintMask *, 0x00735F00, UInt32 tintType, UInt32 index);
	DEFINE_MEMBER_FN(GetDamage, double, 0x00730810, ObjDesc * pForm);
	DEFINE_MEMBER_FN(GetArmorValue, double, 0x007307E0, ObjDesc * pForm);
};

STATIC_ASSERT(offsetof(PlayerCharacter, userEventEnabledEvent) == 0x1A4);
STATIC_ASSERT(offsetof(PlayerCharacter, numPerkPoints) == 0x6E1);
STATIC_ASSERT(offsetof(PlayerCharacter, tintMasks) == 0x6E8);
STATIC_ASSERT(offsetof(PlayerCharacter, overlayTintMasks) == 0x6F4);
STATIC_ASSERT(offsetof(PlayerCharacter, lastRiddenHorseHandle) == 0x5AC);
STATIC_ASSERT(offsetof(PlayerCharacter, skills) == 0x614);

// D8
class Explosion : public TESObjectREFR
{
	//
};

// 118
class ChainExplosion : public Explosion
{
	//
};

// 88
class Hazard : public TESObjectREFR
{
	enum { kTypeID = kFormType_Hazard };
};

// 140+
class Projectile : public TESObjectREFR
{
	//
};

// 150
class BarrierProjectile : public Projectile
{
	enum { kTypeID = kFormType_BarrierProj };
};

// 174
class BeamProjectile : public Projectile
{
	enum { kTypeID = kFormType_BeamProj };
};

// 16C
class ConeProjectile : public Projectile
{
	enum { kTypeID = kFormType_ConeProj };
};

// 148
class FlameProjectile : public Projectile
{
	enum { kTypeID = kFormType_FlameProj };
};

// 148
class GrenadeProjectile : public Projectile
{
	enum { kTypeID = kFormType_Grenade };
};

// 148
class MissileProjectile : public Projectile
{
	enum { kTypeID = kFormType_Missile };
};

// 150
class ArrowProjectile : public MissileProjectile
{
	enum { kTypeID = kFormType_Arrow };
};

// This does alot more, but no idea what it is yet
// ??
class CrosshairRefHandleHolder
{
	UInt32	unk00;					// 00
	UInt32	crosshairRefHandle;		// 04
	// ...

public:
	static CrosshairRefHandleHolder * GetSingleton(void)
	{
		return *((CrosshairRefHandleHolder **)0x01B115D8);
	}

	UInt32 CrosshairRefHandle(void) const		{ return crosshairRefHandle; }
};
