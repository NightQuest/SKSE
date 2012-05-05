#include "Hooks_Gameplay.h"
#include "SafeWrite.h"
#include "Utilities.h"

static UInt32 g_forceContainerCategorization = 0;
static const UInt32 kHook_ContainerMode_Base = 0x0083CDA0;
static const UInt32 kHook_ContainerMode_Categories = kHook_ContainerMode_Base + 0x4E;
static const UInt32 kHook_ContainerMode_NoCategories = kHook_ContainerMode_Base + 0x63;
static UInt32 ** g_containerMode = (UInt32 **)0x01393884;

static void __declspec(naked) Hook_ContainerMode(void)
{
	__asm
	{
		// check override
		cmp		g_forceContainerCategorization, 0
		jnz		useCategories

		// original code (modified because msvc doesn't like immediates)
		// setting g_containerMode to 3 all the time causes other problems, don't bother

		push	eax
		mov		eax, [g_containerMode]
		mov		eax, [eax]
		cmp		eax, 3
		pop		eax

		jz		useCategories

		jmp		[kHook_ContainerMode_NoCategories]

useCategories:
		jmp		[kHook_ContainerMode_Categories]
	}
}

void Hooks_Gameplay_EnableForceContainerCategorization(bool enable)
{
	g_forceContainerCategorization = enable ? 1 : 0;
}

void Hooks_Gameplay_Commit(void)
{
	// optionally force containers in to "npc" mode, showing categories
	WriteRelJump(kHook_ContainerMode_Base + 0x45, (UInt32)Hook_ContainerMode);

	// read config
	UInt32	enableContainerCategorization = 0;
	if(GetConfigOption_UInt32("Interface", "EnableContainerCategorization", &enableContainerCategorization))
	{
		if(enableContainerCategorization)
		{
			_MESSAGE(".ini enabled container categorization");
			g_forceContainerCategorization = 1;
		}
	}
}
