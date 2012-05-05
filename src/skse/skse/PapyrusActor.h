#pragma once

class TESForm;
class Actor;
class VMClassRegistry;

namespace papyrusActor
{
	void RegisterFuncs(VMClassRegistry* registry);

	TESForm* GetWornForm(Actor* thisActor, UInt32 slot);
}
