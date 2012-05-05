#pragma once

class TESObjectREFR;
class TESForm;
class VMClassRegistry;

namespace papyrusObjectReference
{
	void RegisterFuncs(VMClassRegistry* registry);
	UInt32 GetNumItems(TESObjectREFR* pContainerRef);
	TESForm* GetNthForm(TESObjectREFR* pContainerRef, UInt32 n);

	bool IsHarvested(TESObjectREFR* pProduceRef);
}