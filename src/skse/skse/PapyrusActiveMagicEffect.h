#pragma once
 
class ActiveEffect;
class VMClassRegistry;
 
namespace papyrusActiveMagicEffect
{
	void RegisterFuncs(VMClassRegistry* registry);

	float GetTimeElapsed(ActiveEffect* effect);
	float GetDuration(ActiveEffect* effect);
}
