#include "PapyrusNetImmerse.h"

#include "GameAPI.h"
#include "GameForms.h"
#include "GameRTTI.h"
#include "GameReferences.h"
#include "GameObjects.h"

#include "NiNodes.h"
#include "NiGeometry.h"

// This class needs to be moved and renamed
class UnkNiClass {
public:
	MEMBER_FN_PREFIX(UnkNiClass);
	DEFINE_MEMBER_FN(SetNiGeometryTexture, UInt32, 0x006A4300, NiAVObject * geometry, BGSTextureSet * textureSet);

	static UnkNiClass *	GetSingleton(void)
	{
		return *((UnkNiClass **)0x01B375F8);
	}
};

namespace papyrusNetImmerse
{
	bool HasNode(StaticFunctionTag* base, TESObjectREFR * obj, BSFixedString nodeName, bool firstPerson)
	{
		if(!obj)
			return false;

		NiNode * node = obj->GetNiNode();
		PlayerCharacter * player = DYNAMIC_CAST(obj, TESObjectREFR, PlayerCharacter);
		if(player && player->loadedState)
			node = firstPerson ? player->firstPersonSkeleton : player->loadedState->node;

		if(!node)
			return 0.0;

		NiAVObject * object = node->GetObjectByName(&nodeName.data);
		return (object != NULL);
	}

	float GetNodePositionX(StaticFunctionTag* base, TESObjectREFR * obj, BSFixedString nodeName, bool firstPerson)
	{
		if(!obj)
			return 0.0;

		NiNode * node = obj->GetNiNode();
		PlayerCharacter * player = DYNAMIC_CAST(obj, TESObjectREFR, PlayerCharacter);
		if(player && player->loadedState)
			node = firstPerson ? player->firstPersonSkeleton : player->loadedState->node;

		if(!node)
			return 0.0;

		NiAVObject * object = node->GetObjectByName(&nodeName.data);
		if(!object)
			return 0.0;

		return object->m_worldTransform.pos.x;
	}

	float GetNodePositionY(StaticFunctionTag* base, TESObjectREFR * obj, BSFixedString nodeName, bool firstPerson)
	{
		if(!obj)
			return 0.0;

		NiNode * node = obj->GetNiNode();
		PlayerCharacter * player = DYNAMIC_CAST(obj, TESObjectREFR, PlayerCharacter);
		if(player && player->loadedState)
			node = firstPerson ? player->firstPersonSkeleton : player->loadedState->node;

		if(!node)
			return 0.0;

		NiAVObject * object = node->GetObjectByName(&nodeName.data);
		if(!object)
			return 0.0;

		return object->m_worldTransform.pos.y;
	}

	float GetNodePositionZ(StaticFunctionTag* base, TESObjectREFR * obj, BSFixedString nodeName, bool firstPerson)
	{
		if(!obj)
			return 0.0;

		NiNode * node = obj->GetNiNode();
		PlayerCharacter * player = DYNAMIC_CAST(obj, TESObjectREFR, PlayerCharacter);
		if(player && player->loadedState)
			node = firstPerson ? player->firstPersonSkeleton : player->loadedState->node;

		if(!node)
			return 0.0;

		NiAVObject * object = node->GetObjectByName(&nodeName.data);
		if(!object)
			return 0.0;

		return object->m_worldTransform.pos.z;
	}

	float GetNodeScale(StaticFunctionTag* base, TESObjectREFR * obj, BSFixedString nodeName, bool firstPerson)
	{
		if(!obj)
			return 0.0;

		NiNode * node = obj->GetNiNode();
		PlayerCharacter * player = DYNAMIC_CAST(obj, TESObjectREFR, PlayerCharacter);
		if(player && player->loadedState)
			node = firstPerson ? player->firstPersonSkeleton : player->loadedState->node;
	
		if(!node)
			return 0.0;

		NiAVObject * object = node->GetObjectByName(&nodeName.data);
		if(!object)
			return 0.0;

		return object->m_localTransform.scale;
	}

	void SetNodeScale(StaticFunctionTag* base, TESObjectREFR * obj, BSFixedString nodeName, float value, bool firstPerson)
	{
		if(obj) {
			NiNode * node = obj->GetNiNode();
			PlayerCharacter * player = DYNAMIC_CAST(obj, TESObjectREFR, PlayerCharacter);
			if(player && player->loadedState)
				node = firstPerson ? player->firstPersonSkeleton : player->loadedState->node;

			if(node) {
				NiAVObject * object = node->GetObjectByName(&nodeName.data);
				if(object) {
					object->m_localTransform.scale = value;
					NiAVObject::ControllerUpdateContext ctx;
					object->UpdateWorldData(&ctx);
				}
			}
		}
	}

	void SetNodeTextureSet(StaticFunctionTag* base, TESObjectREFR * obj, BSFixedString nodeName, BGSTextureSet * textureSet, bool firstPerson)
	{
		if(obj && textureSet) {
			NiNode * node = obj->GetNiNode();
			PlayerCharacter * player = DYNAMIC_CAST(obj, TESObjectREFR, PlayerCharacter);
			if(player && player->loadedState)
				node = firstPerson ? player->firstPersonSkeleton : player->loadedState->node;

			if(node) {
				NiAVObject * object = node->GetObjectByName(&nodeName.data);
				if(object) {
					NiGeometry * geometry = object->GetAsNiGeometry();
					if(geometry)
						CALL_MEMBER_FN(UnkNiClass::GetSingleton(), SetNiGeometryTexture)(geometry, textureSet);
				}
			}
		}
	}
};

#include "PapyrusVM.h"
#include "PapyrusNativeFunctions.h"

void papyrusNetImmerse::RegisterFuncs(VMClassRegistry* registry)
{
	// NiNode Manipulation
	registry->RegisterFunction(
		new NativeFunction3<StaticFunctionTag, bool, TESObjectREFR*, BSFixedString, bool>("HasNode", "NetImmerse", papyrusNetImmerse::HasNode, registry));

	registry->RegisterFunction(
		new NativeFunction3<StaticFunctionTag, float, TESObjectREFR*, BSFixedString, bool>("GetNodePositionX", "NetImmerse", papyrusNetImmerse::GetNodePositionX, registry));

	registry->RegisterFunction(
		new NativeFunction3<StaticFunctionTag, float, TESObjectREFR*, BSFixedString, bool>("GetNodePositionY", "NetImmerse", papyrusNetImmerse::GetNodePositionY, registry));

	registry->RegisterFunction(
		new NativeFunction3<StaticFunctionTag, float, TESObjectREFR*, BSFixedString, bool>("GetNodePositionZ", "NetImmerse", papyrusNetImmerse::GetNodePositionZ, registry));

	registry->RegisterFunction(
		new NativeFunction3<StaticFunctionTag, float, TESObjectREFR*, BSFixedString, bool>("GetNodeScale", "NetImmerse", papyrusNetImmerse::GetNodeScale, registry));

	registry->RegisterFunction(
		new NativeFunction4<StaticFunctionTag, void, TESObjectREFR*, BSFixedString, float, bool>("SetNodeScale", "NetImmerse", papyrusNetImmerse::SetNodeScale, registry));

	registry->RegisterFunction(
		new NativeFunction4<StaticFunctionTag, void, TESObjectREFR*, BSFixedString, BGSTextureSet*, bool>("SetNodeTextureSet", "NetImmerse", papyrusNetImmerse::SetNodeTextureSet, registry));

	registry->SetFunctionFlags("NetImmerse", "HasNode", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("NetImmerse", "GetNodePositionX", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("NetImmerse", "GetNodePositionY", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("NetImmerse", "GetNodePositionZ", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("NetImmerse", "GetNodeScale", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("NetImmerse", "SetNodeScale", VMClassRegistry::kFunctionFlag_NoWait);
}
