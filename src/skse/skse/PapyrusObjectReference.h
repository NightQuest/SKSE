#pragma once

class TESObjectREFR;
class TESForm;
class VMClassRegistry;

namespace papyrusObjectReference
{
	void RegisterFuncs(VMClassRegistry* registry);
	UInt32 GetNumItems(TESObjectREFR* pContainerRef);
	TESForm* GetNthForm(TESObjectREFR* pContainerRef, UInt32 n);
	float GetTotalItemWeight(TESObjectREFR* pContainerRef);
	float GetTotalArmorWeight(TESObjectREFR* pContainerRef);

	void SetItemHealthPercent(TESObjectREFR* object, float value);
	float GetItemCharge(TESObjectREFR* object);
	float GetItemMaxCharge(TESObjectREFR* object);
	void SetItemCharge(TESObjectREFR* object, float value);

	bool IsHarvested(TESObjectREFR* pProduceRef);
}
