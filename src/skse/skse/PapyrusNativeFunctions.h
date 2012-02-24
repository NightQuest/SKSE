#pragma once

#include "skse/GameTypes.h"
#include "skse/GameAPI.h"

// native function bindings for papyrus

// all of this is originally in namespace BSScript

class PapyrusClassRegistry;

// 08
class IFunction
{
public:
	IFunction()				{ }
	virtual ~IFunction()	{ }

//	void	** _vtbl;	// 00
	UInt32	refCount;	// 04 BSIntrusiveRefCounted

	virtual StringCache::Ref *	GetName(void) = 0;
	virtual StringCache::Ref *	GetClassName(void) = 0;
	virtual StringCache::Ref *	GetStr10(void) = 0;
	virtual void				GetUnk14(UInt32 * dst) = 0;
	virtual UInt32				GetNumParams(void) = 0;
	virtual void				Unk_06(UInt32 idx, UInt32 out1, UInt32 out2) = 0;	// param list stuff
	virtual UInt32				GetNumParams2(void) = 0;
	virtual bool				Unk_08(void) = 0;
	virtual UInt8				GetUnk20(void) = 0;
	virtual bool				Unk_0A(void) = 0;
	virtual UInt32				Unk_0B(void) = 0;
	virtual UInt32				GetUnk24(void) = 0;
	virtual StringCache::Ref *	GetStr28(void) = 0;
	virtual void				Unk_0E(UInt32 unk) = 0;
	virtual UInt32				Invoke(UInt32 unk0, UInt32 unk1, UInt32 unk2) = 0;
	virtual StringCache::Ref *	Unk_10(void) = 0;
	virtual bool				Unk_11(UInt32 unk0, UInt32 * unk1) = 0;
	virtual bool				Unk_12(UInt32 idx, UInt32 out) = 0;	// param list stuff
	virtual UInt8				GetUnk21(void) = 0;
	virtual void				SetUnk21(UInt8 arg) = 0;
	virtual bool				HasCallback(void) = 0;
	virtual bool				Run(UInt32 arg0, UInt32 arg1, UInt32 arg2, UInt32 arg3, UInt32 arg4) = 0;			// unique to each type combination
};

// BSScript::NF_util::NativeFunctionBase
// 2C
class NativeFunctionBase : public IFunction
{
public:
	NativeFunctionBase()			{ }
	virtual ~NativeFunctionBase()	{ }

	// 08
	struct ParameterInfo
	{
		enum
		{
			kType_String =	2,
			kType_Int =		3,
			kType_Float =	4,
			kType_Bool =	5,
		};

		// 08
		struct Entry
		{
			StringCache::Ref	name;	// 00
			UInt32				type;	// 04
		};

		Entry	* data;		// 00 length = numParams + unk06
		UInt16	numParams;	// 04
		UInt16	unk06;		// 06
	};

	virtual StringCache::Ref *	GetName(void)			{ return &m_fnName; }
	virtual StringCache::Ref *	GetClassName(void)		{ return &m_className; }
	virtual StringCache::Ref *	GetStr10(void)			{ return &unk10; }
	virtual void				GetUnk14(UInt32 * dst)	{ *dst = unk14; }
	virtual UInt32				GetNumParams(void)		{ return m_params.unk06; }
	virtual void				Unk_06(UInt32 idx, UInt32 out1, UInt32 out2)		// ### param list stuff
														{ CALL_MEMBER_FN(this, Impl_Fn06)(idx, out1, out2); }
	virtual UInt32				GetNumParams2(void)		{ return m_params.unk06; }
	virtual bool				Unk_08(void)			{ return true; }
	virtual UInt8				GetUnk20(void)			{ return unk20; }
	virtual bool				Unk_0A(void)			{ return true; }
	virtual UInt32				Unk_0B(void)			{ return 0; }
	virtual UInt32				GetUnk24(void)			{ return unk24; }
	virtual StringCache::Ref *	GetStr28(void)			{ return &unk28; }
	virtual void				Unk_0E(UInt32 unk)		{ }							// always nop?
	virtual UInt32				Invoke(UInt32 unk0, UInt32 unk1, UInt32 unk2)
														{ return CALL_MEMBER_FN(this, Impl_Invoke)(unk0, unk1, unk2); }
	virtual StringCache::Ref *	Unk_10(void)			{ return CALL_MEMBER_FN(this, Impl_Fn10)(); }
	virtual bool				Unk_11(UInt32 unk0, UInt32 * unk1)
														{ *unk1 = 0; return false; }
	virtual bool				Unk_12(UInt32 idx, UInt32 out)						// ### param list stuff
														{ return CALL_MEMBER_FN(this, Impl_Fn12)(idx, out); }
	virtual UInt8				GetUnk21(void)			{ return unk21; }
	virtual void				SetUnk21(UInt8 arg)		{ unk21 = arg; }
	virtual bool				HasCallback(void) = 0;
	virtual bool				Run(UInt32 arg0, UInt32 arg1, UInt32 arg2, UInt32 arg3, UInt32 arg4) = 0;

	MEMBER_FN_PREFIX(NativeFunctionBase);
	DEFINE_MEMBER_FN(Impl_dtor, void, 0x00C287E0);
	DEFINE_MEMBER_FN(Impl_Fn06, void, 0x00C28C60, UInt32 idx, UInt32 out1, UInt32 out2);
	DEFINE_MEMBER_FN(Impl_Invoke, UInt32, 0x00C289C0, UInt32 unk0, UInt32 unk1, UInt32 unk2);
	DEFINE_MEMBER_FN(Impl_Fn10, StringCache::Ref *, 0x00C28820);
	DEFINE_MEMBER_FN(Impl_Fn12, bool, 0x00C28C70, UInt32 idx, UInt32 out);

	// redirect to formheap
	static void * operator new(std::size_t size)
	{
		return FormHeap_Allocate(size);
	}

	static void * operator new(std::size_t size, const std::nothrow_t &)
	{
		return FormHeap_Allocate(size);
	}

	// placement new
	static void * operator new(std::size_t size, void * ptr)
	{
		return ptr;
	}

	static void operator delete(void * ptr)
	{
		FormHeap_Free(ptr);
	}

	static void operator delete(void * ptr, const std::nothrow_t &)
	{
		FormHeap_Free(ptr);
	}

	static void operator delete(void *, void *)
	{
		// placement delete
	}

protected:
	StringCache::Ref	m_fnName;		// 08
	StringCache::Ref	m_className;	// 0C
	StringCache::Ref	unk10;			// 10
	UInt32				unk14;			// 14 - return type
	ParameterInfo		m_params;		// 18
	UInt8				unk20;			// 20 - related to extra entries in m_params
	UInt8				unk21;			// 21
	UInt8				unk22;			// 22
	UInt8				pad23;			// 23
	UInt32				unk24;			// 24
	StringCache::Ref	unk28;			// 28
};

// 30
// this should be fully functional for deriving
class NativeFunction : public NativeFunctionBase
{
public:
	NativeFunction(const char * fnName, const char * className, UInt32 unk0, UInt32 unk1)
								{ CALL_MEMBER_FN(this, Impl_ctor)(fnName, className, unk0, unk1); }
	// lower class destructors are invoked by this call
	virtual ~NativeFunction()	{ CALL_MEMBER_FN(this, Impl_dtor)(); }

	virtual bool				HasCallback(void)	{ return m_callback != 0; }
	virtual bool				Run(UInt32 arg0, UInt32 arg1, UInt32 arg2, UInt32 arg3, UInt32 arg4) = 0;

	MEMBER_FN_PREFIX(NativeFunction);
	DEFINE_MEMBER_FN(Impl_ctor, NativeFunction *, 0x00C28910, const char * fnName, const char * className, UInt32 unk0, UInt32 numParams);
	DEFINE_MEMBER_FN(Impl_dtor, void, 0x00C287E0);

protected:
	void	* m_callback;	// 2C

	// hide
	NativeFunction()	{ }
};

// ### begin hack section
// ### IFunction::Run still needs to be fully understood
// ### until then we're limited to existing function types

class NativeFunction1_static_bool_float : public NativeFunction
{
public:
	typedef bool (__cdecl * Callback)(UInt32 unk0, UInt32 unk1, UInt32 unk2, float arg);

	NativeFunction1_static_bool_float(const char * fnName, const char * className, Callback callback, PapyrusClassRegistry ** registry)
		{ CALL_MEMBER_FN(this, Impl_ctor)(fnName, className, callback, registry); }

	virtual bool	Run(UInt32 arg0, UInt32 arg1, UInt32 arg2, UInt32 arg3, UInt32 arg4)
		{ return CALL_MEMBER_FN(this, Impl_Run)(arg0, arg1, arg2, arg3, arg4); }

	MEMBER_FN_PREFIX(NativeFunction1_static_bool_float);
	DEFINE_MEMBER_FN(Impl_ctor, NativeFunction1_static_bool_float *, 0x008FFFA0, const char * fnName, const char * className, Callback callback, PapyrusClassRegistry ** registry);
	DEFINE_MEMBER_FN(Impl_Run, bool, 0x009001E0, UInt32 arg0, UInt32 arg1, UInt32 arg2, UInt32 arg3, UInt32 arg4);
};
