#pragma once

#include "skse/ScaleformCallbacks.h"

// 1C+
class IMenu : public FxDelegateHandler
{
public:
	IMenu();
	virtual ~IMenu();
	
	virtual void	InstallCallbacks(AddCallbackVisitor * visitor);	// called from 00BF59BD
	virtual void	Unk_02(void);
	virtual void	Unk_03(void);
	virtual UInt32	Unk_04(void * arg);
	virtual void	Unk_05(UInt32 arg0, UInt32 arg1);	// CurrentTime
	virtual void	Unk_06(void);

	UInt32			unk08;		// 08 - init'd to 0, a class, virtual fn 0x114 called in dtor
	UInt8			unk0C;		// 0C - init'd to 3
	UInt8			pad0D[3];	// 0D
	UInt32			unk10;		// 10 - init'd to 0
	UInt32			unk14;		// 14 - init'd to 0x12
	GRefCountBase	* unk18;	// 18 - holds a reference
};

// 34
class Console : public IMenu
{
public:
	// C+
	struct Unk20
	{
		struct Unk0
		{
			UInt32	unk0;
			UInt32	unk4;
		};

		struct Unk8
		{
			UInt32	unk0;
		};

		Unk0	unk0;	// 0
		Unk8	unk8;	// 8
	};

	void	* opcodeInfo;	// 1C - constructor checks that opcodes match
	Unk20	unk20;			// 20 - init'd to 0, probably history linked list?
	UInt32	unk2C;			// 2C - init'd to 0
	UInt8	unk30;			// 30 - init'd to 0

	// ### customization here
	DEFINE_MEMBER_FN_LONG(Console, InstallCallbacks_Orig, void, 0x0099CFB0, AddCallbackVisitor * visitor);

	void	InstallCallbacks_Hooked(AddCallbackVisitor * visitor);
	typedef void (Console::*InstallCallbacks_Ptr)(AddCallbackVisitor * visitor);
};

// 68
class BarterMenu : public IMenu
{
	GFxValue	* root;		// 1C
	// ...
	UInt8		unk34;		// 34
};
