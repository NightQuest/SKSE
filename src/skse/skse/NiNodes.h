#pragma once

#include "skse/NiTypes.h"
#include "skse/NiObjects.h"

class BSFaceGenAnimationData;

// B8
class NiNode : public NiAVObject
{
public:
	virtual void	AttachChild(NiAVObject * obj, bool firstAvail);
	virtual void	DetachChild(UInt32 unk1, NiAVObject * obj);
	virtual void	Unk_35(void);
	virtual void	RemoveChild(NiAVObject * obj);
	virtual void	Unk_37(void);
	virtual void	Unk_38(void);
	virtual void	Unk_39(void);
	virtual void	Unk_3A(void);
	virtual void	UpdateUpwardPass(void);

	NiTArray <NiAVObject *>	m_children;	// A8
};

STATIC_ASSERT(sizeof(NiNode) == 0xB8);

// EC
class BSFaceGenNiNode : public NiNode
{
public:
	UInt32	unkBC;
	UInt32	unkC0;
	UInt32	unkC4;
	float	unkC8;
	UInt32	unkCC;
	UInt32	unkD0;
	UInt32	unkD4;
	float	unkD8;
	BSFaceGenAnimationData	* animData;
	float	unkE0;
	UInt32	unkE4;
	UInt32	unkE8;
	UInt32	unkEC;

	enum {
		kAdjustType_Unk0 = 0,
		kAdjustType_Unk1 = 1,
		kAdjustType_Unk2 = 2,
		kAdjustType_Neck = 3,
	};

	MEMBER_FN_PREFIX(BSFaceGenNiNode);
	DEFINE_MEMBER_FN(AdjustHeadMorph, void, 0x005A8270, UInt32 unk04, UInt32 unk08, float delta);
};

STATIC_ASSERT(sizeof(BSFaceGenNiNode) == 0xEC);


class NiSwitchNode : public NiNode
{
public:
	// Nothing yet
};

typedef UInt32 (* _UpdateModelSkin)(NiNode*, NiColorA**);
extern _UpdateModelSkin UpdateModelSkin;

typedef UInt32 (* _UpdateModelHair)(NiNode*, NiColorA**);
extern _UpdateModelHair UpdateModelHair;

typedef UInt32 (* _UpdateModelFace)(NiNode*);
extern _UpdateModelFace UpdateModelFace;