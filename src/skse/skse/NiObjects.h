#pragma once

#include "skse/NiRTTI.h"

// NiRefObject/NiObject and important children
// generally other children should go in other files
// especially if they can be grouped

class NiCloningProcess;
class NiStream;
class NiObjectGroup;

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

// ### not all of this is verified, I'm just assuming that little has changed from
// ### previous versions of NetImmerse that we have .pdb files for reference

// 08
class NiObject : public NiRefObject
{
public:
	// standard NetImmerse
	virtual NiRTTI *		GetRTTI(void);

	// then a bunch of empty functions (what)
	virtual UInt32			Unk_03(void);
	virtual UInt32			Unk_04(void);
	virtual UInt32			Unk_05(void);
	virtual UInt32			Unk_06(void);
	virtual UInt32			Unk_07(void);
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
