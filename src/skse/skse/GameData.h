#pragma once

#include "GameTypes.h"
#include "GameForms.h"
#include "GameObjects.h"
#include "GameReferences.h"

class BSFile;

struct FormRecordData
{
	UInt8		typeID;		// corresponds to kFormType_XXX
	UInt32		typeCode;	// i.e. 'GMST', 'FACT'
	UInt32		unk08;		// only seen zero
};

struct ChunkHeader
{
	UInt32	type : 4;	// i.e. 'XGRD', 'DATA'
	UInt16	size : 2;
};

struct ModInfo		// referred to by game as TESFile
{
	ModInfo();
	~ModInfo();

	// 18 info about currently loading form
	struct FormInfo
	{
		UInt32		recordType;			// 00 i.e. 'FACT', 'GMST'
		UInt32		unk04;				// 04 looks like size of entire record
		UInt32		formFlags;			// 08 copied to TESForm->flags
		UInt32		formID;				// 0C 
		UInt32		unk10;				// 10
		UInt16		unk14;				// 14 always initialized to 0F on SaveForm. 
		UInt16		unk16;
	};

	tList<UInt32>						unkList;			// 000
	UInt32 /*NiTPointerMap<TESFile*>*/	* pointerMap;		// 008
	UInt32								unk00C;				// 00C
	BSFile*								unkFile;			// 010
	UInt32								unk014;				// 014 
	void								* unk018;			// 018 seen all zeroes. size unknown
	void								* unk01C;			// 01C as above
	char								name[0x104];		// 020
	char								filepath[0x104];	// 124
	UInt32								unk228;				// 228
	UInt32								unk22C;				// init'd to dword_F469CC (0x2800) same val as BSFile+10?
	UInt32								unk230;				// 230
	UInt32								unk234;				// 234
	UInt32								unk238;				// 238
	UInt32								unk23C;				// 23C
	FormInfo							formInfo;			// 240
	ChunkHeader							subRecord;			// 258
	UInt32								unk260;				// 260
	UInt32								fileOffset;			// 264
	UInt32								dataOffset;			// 268 index into dataBuf
	UInt32								subrecordBytesRead;	// 26C generates error on Read if != expected length
	UInt32						unk268[(0x298-0x270) >> 2];	// 270
	UInt8								unk298;				// 298
	UInt8								bIsBigEndian;		// 299
	UInt8								unk29A;				// 29A
	UInt8								pad29B;
	WIN32_FIND_DATA						fileData;			// 29C
	float								unk3DC;				// 3DC init'd to 0.94
	UInt32								unk3E0;				// 3E0
	UInt32								flags;				// 3E4 init'd to 0x00000800. 4000 and 40000 do stuff
	UInt8								unk3E8;				// 3E8
	UInt8								pad3E9[3];
	UInt32								unk3EC;				// 3EC
	UInt32								unk3F0;				// 3F0
	UInt32								unk3F4;				// 3F4
	UInt32								unk3F8;				// 3F8
	UInt32								numRefMods;			// 3FC related to modindex; see 4472D0
																// formIDs in mod are as saved in GECK, must fix up at runtime
	ModInfo								** refModInfo;		// 400 used to look up modInfo based on fixed mod index, double-check
	UInt32								unk404;				// 404
	UInt32								unk408;				// 408
	UInt8								modIndex;			// 40C init to 0xFF
	UInt8								pad40D[3];
	BSString							author;				// 410
	BSString							description;		// 418
	void								* dataBuf;			// 420 
	UInt32								unk424;				// 424 looks like size of entire record
	UInt8								unk428;				// 428
	UInt8								pad429[3];
	
	bool IsLoaded() const { return true; }
};

struct ModList
{
	tList<ModInfo>		modInfoList;
	UInt32				loadedModCount;
	ModInfo*			loadedMods[0xFF];
};

class DataHandler
{
public:
	static DataHandler* GetSingleton();

	// loads of tArrays of object types, at least a good number in formType order
	UInt32						unk000;
	UInt32						unk004;
	UnkFormArray				unk008;
	UnkFormArray				unk014;
	UnkFormArray				unk020;
	UnkFormArray				unk02C;
	tArray<BGSKeyword*>			keywords;
	tArray<BGSLocationRefType*>	locRefTypes;
	tArray<BGSAction*>			actions;
	tArray<BGSTextureSet*>		textureSets;
	tArray<BGSMenuIcon*>			menuIcons;
	tArray<TESGlobal*>			globals;
	tArray<TESClass*>			classes;
	tArray<TESFaction*>			factions;
	tArray<BGSHeadPart*>			headParts;
	tArray<TESEyes*>				eyes;
	tArray<TESRace*>				races;
	tArray<TESSound*>			sounds;
	tArray<BGSAcousticSpace*>	acousticSpaces;
	UnkFormArray				unkSkills;
	tArray<EffectSetting*>		magicEffects;
	tArray<Script*>				scripts;
	tArray<TESLandTexture*>		landTextures;
	tArray<EnchantmentItem*>	enchantments;
	tArray<SpellItem*>			spellItems;
	tArray<ScrollItem*>			scrolls;
	tArray<TESObjectACTI*>		activators;
	tArray<BGSTalkingActivator*>	talkingActivators;
	tArray<TESObjectARMO*>		armors;
	tArray<TESObjectBOOK*>		books;
	tArray<TESObjectCONT*>		containers;
	tArray<TESObjectDOOR*>		doors;
	tArray<IngredientItem*>		ingredients;
	tArray<TESObjectLIGH*>		lights;
	tArray<TESObjectMISC*>		miscObjects;
	tArray<BGSApparatus*>		apparatuses;
	tArray<TESObjectSTAT*>		statics;
	tArray<BGSStaticCollection*>	staticCollections;
	tArray<BGSMovableStatic*>	movableStatics;
	tArray<TESGrass*>			grasses;
	tArray<TESObjectTREE*>		trees;
	tArray<TESFlora*>			flora;
	tArray<TESFurniture*>		furniture;
	tArray<TESObjectWEAP*>		weapons;
	tArray<TESAmmo*>				ammo;
	tArray<TESNPC*>				npcs;
	tArray<TESLevCharacter*>		levCharacters;
	tArray<TESKey*>				keys;
	tArray<AlchemyItem*>			potions;
	tArray<BGSIdleMarker*>		idleMarkers;
	tArray<BGSNote*>				notes;
	tArray<BGSConstructibleObject*> constructibles;
	tArray<BGSProjectile*>		projectiles;
	tArray<BGSHazard*>			bgsHazards;
	tArray<TESSoulGem*>			soulGems;
	tArray<TESLevItem*>			levItems;
	tArray<TESWeather*>			weather;
	tArray<TESClimate*>			climates;
	tArray<BGSShaderParticleGeometryData*>	shaderParticleGeometryData;
	tArray<BGSReferenceEffect*>	referenceEffects;
	tArray<TESRegion*>			regions;
	tArray<NavMeshInfoMap*>		navMeshInfoMaps;
	tArray<TESObjectCELL*>		cells;
	tArray<TESObjectREFR*>		refs;	// could be actors
	tArray<Character*>			characters;
	tArray<MissileProjectile*>	missleProjs;
	tArray<ArrowProjectile*>		arrowProjs;
	tArray<GrenadeProjectile*>	grenadeProjs;
	tArray<BeamProjectile*>		beamProjs;
	tArray<FlameProjectile*>		flameProjs;
	tArray<ConeProjectile*>		coneProjs;
	tArray<BarrierProjectile*>	barrierProjs;
	tArray<Hazard*>				hazards;
	tArray<TESWorldSpace*>		worldSpaces;
	tArray<TESObjectLAND*>		lands;
	tArray<NavMesh*>				navMeshes;
	UnkFormArray				unkTLOD;
	tArray<TESTopic*>			topics;
	tArray<TESTopicInfo*>		topicInfos;
	tArray<TESQuest*>			quests;
	tArray<TESIdleForm*>			idleForms;
	tArray<TESPackage*>			packages;
	tArray<TESCombatStyle*>		combatStyles;
	tArray<TESLoadScreen*>		loadScreens;
	tArray<TESLevSpell*>			levSpells;
	tArray<TESObjectANIO*>		anios;
	tArray<TESWaterForm*>		waterForms;
	tArray<TESEffectShader*>		effectShaders;
	UnkFormArray				unkTOFTs;
	tArray<BGSExplosion*>		explosions;
	tArray<BGSDebris*>			debris;
	tArray<TESImageSpace*>		imageSpaces;
	tArray<TESImageSpaceModifier*>	imageSpaceModifiers;
	tArray<BGSListForm*>			listForms;
	tArray<BGSPerk*>				perks;
	tArray<BGSBodyPartData*>		bodyPartData;
	tArray<BGSAddonNode*>		addonNodes;
	tArray<ActorValueInfo*>		actorValueInfos;
	tArray<BGSCameraShot*>		cameraShots;
	tArray<BGSCameraPath*>		cameraPaths;
	tArray<BGSVoiceType*>		voiceTypes;
	tArray<BGSMaterialType*>		materialTypes;
	tArray<BGSImpactData*>		impactData;
	tArray<BGSImpactDataSet*>	impactDataSets;
	tArray<TESObjectARMA*>		armorAddons;
	tArray<BGSEncounterZone*>	encounterZones;
	tArray<BGSLocation*>			locations;
	tArray<BGSMessage*>			messages;
	tArray<BGSRagdoll*>			ragdolls;
	UnkFormArray				unkDOBJs;
	tArray<BGSLightingTemplate*>	lightingTemplates;
	tArray<BGSMusicType*>		musicTypes;
	tArray<BGSFootstep*>			footsteps;
	tArray<BGSFootstepSet*>		footstepSets;
	tArray<BGSStoryManagerBranchNode*>	branchNodes;
	tArray<BGSStoryManagerQuestNode*>	questNodes;
	tArray<BGSStoryManagerEventNode*>	eventNodes;
	tArray<BGSDialogueBranch*>	dialogBranches;
	tArray<BGSMusicTrackFormWrapper*>	musicTrackFormWrappers;
	UnkFormArray				unkDLVWs;
	tArray<TESWordOfPower*>		wordOfPowers;
	tArray<TESShout*>			shouts;
	tArray<BGSEquipSlot*>			equipSlots;
	tArray<BGSRelationship*>		relationships;
	tArray<BGSScene*>			scenes;
	tArray<BGSAssociationType*>	associationTypes;
	tArray<BGSOutfit*>			outfits;
	tArray<BGSArtObject*>		artObjects;
	tArray<BGSMaterialObject*>	materialObjects;
	tArray<BGSMovementType*>		movementTypes;
	tArray<BGSSoundDescriptorForm*>	soundDescriptors;
	tArray<BGSDualCastData*>		dualCastData;
	tArray<BGSSoundCategory*>	soundCategories;
	tArray<BGSSoundOutput*>		soundOutputs;
	tArray<BGSCollisionLayer*>	collisonLayers;
	tArray<BGSColorForm*>		colors;
	tArray<BGSReverbParameters*>	reverbParams;
	UInt32 unks[0x0E]; // 03 Cell** 06 TESGlobal**
	ModList							modList;
	UInt32 moreunks[100];

	const ModInfo* LookupModByName(const char* modName);
	UInt8 GetModIndex(const char* modName);
};
