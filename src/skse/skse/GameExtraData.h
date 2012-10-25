#pragma once

#include "GameBSExtraData.h"
#include "GameReferences.h"
#include "GameAPI.h"

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
	~ExtraPersistentCell();

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

	struct EntryData
	{
		TESForm* type;
		ExtendDataList* extendDataList;
		SInt32 countDelta;
	};

	typedef tList<EntryData> EntryDataList;

	struct Data
	{
		EntryDataList*	objList;
		TESObjectREFR*	owner;
		float			totalWeight;
		float			armorWeight;
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
	~ExtraWorn();
};

class ExtraWornLeft : public BSExtraData
{
public:
	ExtraWornLeft();
	~ExtraWornLeft();
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
	~ExtraFollower();

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
	~ExtraOwnership();

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
 //	ExtraCannotWear
 //	ExtraPoison
 //	ExtraLastFinishedSequence
 //	ExtraSavedAnimation
 //	ExtraNorthRotation
 //	ExtraSpawnContainer
 //	ExtraFriendHits
 //	ExtraHeadingTarget
 //	ExtraRefractionProperty
 //	ExtraStartingWorldOrCell
 //	ExtraHotkey
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
	~ExtraFactionChanges();

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
 //	ExtraPrimitive
 //	ExtraOpenCloseActivateRef
 //	ExtraAnimNoteReceiver
 //	ExtraAmmo
 //	ExtraPatrolRefData
 //	ExtraPackageData
 //	ExtraOcclusionShape
 //	ExtraCollisionData
 //	ExtraSayTopicInfoOnceADay
struct ExtraEncounterZone : public BSExtraData
{
public:
	ExtraEncounterZone();
	~ExtraEncounterZone();

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
	~ExtraFollowerSwimBreadcrumbs();

	UInt32	unk08;
	float	unk0C; // Looks like a position?
	float	unk10;
	float	unk14;
};

class ExtraAliasInstanceArray : public BSExtraData
{
public:
	ExtraAliasInstanceArray();
	~ExtraAliasInstanceArray();

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
	~ExtraPromotedRef();

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
	~ExtraFlags();

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

