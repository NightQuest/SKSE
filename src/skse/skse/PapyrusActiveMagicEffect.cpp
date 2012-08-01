#include "PapyrusActiveMagicEffect.h"
 
#include "GameForms.h"
#include "GameObjects.h"
#include "GameRTTI.h"
  
namespace papyrusActiveMagicEffect
{
	float GetTimeElapsed(ActiveEffect* effect)
	{
		return (effect) ? effect->elapsed : 0.0;
	}

	float GetDuration(ActiveEffect* effect)
	{
		return (effect) ? effect->duration : 0.0;
	}
}
 
#include "PapyrusVM.h"
#include "PapyrusNativeFunctions.h"
 
void papyrusActiveMagicEffect::RegisterFuncs(VMClassRegistry* registry)
{
	registry->RegisterFunction(
		new NativeFunction0 <ActiveEffect, float>("GetTimeElapsed", "ActiveMagicEffect", papyrusActiveMagicEffect::GetTimeElapsed, registry));

	registry->RegisterFunction(
		new NativeFunction0 <ActiveEffect, float>("GetDuration", "ActiveMagicEffect", papyrusActiveMagicEffect::GetDuration, registry));
}
