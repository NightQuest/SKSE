#pragma once

class TESObjectREFR;
class TESForm;
class VMClassRegistry;

namespace papyrusContainer
{
	void RegisterFuncs(VMClassRegistry* registry);
	UInt32 GetNumItems(TESObjectREFR* pContainerRef);
	TESForm* GetNthForm(TESObjectREFR* pContainerRef, UInt32 n);
}