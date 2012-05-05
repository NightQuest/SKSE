#pragma once

#include "skse/Utilities.h"
#include "skse/PapyrusVM.h"

class VMState;
class VMValue;
class VMClassRegistry;
struct StaticFunctionTag;

class VMArgList
{
public:
	VMArgList();
	~VMArgList();

	MEMBER_FN_PREFIX(VMArgList);
	DEFINE_MEMBER_FN(GetOffset, UInt32, 0x00C1FB60, VMState * state);
	DEFINE_MEMBER_FN(Get, VMValue *, 0x00C20170, VMState * state, UInt32 idx, UInt32 offset);
};

template <typename T>
void PackValue(VMValue * dst, T * src, VMClassRegistry * registry);

template <typename T>
void UnpackValue(T * dst, VMValue * src, VMClassRegistry * registry);

template <typename T>
UInt32 GetTypeID(VMClassRegistry * registry);

template <> void PackValue <void>(VMValue * dst, void * src, VMClassRegistry * registry);
template <> void PackValue <UInt32>(VMValue * dst, UInt32 * src, VMClassRegistry * registry);
template <> void PackValue <SInt32>(VMValue * dst, SInt32 * src, VMClassRegistry * registry);
template <> void PackValue <float>(VMValue * dst, float * src, VMClassRegistry * registry);
template <> void PackValue <bool>(VMValue * dst, bool * src, VMClassRegistry * registry);
template <> void PackValue <BSFixedString>(VMValue * dst, BSFixedString * src, VMClassRegistry * registry);

void PackHandle(VMValue * dst, void * src, UInt32 typeID, VMClassRegistry * registry);

template <typename T>
void PackValue(VMValue * dst, T ** src, VMClassRegistry * registry)
{
	typedef remove_pointer <T>::type	BaseType;
	PackHandle(dst, *src, BaseType::kTypeID, registry);
}

template <> void UnpackValue <float>(float * dst, VMValue * src, VMClassRegistry * registry);
template <> void UnpackValue <UInt32>(UInt32 * dst, VMValue * src, VMClassRegistry * registry);
template <> void UnpackValue <SInt32>(SInt32 * dst, VMValue * src, VMClassRegistry * registry);
template <> void UnpackValue <bool>(bool * dst, VMValue * src, VMClassRegistry * registry);
template <> void UnpackValue <BSFixedString>(BSFixedString * dst, VMValue * src, VMClassRegistry * registry);

void * UnpackHandle(VMValue * src, VMClassRegistry * registry, UInt32 typeID);

template <typename T>
void UnpackValue(T ** dst, VMValue * src, VMClassRegistry * registry)
{
	*dst = (T *)UnpackHandle(src, registry, T::kTypeID);
}

UInt32 GetTypeIDFromFormTypeID(UInt32 formTypeID, VMClassRegistry * registry);

template <> UInt32 GetTypeID <void>(VMClassRegistry * registry);
template <> UInt32 GetTypeID <UInt32>(VMClassRegistry * registry);
template <> UInt32 GetTypeID <SInt32>(VMClassRegistry * registry);
template <> UInt32 GetTypeID <int>(VMClassRegistry * registry);
template <> UInt32 GetTypeID <float>(VMClassRegistry * registry);
template <> UInt32 GetTypeID <bool>(VMClassRegistry * registry);
template <> UInt32 GetTypeID <BSFixedString>(VMClassRegistry * registry);

template <typename T>
UInt32 GetTypeID <T *>(VMClassRegistry * registry)
{
	UInt32		result;

	typedef remove_pointer <T>::type	BaseType;

	result = GetTypeIDFromFormTypeID(BaseType::kTypeID, registry);

	return result;
}

template <class T>
struct IsStaticType
{
	enum { value = 0 };
};

template <>
struct IsStaticType <StaticFunctionTag>
{
	enum { value = 1 };
};
