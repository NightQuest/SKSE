#pragma once

#include "skse/NiObjects.h"

class NiRenderer : public NiObject
{
public:
	virtual ~NiRenderer();
};

class NiDX9Renderer : public NiRenderer
{
public:
	virtual ~NiDX9Renderer();

	UInt32		unk008[(0x02C-0x008) >> 2];	// 004
	UInt32      unk02C[(0x038-0x02C) >> 2]; // 02C
	void		* m_pkD3DDevice9;			// 038
	UInt32      unk03C[(0x390-0x03C) >> 2]; // 03C
	UInt32      m_uiBackground;				// 390
	UInt32      unk394[(0x880-0x394) >> 2]; // 394

	static NiDX9Renderer * GetSingleton();
};

STATIC_ASSERT(offsetof(NiDX9Renderer, m_pkD3DDevice9) == 0x38);

// Unknown class name, No RTTI
class NiRenderManager
{
public:
	static NiRenderManager * GetSingleton();

	MEMBER_FN_PREFIX(NiRenderManager); 
	DEFINE_MEMBER_FN(CreateRenderTarget, BSRenderTargetGroup *, 0x00C91800, NiDX9Renderer * dx9Renderer, UInt32 type, UInt32 unk1, UInt32 unk2);
};