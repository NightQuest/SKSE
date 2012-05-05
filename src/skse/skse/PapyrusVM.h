#pragma once

#include "skse/Utilities.h"
#include "skse/GameTypes.h"

class IFunction;
class VMIdentifier;

class IObjectHandlePolicy
{
public:
	IObjectHandlePolicy();
	virtual ~IObjectHandlePolicy();

	// this code heavily uses 64-bit values, so many of these arguments may be paired 64-bit (eax/edx)
	virtual bool	IsType(UInt32 typeID, UInt64 handle);
	virtual bool	Unk_02(UInt64 handle);
	virtual UInt64	GetInvalidHandle(void);
	virtual UInt64	Create(UInt32 typeID, void * srcData);
	virtual bool	IsREFR(UInt64 handle);	// return IsType(TESObjectREFR::kTypeID, handle);
	virtual UInt64	Unk_06(UInt32 unk0, UInt32 unk1);
	virtual UInt64	Unk_07(UInt32 unk0, UInt32 unk1);
	virtual void *	Resolve(UInt32 typeID, UInt64 handle);
	virtual void	AddRef(UInt64 handle);
	virtual void	Release(UInt64 handle);
	virtual void	GetName(UInt64 handle, void * outStr);

//	void	** _vtbl;	// 00
};

extern IObjectHandlePolicy	** g_objectHandlePolicy;

class ObjectBindPolicy
{
public:
	ObjectBindPolicy();
	virtual ~ObjectBindPolicy();

	virtual void	Unk_01(UInt64 unk);
	virtual void	Unk_02(UInt64 unk);
	virtual void	Unk_03(UInt64 unk);
	virtual void	Unk_04(void);
	virtual UInt32	Unk_05(UInt32 unk0, UInt32 unk1);
	virtual void	Unk_06(UInt32 unk0, UInt32 unk1, UInt32 unk2, UInt32 unk3);
	virtual void	Unk_07(UInt32 unk0, UInt32 unk1, UInt32 unk2, UInt32 unk3, UInt32 unk4, UInt32 unk5);
	virtual bool	Unk_08(void);
	virtual void	Unk_09(UInt32 unk0, UInt32 unk1, UInt32 unk2, UInt32 unk3);
	virtual void	Unk_0A(UInt32 unk0, UInt32 unk1, UInt32 unk2, UInt32 unk3);
	virtual void	Unk_0B(UInt32 unk0, UInt32 unk1, UInt32 unk2, UInt32 unk3, UInt32 unk4);
	virtual void	Unk_0C(UInt32 unk0, UInt32 unk1, UInt32 unk2, UInt32 unk3, UInt32 unk4);

//	void	** _vtbl;	// 00

	MEMBER_FN_PREFIX(ObjectBindPolicy);
	DEFINE_MEMBER_FN(BindObject, void, 0x00C11410, VMIdentifier ** identifier, UInt64 handle);
};

// 10
class VMClassInfo
{
public:
	SInt32				refCount;
	StringCache::Ref	name;	// probably StringCache::Ref
	void				* unk08;
	void				* unk0C;

	void	AddRef(void);
	void	Release(void);

	MEMBER_FN_PREFIX(VMClassInfo);
	DEFINE_MEMBER_FN(Destroy, void, 0x00C1A640);
};

// 4B04
// this does more than hold on to class registrations, but for now that's all we care about
class VMClassRegistry
{
public:
	VMClassRegistry();
	virtual ~VMClassRegistry();

	virtual void	Unk_01(void);
	virtual void	Unk_02(void);
	virtual void	Unk_03(void);
	virtual void	Unk_04(void);
	virtual void	Unk_05(void);
	virtual void	Unk_06(void);
	virtual void	Unk_07(void);
	virtual void	RegisterForm(UInt32 typeID, const char * papyrusClassName);
	virtual void	Unk_09(void);
	virtual bool	GetFormClass(UInt32 formID, VMClassInfo ** outClass);
	virtual void	Unk_0B(void);
	virtual void	Unk_0C(void);
	virtual bool	Unk_0D(StringCache::Ref * className, UInt32 * unk);
	virtual void	Unk_0E(void);
	virtual void	Unk_0F(void);
	virtual void	Unk_10(void);
	virtual void	Unk_11(void);
	virtual void	Unk_12(void);
	virtual bool	Unk_13(StringCache::Ref * className, VMIdentifier ** identifier);
	virtual void	Unk_14(void);
	virtual void	Unk_15(void);
	virtual void	RegisterFunction(IFunction * fn);
	virtual void	SetFunctionFlagsEx(const char * className, UInt32 unk0, const char * fnName, UInt32 flags);
	virtual void	SetFunctionFlags(const char * className, const char * fnName, UInt32 flags);
	virtual void	Unk_19(void);
	virtual bool	Unk_1A(UInt64 handle, const char * clasName, VMIdentifier ** identifier);
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
	virtual IObjectHandlePolicy *	GetHandlePolicy(void);
	virtual void	Unk_2C(void);
	virtual ObjectBindPolicy *		GetObjectBindPolicy(void);
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

	VMClassRegistry	* m_classRegistry;	// 00FC
};

// 1C?
class VMIdentifier
{
public:
	enum
	{
		kLockBit = 0x80000000,
		kFastSpinThreshold = 10000
	};

	SInt32			m_refCount;	// 00
	VMClassInfo		* m_type;	// 04
	void			* unk08;	// 08
	void			* unk0C;	// 0C
	volatile UInt64	m_handle;	// 10
	volatile SInt32	m_lock;		// 18

	UInt64	GetHandle(void);

	SInt32	Lock(void);
	void	Unlock(SInt32 oldLock);

	// lock and refcount?
	void	IncrementLock(void);
	SInt32	DecrementLock(void);

	void	Destroy(void);

	MEMBER_FN_PREFIX(VMIdentifier);
	DEFINE_MEMBER_FN(Destroy_Internal, void, 0x00C16740);
};

// 08
// possibly BSScriptVariable
class VMValue
{
public:
	VMValue()
		:type(kType_None) { data.u = 0; }
	~VMValue()
		{ CALL_MEMBER_FN(this, Destroy)(); }

	enum
	{
		kType_None =		0,
		kType_Identifier =	1,
		kType_String =		2,
		kType_Int =			3,
		kType_Float =		4,
		kType_Bool =		5,

		kType_Unk0B =		0x0B,
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
		SInt32			i;
		UInt32			u;
		float			f;
		bool			b;
		void			* p;
		ArrayData		* arr;
		VMIdentifier	* id;
	} data;			// 04

	MEMBER_FN_PREFIX(VMValue);
	DEFINE_MEMBER_FN(Set, void, 0x00C181E0, VMValue * src);
	DEFINE_MEMBER_FN(Destroy, void, 0x00C180E0);

	void	SetNone(void)
	{
		CALL_MEMBER_FN(this, Destroy)();

		type = kType_None;
		data.u = 0;
	}

	void	SetInt(SInt32 i)
	{
		CALL_MEMBER_FN(this, Destroy)();

		type = kType_Int;
		data.i = i;
	}

	void	SetFloat(float f)
	{
		CALL_MEMBER_FN(this, Destroy)();

		type = kType_Float;
		data.f = f;
	}

	void	SetBool(bool b)
	{
		CALL_MEMBER_FN(this, Destroy)();

		type = kType_Bool;
		data.b = b;
	}

	void	SetIdentifier(VMClassInfo * classInfo)
	{
		CALL_MEMBER_FN(this, Destroy)();

		type = (UInt32)classInfo;
		data.id = NULL;
	}

	void	SetIdentifier(VMIdentifier ** identifier)
	{
		if(GetUnmangledType() == kType_Identifier)
		{
			CALL_MEMBER_FN(this, Destroy)();

			if(*identifier)
				(*identifier)->IncrementLock();

			data.id = *identifier;
		}
	}

	// 00-0F are untouched
	// 10+ alternate between 0x01 and 0x0B
	UInt32	GetUnmangledType(void);

	bool	IsIdentifier(void)	{ return GetUnmangledType() == kType_Identifier; }
};

STATIC_ASSERT(sizeof(VMValue) == 0x08);
