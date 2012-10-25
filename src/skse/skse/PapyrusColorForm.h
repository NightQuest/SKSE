#pragma once
 
class BGSColorForm;
struct StaticFunctionTag;
class VMClassRegistry;

namespace papyrusColorComponent
{
	void RegisterFuncs(VMClassRegistry* registry);

	UInt32 GetRed(StaticFunctionTag* base, UInt32 argb);
	UInt32 GetGreen(StaticFunctionTag* base, UInt32 argb);
	UInt32 GetBlue(StaticFunctionTag* base, UInt32 argb);

	float GetHue(StaticFunctionTag* base, UInt32 argb);
	float GetSaturation(StaticFunctionTag* base, UInt32 argb);
	float GetLuminosity(StaticFunctionTag* base, UInt32 argb);

	UInt32 SetColor(StaticFunctionTag* base, UInt32 red, UInt32 green, UInt32 blue, UInt32 alpha);
	UInt32 SetRed(StaticFunctionTag* base, UInt32 argb, UInt32 red);
	UInt32 SetGreen(StaticFunctionTag* base, UInt32 argb, UInt32 green);
	UInt32 SetBlue(StaticFunctionTag* base, UInt32 argb, UInt32 blue);
	UInt32 SetHue(StaticFunctionTag* base, UInt32 argb, float hue);
	UInt32 SetSaturation(StaticFunctionTag* base, UInt32 argb, float sat);
	UInt32 SetLuminosity(StaticFunctionTag* base, UInt32 argb, float lum);
}
 
namespace papyrusColorForm
{
	void RegisterFuncs(VMClassRegistry* registry);

	UInt32 GetColor(BGSColorForm* colorForm);
}
