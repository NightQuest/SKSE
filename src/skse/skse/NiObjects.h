#pragma once

#include "skse/NiRTTI.h"
#include "skse/NiTypes.h"
#include "skse/Utilities.h"

// NiRefObject/NiObject and important children
// generally other children should go in other files
// especially if they can be grouped

class NiCloningProcess;
class NiStream;
class NiObjectGroup;
class NiExtraData;
class NiTimeController;
class NiNode;
class NiGeometry;
class NiRenderedTexture;

// 08
class NiRefObject
{
public:
	NiRefObject();
	virtual ~NiRefObject();

	virtual void	DeleteThis(void);	// calls virtual dtor

//	void	** _vtbl;		// 00
	UInt32	m_uiRefCount;	// 04
};

// ### not all of this is verified, I'm just assuming that little has changed from other
// ### games using previous versions of NetImmerse that have released .pdb files for reference

// 08
class NiObject : public NiRefObject
{
public:
	// standard NetImmerse
	virtual NiRTTI *		GetRTTI(void);

	// then a bunch of attempts to avoid dynamic_cast?
	// unverified, do not use
	virtual NiNode *		GetAsNiNode(void);
	virtual UInt32			Unk_04(void);
	virtual UInt32			Unk_05(void);
	virtual UInt32			Unk_06(void);
	virtual NiGeometry *	GetAsNiGeometry(void); // This could also be NiTriBasedGeom or another sub class
	virtual UInt32			Unk_08(void);
	virtual UInt32			Unk_09(void);
	virtual UInt32			Unk_0A(void);
	virtual UInt32			Unk_0B(void);
	virtual UInt32			Unk_0C(void);
	virtual UInt32			Unk_0D(void);
	virtual UInt32			Unk_0E(void);
	virtual UInt32			Unk_0F(void);
	virtual UInt32			Unk_10(void);
	virtual UInt32			Unk_11(void);
	virtual UInt32			Unk_12(void);

	// then back to NetImmerse
	virtual NiObject *		CreateClone(NiCloningProcess cloner);

	virtual void			LoadBinary(NiStream * stream);
	virtual void			LinkObject(NiStream * stream);
	virtual bool			RegisterStreamables(NiStream * stream);
	virtual void			SaveBinary(NiStream * stream);
	virtual bool			IsEqual(NiObject * object);

	// viewer appears to be disabled sadly
	// why did you do that? it was really useful for figuring out class data
	// and it's not like it totally bloated up the executa... er never mind

	virtual void			ProcessClone(NiCloningProcess * cloner);
	virtual void			PostLinkObject(NiStream * stream);
	virtual bool			StreamCanSkip(void);
	virtual const NiRTTI *	GetStreamableRTTI(void) const;
	virtual UInt32			GetBlockAllocationSize(void) const;
	virtual NiObjectGroup *	GetGroup(void) const;
	virtual void			SetGroup(NiObjectGroup * group);

	// begin bethesda extensions? possibly just stuff we can't match up
	virtual UInt32			Unk_20(void);
};

STATIC_ASSERT(sizeof(NiObject) == 0x08);

// 18
class NiObjectNET : public NiObject
{
public:
	const char	* m_name;

	NiTimeController	* m_controller;	// 0C next pointer at +0x30

	NiExtraData	** m_extraData;			// 10 extra data
	UInt16		m_extraDataLen;			// 14 max valid entry
	UInt16		m_extraDataCapacity;	// 16 array len
};

STATIC_ASSERT(sizeof(NiObjectNET) == 0x18);

// A8
class NiAVObject : public NiObjectNET
{
public:
	enum
	{
		kFlag_SelectiveUpdate =				0x00000002,
		kFlag_UpdatePropertyControllers =	0x00000004,

		kFlag_SelectiveUpdateRigid =		0x00000010,

		kFlag_OverrideSelectiveTransforms =	0x00000080,
	};

	struct ControllerUpdateContext
	{
		enum
		{
			kDirty =	1 << 0,
		};

		float	delta;
		UInt8	flags;
	};

	virtual void	UpdateControllers(ControllerUpdateContext * ctx);	// calls controller vtbl+0x8C
	virtual void	UpdateNodeBound(ControllerUpdateContext * ctx);
	virtual void	ApplyTransform(NiMatrix33 * mtx, NiPoint3 * translate, bool postTransform);
	virtual void	Unk_24(UInt32 arg0);	// call Unk_24 on all children
	virtual void	Unk_25(UInt32 arg0);
	virtual void	Unk_26(UInt32 arg0);
	virtual NiAVObject *	GetObjectByName(const char ** name);	// BSFixedString? alternatively BSFixedString is a typedef of a netimmerse type
	virtual void	SetSelectiveUpdateFlags(bool * selectiveUpdate, bool selectiveUpdateTransforms, bool * rigid);
	virtual void	UpdateDownwardPass(ControllerUpdateContext * ctx, UInt32 unk1);
	virtual void	UpdateSelectedDownwardPass(ControllerUpdateContext * ctx, UInt32 unk1);
	virtual void	UpdateRigidDownwardPass(ControllerUpdateContext * ctx, UInt32 unk1);
	virtual void	UpdateWorldBound(void);
	virtual void	UpdateWorldData(ControllerUpdateContext * ctx);
	virtual void	UpdateNoControllers(ControllerUpdateContext * ctx);
	virtual void	UpdateDownwardPassTempParent(NiNode * parent, ControllerUpdateContext * ctx);
	virtual void	Unk_30(void);	// calls virtual function on parent
	virtual void	Unk_31(UInt32 arg0);
	virtual void	Unk_32(UInt32 arg0);

	NiNode		* m_parent;			// 18
	NiAVObject	* unk1C;			// 1C
	NiTransform	m_localTransform;	// 20
	NiTransform	m_worldTransform;	// 54
	float		unk88;				// 88
	float		unk8C;				// 8C
	float		unk90;				// 90
	float		unk94;				// 94
	UInt32		m_flags;			// 98 - bitfield
	float		unk9C;				// 9C
	UInt32		unkA0;				// A0
	UInt8		unkA4;				// A4
	UInt8		unkA5;				// A5 - bitfield

	MEMBER_FN_PREFIX(NiAVObject);
	DEFINE_MEMBER_FN(UpdateNode, void, 0x00AAF320, NiAVObject * node);
};

STATIC_ASSERT(sizeof(NiAVObject) == 0xA8);
