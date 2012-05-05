#pragma once

#include "GameBSExtraData.h"
#include "GameReferences.h"

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
 //	ExtraPersistentCell
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
};

 
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
 //	ExtraFollower
 //	ExtraLevCreaModifier
 //	ExtraGhost
 //	ExtraOriginalReference
 //	ExtraOwnership
 //	ExtraGlobal
 //	ExtraRank
class ExtraCount : public BSExtraData
{
public:
	ExtraCount();
	~ExtraCount();

	UInt32 count;
};
 //	ExtraHealth
 //	ExtraTimeLeft
 //	ExtraCharge
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
 //	ExtraFactionChanges
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
 //	ExtraEncounterZone
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
 //	ExtraFollowerSwimBreadcrumbs
 //	ExtraAliasInstanceArray
 //	ExtraLocation
 //	ExtraLitWaterRefs
 //	ExtraLocationRefType
 //	ExtraPromotedRef
 //	ExtraOutfitItem
 //	ExtraLeveledItemBase
 //	ExtraLightData
 //	ExtraSceneData
 //	ExtraBadPosition
 //	ExtraGeadTrackingWeight
 //	ExtraFromAlias
 //	ExtraShouldWear
 //	ExtraFavorCost
 //	ExtraAttachedArrows3D
 //	ExtraTextDisplayData
 //	ExtraAlphaCutoff
 //	ExtraEnchantment
 //	ExtraSoul
 //	ExtraForcedTarget
 //	ExtraUniqueID
 //	ExtraFlags
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

