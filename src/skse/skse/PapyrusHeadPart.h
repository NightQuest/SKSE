#pragma once
 
class BGSHeadPart;
class BGSListForm;
class VMClassRegistry;
 
namespace papyrusHeadPart
{
	void RegisterFuncs(VMClassRegistry* registry);

	UInt32 GetType(BGSHeadPart* thisPart);
	UInt32 GetNumExtraParts(BGSHeadPart* thisPart);
	BGSHeadPart* GetNthExtraPart(BGSHeadPart* thisPart, UInt32 n);
	bool HasExtraPart(BGSHeadPart* thisPart, BGSHeadPart* extraPart);
	UInt32 GetIndexOfExtraPart(BGSHeadPart* thisPart, BGSHeadPart* extraPart);
	BGSListForm* GetValidRaces(BGSHeadPart* thisPart);
	void SetValidRaces(BGSHeadPart* thisPart, BGSListForm* raceList);
};
