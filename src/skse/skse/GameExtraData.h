#pragma once

#include "GameBSExtraData.h"
#include "GameReferences.h"
#include "GameAPI.h"
#include "GameObjects.h"

	//ExtraHavok
 //	ExtraCell3D
 //	ExtraCellWaterType
 //	ExtraRegionList
 //	ExtraSeenData
 //	ExtraEditorID
 //	ExtraCellMusicType
 //	ExtraCellSkyRegion
 //	ExtraProcessMiddleLow
 //	ExtraDetachTime
class ExtraPersistentCell : public BSExtraData
{
public:
	ExtraPersistentCell();
	virtual ~ExtraPersistentCell();

	TESObjectCELL* cell;
};
 //	ExtraAction
 //	ExtraStartingPosition
 //	ExtraAnimGraphManager
 //	ExtraUsedMarkers
 //	ExtraDistantData
 //	ExtraRagDollData
class ExtraContainerChanges : public BSExtraData
{
public:
	ExtraContainerChanges();
	virtual ~ExtraContainerChanges();

	typedef tList<BaseExtraList> ExtendDataList;

	class EntryData
	{
	public:
		TESForm* type;
		ExtendDataList* extendDataList;
		SInt32 countDelta;

		static EntryData * Create(TESForm * item, UInt32 count);

		void Delete(void);

		void GetExtraWornBaseLists(BaseExtraList ** pWornBaseListOut, BaseExtraList ** pWornLeftBaseListOut) const;
	};

	typedef tList<EntryData> EntryDataList;

	class Data
	{
	public:
		EntryDataList*	objList;
		TESObjectREFR*	owner;
		float			totalWeight;
		float			armorWeight;

		EntryData * FindItemEntry(TESForm * item) const;

		// Allocate new entry data as a merge between base container data and extra data
		// Uses BaseExtraList*'s from original extra data and combined count
		EntryData * CreateEquipEntryData(TESForm * item);
	};

	Data * data;

	struct FoundEquipData {
		TESForm* pForm;
		BaseExtraList* pExtraData;
	};
	FoundEquipData FindEquipped(FormMatcher& matcher) const;
};
typedef ExtraContainerChanges::FoundEquipData EquipData;
 
 class ExtraWorn : public BSExtraData
{
public:
	ExtraWorn();
	virtual ~ExtraWorn();
};

class ExtraWornLeft : public BSExtraData
{
public:
	ExtraWornLeft();
	virtual ~ExtraWornLeft();
};
 //	ExtraPackageStartLocation
 //	ExtraPackage
 //	ExtraTresPassPackage
 //	ExtraRunOncePacks
 //	ExtraReferenceHandle
class ExtraFollower : public BSExtraData
{
public:
	ExtraFollower();
	virtual ~ExtraFollower();

	UInt32	unk08;		// 08
	UInt32	unk0C;		// 0C
	UInt32	followers;	// 10
};
 //	ExtraLevCreaModifier
 //	ExtraGhost
 //	ExtraOriginalReference
class ExtraOwnership : public BSExtraData
{
public:
	ExtraOwnership();
	virtual ~ExtraOwnership();

	TESForm* owner;
};
 //	ExtraGlobal
 //	ExtraRank
class ExtraCount : public BSExtraData
{
public:
	ExtraCount();
	virtual ~ExtraCount();

	UInt32 count;

	static ExtraCount* Create();
};
class ExtraHealth : public BSExtraData // Tempered
{
public:
	ExtraHealth();
	virtual ~ExtraHealth();

	enum { // Multiplier
		kHealthBase = 1
	};

	float health;

	static ExtraHealth* Create();
};
 //	ExtraTimeLeft
class ExtraCharge : public BSExtraData
{
public:
	ExtraCharge();
	virtual ~ExtraCharge();

	float charge;

	static ExtraCharge* Create();
};
 //	ExtraLight
 //	ExtraLock
 //	ExtraTeleport
 //	ExtraMapMarker
 //	ExtraLeveledCreature
 //	ExtraLeveledItem
 //	ExtraScale
 //	ExtraSeed
 //	ExtraMagicCaster
 //	ExtraPlayerCrimeList
 //	ExtraEnableStateParent
 //	ExtraEnableStateChildren
 //	ExtraItemDropper
 //	ExtraDroppedItemList
 //	ExtraRandomTeleportMarker
 //	ExtraSavedHavokData
class ExtraCannotWear : public BSExtraData
{
public:
	ExtraCannotWear();
	virtual ~ExtraCannotWear();

	UInt32	unk08;

	static ExtraCannotWear* Create();
};
 //	ExtraPoison
 //	ExtraLastFinishedSequence
 //	ExtraSavedAnimation
 //	ExtraNorthRotation
 //	ExtraSpawnContainer
 //	ExtraFriendHits
 //	ExtraHeadingTarget
 //	ExtraRefractionProperty
 //	ExtraStartingWorldOrCell
class ExtraHotkey : public BSExtraData
{
public:
	ExtraHotkey();
	virtual ~ExtraHotkey();

	SInt32	hotkey;	// 08 (1 to 8, -1 unbound)

	static ExtraHotkey* Create();
};
 //	ExtraEditiorRefMoveData
 //	ExtraInfoGeneralTopic
 //	ExtraHasNoRumors
 //	ExtraSound
 //	ExtraTerminalState
 //	ExtraLinkedRef
 //	ExtraLinkedRefChildren
 //	ExtraActivateRef
 //	ExtraActivateRefChildren
 //	ExtraCanTalkToPlayer
 //	ExtraObjectHealth
 //	ExtraCellImageSpace
 //	ExtraNavMeshPortal
 //	ExtraModelSwap
 //	ExtraRadius
struct ExtraFactionChanges : public BSExtraData
{
public:
	ExtraFactionChanges();
	virtual ~ExtraFactionChanges();

	struct FactionInfo
	{
		TESFaction* faction;
		UInt32 rank;
	};

	UInt32	unk08;
	tArray<FactionInfo> factions;
};
 //	ExtraDismemberedLimbs
 //	ExtraActorCause
 //	ExtraMultiBound
 //	ExtraMultiBoundData
 //	ExtraMultiBoundRef
 //	ExtraReflectedRefs
 //	ExtraReflectorRefs
 //	ExtraEmittanceSource
 //	ExtraRadioData
 //	ExtraCombatStyle
struct ExtraPrimitive : public BSExtraData
{
public:
	ExtraPrimitive();
	virtual ~ExtraPrimitive();

	BGSPrimitive	* primitive;
};
 //	ExtraOpenCloseActivateRef
 //	ExtraAnimNoteReceiver
 //	ExtraAmmo
 //	ExtraPatrolRefData
 //	ExtraPackageData
 //	ExtraOcclusionShape
struct ExtraCollisionData : public BSExtraData
{
public:
	ExtraCollisionData();
	virtual ~ExtraCollisionData();

	struct Data
	{
		UInt32	collisionLayer; // LayerId
	};

	Data	* data;
};
 //	ExtraSayTopicInfoOnceADay
struct ExtraEncounterZone : public BSExtraData
{
public:
	ExtraEncounterZone();
	virtual ~ExtraEncounterZone();

	BGSEncounterZone* encounterZone;
};
 //	ExtraSayTopicInfo
 //	ExtraOcclusionPlaneRefData
 //	ExtraPortalRefData
 //	ExtraPortal
 //	ExtraRoom
 //	ExtraHealthPerc
 //	ExtraRoomRefData
 //	ExtraGuardedRefData
 //	ExtraCreatureAwakeSound
 //	ExtraHorse
 //	ExtraIgnoredBySandbox
 //	ExtraCellAcousticSpace
 //	ExtraReservedMarkers
 //	ExtraWeaponIdleSound
 //	ExtraWaterLightRefs
 //	ExtraWeaponAttackSound
 //	ExtraActivateLoopSound
 //	ExtraPatrolRefInUseData
 //	ExtraAshPileRef
class ExtraFollowerSwimBreadcrumbs : public BSExtraData
{
public:
	ExtraFollowerSwimBreadcrumbs();
	virtual ~ExtraFollowerSwimBreadcrumbs();

	UInt32	unk08;
	float	unk0C; // Looks like a position?
	float	unk10;
	float	unk14;
};

class ExtraAliasInstanceArray : public BSExtraData
{
public:
	ExtraAliasInstanceArray();
	virtual ~ExtraAliasInstanceArray();

	struct AliasInfo
	{
		TESQuest		* quest;
		BGSBaseAlias	* alias;
		tArray<TESPackage*>	* packages;
	};

	tArray<AliasInfo*> aliases;
};

class ExtraLocation : public BSExtraData
{
public:
	ExtraLocation(); // Related to protected/essential
	~ExtraLocation();

	BGSLocation* location;
};
 //	ExtraLitWaterRefs
 //	ExtraLocationRefType
class ExtraPromotedRef : public BSExtraData
{
public:
	ExtraPromotedRef();
	virtual ~ExtraPromotedRef();

	tArray<TESForm*> unk08;
};
 //	ExtraOutfitItem
 //	ExtraLeveledItemBase
 //	ExtraLightData
 //	ExtraSceneData
 //	ExtraBadPosition
 //	ExtraHeadTrackingWeight
 //	ExtraFromAlias
 //	ExtraShouldWear
 //	ExtraFavorCost
 //	ExtraAttachedArrows3D
class ExtraTextDisplayData : public BSExtraData
{
public:
	ExtraTextDisplayData();
	virtual ~ExtraTextDisplayData();

	BSFixedString	name;
	BGSMessage		* message;
	TESQuest		* owner;
	UInt32			unk14;
	float			unk18;

	static ExtraTextDisplayData* Create();
};
 //	ExtraAlphaCutoff
class ExtraEnchantment : public BSExtraData
{
public:
	ExtraEnchantment();
	virtual ~ExtraEnchantment();

	EnchantmentItem*	enchant;
	UInt32				maxCharge;

	//static ExtraEnchantment* Create();
};

class ExtraSoul : public BSExtraData
{
public:
	ExtraSoul();
	virtual ~ExtraSoul();

	UInt32 count;

	static ExtraSoul* Create();
};
 //	ExtraForcedTarget
 //	ExtraUniqueID
 //	ExtraFlags
class ExtraFlags : public BSExtraData
{
	ExtraFlags();
	virtual ~ExtraFlags();

	UInt32 flags;
};
 //	ExtraRefrPath
 //	ExtraDecalGroup
 //	ExtraLockList
 //	ExtraForcedLandingMarker
 //	ExtraLargeRefOwnerCells
 //	ExtraCelLWaterEnvMap
 //	ExtraCellGrassData
 //	ExtraTeleportName
 //	ExtraInteraction
 //	ExtraWaterData
 //	ExtraWaterCurrentZoneData
 //	ExtraAttachRef
 //	ExtraAttachRefChildren
 //	ExtraGroupConstraint
 //	ExtraScriptedAnimDependence
 //	ExtraCachedScale
 //	ExtraRaceData
 //	ExtraGIDBuffer
 //	ExtraMissingRefIDs
