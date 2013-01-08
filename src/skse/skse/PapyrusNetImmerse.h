#pragma once

#include "GameTypes.h"

class VMClassRegistry;
struct StaticFunctionTag;
class TESObjectREFR;
class TESForm;
class BGSTextureSet;

namespace papyrusNetImmerse
{
	void RegisterFuncs(VMClassRegistry* registry);

	bool HasNode(StaticFunctionTag * base, TESObjectREFR * obj, BSFixedString nodeName);
	float GetNodePositionX(StaticFunctionTag * base, TESObjectREFR * obj, BSFixedString nodeName);
	float GetNodePositionY(StaticFunctionTag * base, TESObjectREFR * obj, BSFixedString nodeName);
	float GetNodePositionZ(StaticFunctionTag * base, TESObjectREFR * obj, BSFixedString nodeName);
	float GetNodeScale(StaticFunctionTag * base, TESObjectREFR * obj, BSFixedString nodeName);
	void SetNodeScale(StaticFunctionTag * base, TESObjectREFR * obj, BSFixedString nodeName, float value);
	void SetNodeTextureSet(StaticFunctionTag* base, TESObjectREFR * obj, BSFixedString nodeName, BGSTextureSet * textureSet);
}
