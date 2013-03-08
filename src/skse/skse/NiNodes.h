#pragma once

#include "skse/NiTypes.h"
#include "skse/NiObjects.h"

// NiNode and children

// B8
class NiNode : public NiAVObject
{
public:
	virtual void	AttachChild(NiAVObject * obj, bool firstAvail);
	virtual void	DetachChild(NiAVObject * obj);
	virtual void	Unk_35(void);
	virtual void	Unk_36(void);
	virtual void	Unk_37(void);
	virtual void	Unk_38(void);
	virtual void	Unk_39(void);
	virtual void	Unk_3A(void);
	virtual void	UpdateUpwardPass(void);

	NiTArray <NiAVObject *>	m_children;	// A8
};

STATIC_ASSERT(sizeof(NiNode) == 0xB8);

class BSFaceGenNiNode : public NiNode
{
public:
	// Nothing yet
};

typedef UInt32 (* _UpdateModelSkin)(NiNode*, NiColorA**);
extern _UpdateModelSkin UpdateModelSkin;

typedef UInt32 (* _UpdateModelHair)(NiNode*, NiColorA**);
extern _UpdateModelHair UpdateModelHair;
