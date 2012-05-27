#pragma once
 
class BGSColorForm;
class VMClassRegistry;
 
namespace papyrusColorForm
{
	void RegisterFuncs(VMClassRegistry* registry);

	UInt32 GetRed(BGSColorForm* colorForm);
	UInt32 GetGreen(BGSColorForm* colorForm);
	UInt32 GetBlue(BGSColorForm* colorForm);
	UInt32 GetHue(BGSColorForm* colorForm);
	UInt32 GetSaturation(BGSColorForm* colorForm);
	UInt32 GetLuminosity(BGSColorForm* colorForm);
}
