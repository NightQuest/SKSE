#include "GameEvents.h"

// For testing
// TESActivateEvent																														0x0128C2F0
// TESActiveEffectApplyRemoveEvent																										0x0128C320
// TESActorLocationChangeEvent																											0x0128C350
// TESBookReadEvent																														0x0128C380
// TESCellAttachDetachEvent																												0x0128C3B0
// TESCellFullyLoadedEvent																												0x0128C3E0
// TESCombatEvent																														0x0128C440
// TESContainerChangedEvent																												0x0128C470
// TESDeathEvent																														0x0128C4A0
// TESDestructionStageChangedEvent																										0x0128C4D0
// TESEnterBleedoutEvent																												0x0128C500
// TESEquipEvent																														0x0128C530
// TESFormDeleteEvent																													0x0128C560
// TESFurnitureEvent																													0x0128C590
// TESGrabReleaseEvent																													0x0128C5C0
// TESHitEvent																															0x0128C5F0
// TESLoadGameEvent																														0x0128C650
// TESLockChangedEvent																													0x0128C680
// TESMagicEffectApplyEvent																												0x0128C6B0
// TESMagicWardHitEvent																													0x0128C6E0
// TESMoveAttachDetachEvent																												0x0128C710
// TESObjectLoadedEvent																													0x0128C740
// TESObjectREFRTranslationEvent																										0x0128C770
// TESOpenCloseEvent																													0x0128C7A0
// TESPackageEvent																														0x0128C7D0
// TESPerkEntryRunEvent																													0x0128C800
// TESQuestInitEvent																													0x0128C830
EventDispatcher<TESQuestStageEvent>* g_questStageEventDispatcher = (EventDispatcher<TESQuestStageEvent>*) 0x0128C860;
// TESResetEvent																														0x0128C8F0
// TESResolveNPCTemplatesEvent																											0x0128C920
// TESSceneEvent																														0x0128C950
// TESSceneActionEvent																													0x0128C980
// TESScenePhaseEvent																													0x0128C9B0
// TESSellEvent																															0x0128C9E0
//EventDispatcher<TESSleepStartEvent>* g_sleepStartEventDispatcher = (EventDispatcher<TESSleepStartEvent>*) 0x0128CA10;
// TESSleepStopEvent																													0x0128CA40
// TESSpellCastEvent																													0x0128CA70
// TESTopicInfoEvent																													0x0128CAD0
// TESTrackedStatsEvent																													0x0128CB00
// TESTrapHitEvent																														0x0128CB30
// TESTriggerEvent																														0x0128CB60
// TESTriggerEnterEvent																													0x0128CB90
// TESTriggerLeaveEvent																													0x0128CBC0
// TESUniqueIDChangeEvent																												0x0128CBF0
// TESSwitchRaceCompleteEvent																											0x0128CC80
// TESPlayerBowShotEvent																												0x0128CCA0

// Story based events
EventDispatcher<TESHarvestEvent::ItemHarvested>* g_harvestEventDispatcher = (EventDispatcher<TESHarvestEvent::ItemHarvested>*) 0x0128D104;
// Event	ActorKill																													0x01AE01F8
// Event	ActorItemEquipped																											0x01AE01C4
// Event	Pickpocket																													0x01AE1160
// Event	BooksRead																													0x0128E9CC
EventDispatcher<LevelIncrease::Event>* g_levelIncreaseEventDispatcher = (EventDispatcher<LevelIncrease::Event>*) 0x01AE0EB4;
// Event	SkillIncrease																												0x01AE0E80
// Event	WordLearned																													0x01AE139C
// Event	WordUnlocked																												0x01AE13D0
// Event	Inventory																													0x0128D628
// Event	Bounty																														0x01AE1298
// Event	QuestStatus																													0x01AB8A00
// Event	ObjectiveState																												0x01AB8640
// Event	Trespass																													0x01AE2918
// Event	FinePaid																													0x01AE11FC
// Event	HoursPassed																													0x01AE7424
// Event	DaysPassed																													0x01AD5DD8
// Event	DaysJailed																													0x01AE1368
// Event	CriticalHitEvent																											0x01AE0680
// Event	DisarmedEvent																												0x01AE022C
// Event	ItemsPickpocketed																											0x01AE5DEC
// Event	ItemSteal																													0x01AE1194
// Event	ItemCrafted																													0x01AE5E24
// Event	LocationDiscovery																											0x01AE11C8
// Event	Jailing																														0x01AE1230
// Event	ChestsLooted																												0x01AE5DB8
// Event	TimesTrained																												0x01AE776C
// Event	TimesBartered																												0x01AE5AB0
// Event	ContractedDisease																											0x01AE064C
// Event	SpellsLearned																												0x01AE070C
// Event	DragonSoulGained																											0x01AE05DC
// Event	SoulGemsUsed																												0x01AE7108
// Event	SoulsTrapped																												0x01AE06D8
// Event	PoisonedWeapon																												0x01AE1334
// Event	ShoutAttack																													0x01AE1300
// Event	JailEscape																													0x01AE1264
// Event	GrandTheftHorse																												0x01AE02FC
// Event	AssaultCrime																												0x01AE0294
// Event	MurderCrime																													0x01AE02C8
// Event	LocksPicked																													0x01AE71FC
// Event	LocationCleared																												0x0128EC70
// Event	ShoutMastered																												0x01AE1404
