#pragma once

class IFunction;

// 4B04
// this does more than hold on to class registrations, but for now that's all we care about
class PapyrusClassRegistry
{
public:
	PapyrusClassRegistry();
	virtual ~PapyrusClassRegistry();

	virtual void	Unk_01(void);
	virtual void	Unk_02(void);
	virtual void	Unk_03(void);
	virtual void	Unk_04(void);
	virtual void	Unk_05(void);
	virtual void	Unk_06(void);
	virtual void	Unk_07(void);
	virtual void	RegisterForm(UInt32 type, const char * name);
	virtual void	Unk_09(void);
	virtual void	Unk_0A(void);
	virtual void	Unk_0B(void);
	virtual void	Unk_0C(void);
	virtual void	Unk_0D(void);
	virtual void	Unk_0E(void);
	virtual void	Unk_0F(void);
	virtual void	Unk_10(void);
	virtual void	Unk_11(void);
	virtual void	Unk_12(void);
	virtual void	Unk_13(void);
	virtual void	Unk_14(void);
	virtual void	Unk_15(void);
	virtual void	RegisterFunction(IFunction * fn);
	virtual void	SetFunctionFlagsEx(const char * className, UInt32 unk0, const char * fnName, UInt32 flags);
	virtual void	SetFunctionFlags(const char * className, const char * fnName, UInt32 flags);
	virtual void	Unk_19(void);
	virtual void	Unk_1A(void);
	virtual void	Unk_1B(void);
	virtual void	Unk_1C(void);
	virtual void	Unk_1D(void);
	virtual void	Unk_1E(void);
	virtual void	Unk_1F(void);
	virtual void	Unk_20(void);
	virtual void	Unk_21(void);
	virtual void	Unk_22(void);
	virtual void	Unk_23(void);
	virtual void	Unk_24(void);
	virtual void	Unk_25(void);
	virtual void	Unk_26(void);
	virtual void	Unk_27(void);
	virtual void	Unk_28(void);
	virtual void	Unk_29(void);
	virtual void	Unk_2A(void);
	virtual void	Unk_2B(void);
	virtual void	Unk_2C(void);
	virtual void	Unk_2D(void);
	virtual void	Unk_2E(void);
	virtual void	Unk_2F(void);
	virtual void	Unk_30(void);
	virtual void	Unk_31(void);
	virtual void	Unk_32(void);
	virtual void	Unk_33(void);

//	void	** _vtbl;		// 0000
	UInt32	unk0004;		// 0004
	void	** vtbl0008;	// 0008
	void	** vtbl000C;	// 000C
	void	** vtbl0010;	// 0010
};

// 45D0
class SkyrimVM
{
public:
	SkyrimVM();
	virtual ~SkyrimVM();

	virtual void	Unk_01(void);

//	void	** _vtbl;	// 0000

	UInt32	pad0004[(0x00FC - 0x0004) >> 2];	// 0004

	PapyrusClassRegistry	* m_classRegistry;	// 00FC
};

// 08
// possibly BSScriptVariable
class VMValue
{
public:
	VMValue();
	~VMValue();

	enum
	{
		kType_Identifier =	1,
		kType_String =		2,
		kType_Int =			3,
		kType_Float =		4,
		kType_Bool =		5,

		kTypeFlag_Array =	1 << 0,
	};

	// 14+
	struct ArrayData
	{
		volatile SInt32	refCount;	// 00
		UInt32			unk04;		// 04
		UInt32			len;		// 08
		UInt32			unk0C;		// 0C
		UInt32			unk10;		// 10
//		VMValue			data[0];	// 14

		VMValue	*	GetData(void)	{ return (VMValue *)(this + 1); }
	};

	UInt32	type;	// 00

	union
	{
		SInt32		i;
		UInt32		u;
		float		f;
		bool		b;
		void		* p;
		ArrayData	* arr;
	} data;			// 04

	bool	UnkTypeCheck(void) const
	{
		return ((type >= 0x0B) && (type <= 0x0F));
	}

	bool	IsArray(void) const
	{
		if(UnkTypeCheck()) return true;
		if(type < 0x10) return false;
		return (type & kTypeFlag_Array) != 0;
	}
};

STATIC_ASSERT(sizeof(VMValue) == 0x08);
