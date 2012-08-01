#pragma once

class TESForm;
class Actor;
class SpellItem;
class ActiveEffect;
class VMClassRegistry;

namespace papyrusActor
{
	void RegisterFuncs(VMClassRegistry* registry);

	TESForm* GetWornForm(Actor* thisActor, UInt32 slot);
	void QueueNiNodeUpdate(Actor* thisActor);
	UInt32 GetSpellCount(Actor* thisActor);
	SpellItem* GetNthSpell(Actor* thisActor, UInt32 n);

#ifdef _AEFFECTS
	UInt32 GetNumActiveEffects(Actor* thisActor);
	ActiveEffect* GetNthActiveEffect(Actor* thisActor, UInt32 n);
#endif
}
