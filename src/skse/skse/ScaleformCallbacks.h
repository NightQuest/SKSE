#pragma once

#include "skse/ScaleformAPI.h"
#include "skse/ScaleformTypes.h"
#include "skse/Utilities.h"
#include <typeinfo>
#include <map>

// see RakNet/DependentExtensions/GFx3/FxGameDelegate.h

class FxDelegateHandler;
class GFxMovieView;
class GFxMovieRoot;

// the double in GFxValue is causing very weird alignment issues
#pragma pack (push, 4)

// 10
class GFxValue
{
public:
	GFxValue()
		:objectInterface(NULL), type(kType_Undefined) { }
	~GFxValue();

	enum
	{
		kType_Undefined =	0,
		kType_Null,
		kType_Bool,
		kType_Number,
		kType_String,
		kType_WideString,
		kType_Object,
		kType_Array,
		kType_DisplayObject,

		kTypeFlag_Managed =	1 << 6,

		kMask_Type =		0x8F,	// not sure why it checks the top bit
	};

	union Data
	{
		double	number;
		bool	boolean;
		char	* string;
		char	** managedString;
		wchar_t	* wideString;
		wchar_t	** managedWideString;
		void	* obj;
	};

	// 4
	class ObjectInterface
	{
	public:
		GFxMovieRoot	* root;

		MEMBER_FN_PREFIX(ObjectInterface);
		DEFINE_MEMBER_FN(HasMember, bool, 0x009067E0, void * obj, const char * name, bool isDisplayObj);
		DEFINE_MEMBER_FN(SetMember, bool, 0x009068B0, void * obj, const char * name, GFxValue * value, bool isDisplayObj);
		DEFINE_MEMBER_FN(GetMember, bool, 0x009094F0, void * obj, const char * name, GFxValue * value, bool isDisplayObj);
		DEFINE_MEMBER_FN(DeleteMember, bool, 0x00906970, void * obj, const char * name, bool isDisplayObj);
		DEFINE_MEMBER_FN(Invoke, bool, 0x00908A60, void * obj, GFxValue * result, const char * name, GFxValue * args, UInt32 numArgs, bool isDisplayObj);
	};

	ObjectInterface	* objectInterface;	// 00
	UInt32			type;				// 04
	Data			data;				// 08

	UInt32	GetType(void) const		{ return type & kMask_Type; }
	bool	IsManaged(void) const	{ return (type & kTypeFlag_Managed) != 0; }
	void	CleanManaged(void);
	bool	IsDisplayObject(void) const	{ return GetType() == kType_DisplayObject; }

	bool		GetBool(void);
	char *		GetString(void);
	wchar_t *	GetWideString(void);
	double		GetNumber(void);

	void	SetUndefined(void);
	void	SetNull(void);
	void	SetBool(bool value);
	void	SetNumber(double value);

	MEMBER_FN_PREFIX(GFxValue);
	DEFINE_MEMBER_FN(ReleaseManaged_Internal, void, 0x009081F0, ObjectInterface * objInterface, void * obj);

	bool	HasMember(const char * name);
	bool	SetMember(const char * name, GFxValue * value);
	bool	GetMember(const char * name, GFxValue * value);
	bool	DeleteMember(const char * name);
	bool	Invoke(const char * name, GFxValue * result, GFxValue * args, UInt32 numArgs);
};

STATIC_ASSERT(sizeof(GFxValue) == 0x10);

#pragma pack (pop, 4)

class GFxFunctionHandler : public GRefCountBase
{
public:
	GFxFunctionHandler();
	virtual ~GFxFunctionHandler();

	// 1C
	class Args
	{
	public:
		GFxValue		* result;	// 00
		GFxMovieView	* movie;	// 04
		GFxValue		* thisObj;	// 08
		GFxValue		* unk0C;	// 0C
		GFxValue		* args;		// 10
		UInt32			numArgs;	// 14
		void			* refCon;	// 18
	};

	virtual void	Invoke(Args * args) = 0;

	MEMBER_FN_PREFIX(GFxFunctionHandler);
	DEFINE_MEMBER_FN(Destroy, GFxFunctionHandler *, 0x00847AB0, UInt32 flags);
};

typedef std::map <const std::type_info *, GFxFunctionHandler *>	FunctionHandlerCache;
extern FunctionHandlerCache g_functionHandlerCache;

template <typename T>
void RegisterFunction(GFxValue * dst, GFxMovieView * movie, const char * name)
{
	// either allocate the object or retrieve an existing instance from the cache
	GFxFunctionHandler	* fn = NULL;

	// check the cache
	FunctionHandlerCache::iterator iter = g_functionHandlerCache.find(&typeid(T));
	if(iter != g_functionHandlerCache.end())
		fn = iter->second;

	if(!fn)
	{
		// not found, allocate a new one
		fn = new T;

		// add it to the cache
		// cache now owns the object as far as refcounting goes
		g_functionHandlerCache[&typeid(T)] = fn;
	}

	// create the function object
	GFxValue	fnValue;
	movie->CreateFunction(&fnValue, fn);

	// register it
	dst->SetMember(name, &fnValue);
}

// 04
class FxResponseArgsBase
{
public:
	FxResponseArgsBase();
	virtual ~FxResponseArgsBase();

	virtual UInt32	GetValues(GFxValue ** params);

//	void	** _vtbl;	// 00
};

// 0C + T_numArgs * 0x10
template <UInt32 T_numArgs>
class FxResponseArgs : public FxResponseArgsBase
{
public:
	FxResponseArgs();
	virtual ~FxResponseArgs();

	UInt32		align04;				// 04 - needed because GFxValue contains a double
	GFxValue	args[T_numArgs + 1];	// 08
	UInt32		curArg;					// 28 - offsets assume one argument
};

// ?
class FxResponseArgsList : public FxResponseArgsBase
{
public:
	FxResponseArgsList();

	GArray <GFxValue>	args;
};

// 20
class FxDelegateArgs
{
public:
	FxDelegateArgs();
	~FxDelegateArgs();

	GFxValue			responseID;
	FxDelegateHandler	* menu;		// 10
	GFxMovieView		* movie;	// 14
	GFxValue			* args;		// 18
	UInt32				numArgs;	// 1C
};

// 08
class FxDelegateHandler : public GRefCountBase
{
public:
	FxDelegateHandler();
	~FxDelegateHandler();

	typedef void (* Callback)(const FxDelegateArgs & params);

	class CallbackProcessor
	{
	public:
		CallbackProcessor();
		virtual ~CallbackProcessor();

		virtual void	Process(const GString & name, Callback method);
	};

	class AddCallbackVisitor : public CallbackProcessor
	{
	public:
		AddCallbackVisitor();
		virtual ~AddCallbackVisitor();

		FxDelegateHandler	* parent;
		void				* callbackHashTable;
	};

	virtual void	Add(CallbackProcessor * processor);
};
