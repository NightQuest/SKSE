#pragma once

class TESForm;
class Actor;
class SpellItem;
class VMClassRegistry;

namespace papyrusActor
{
	void RegisterFuncs(VMClassRegistry* registry);

	TESForm* GetWornForm(Actor* thisActor, UInt32 slot);
	void QueueNiNodeUpdate(Actor* thisActor);
	UInt32 GetSpellCount(Actor* thisActor);
	SpellItem* GetNthSpell(Actor* thisActor, UInt32 n);
}
