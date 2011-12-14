#include "Hooks_Gameplay.h"
#include "SafeWrite.h"
#include "Utilities.h"
#include "GameRTTI.h"

//// fix for resistance being totally broken in patch 1.2

// for whatever reason Bethesda decided to move resist calculation from MagicTarget -> Actor in 1.2
// this broke it
// fix moves it back, as it's still calling the old MagicTarget function
// 
// this is probably a hack, but it works

class Actor;

class ActorProxy
{
public:
	DEFINE_MEMBER_FN_LONG(ActorProxy, RealCalculateResist, float, 0x007F6FC0, UInt32 arg0, UInt32 arg1, UInt32 arg2);
};

class MagicTargetProxy
{
public:
	float	CalculateResist(UInt32 arg0, UInt32 arg1, UInt32 arg2)
	{
		float		result = 1;
		ActorProxy	* actor = (ActorProxy *)DYNAMIC_CAST(this, MagicTarget, Actor);

		if(actor)
		{
			result = CALL_MEMBER_FN(actor, RealCalculateResist)(arg0, arg1, arg1);

//			_MESSAGE("CalculateResist: hooked %f", result);
		}

		return result;
	}
};

// this is the solution to getting a pointer-to-member-function pointer
template <typename T>
UInt32 GetFnAddr(T src)
{
	union
	{
		UInt32	u32;
		T		t;
	} data;

	data.t = src;

	return data.u32;
}

void FixResistance(void)
{
	SafeWrite32(0x012A67EC, GetFnAddr(&MagicTargetProxy::CalculateResist));	// Actor
	SafeWrite32(0x012A9ABC, GetFnAddr(&MagicTargetProxy::CalculateResist));	// Character
	SafeWrite32(0x012AA2AC, GetFnAddr(&MagicTargetProxy::CalculateResist));	// PlayerCharacter
}

void Hooks_Gameplay_Install(void)
{
	FixResistance();
}
