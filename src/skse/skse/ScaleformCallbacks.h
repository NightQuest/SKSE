#pragma once

#include "skse/ScaleformTypes.h"
#include "skse/Utilities.h"

// see RakNet/DependentExtensions/GFx3/FxGameDelegate.h

class FxDelegateHandler;
class GFxMovieView;
class GFxMovieRoot;

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

		kMask_Type =		0x3F,
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
		GFxMovieRoot	* root;

		MEMBER_FN_PREFIX(ObjectInterface);
		DEFINE_MEMBER_FN(HasMember, bool, 0x009AFEC0, const char * name);
		DEFINE_MEMBER_FN(GetMember, bool, 0x009970D0, const char * name, GFxValue * value);
		DEFINE_MEMBER_FN(SetMember, bool, 0x0099A770, const char * name, GFxValue * value);
		DEFINE_MEMBER_FN(DeleteMember, bool, 0x009AFEF0, const char * name);
		DEFINE_MEMBER_FN(Invoke, bool, 0x009A0A10, const char * name, GFxValue * result, GFxValue * args, UInt32 numArgs);
	};

	ObjectInterface	* objectInterface;	// 00
	UInt32			type;				// 04
	Data			data;				// 08

	UInt32	GetType(void) const		{ return type & kMask_Type; }
	bool	IsManaged(void) const	{ return (type & kTypeFlag_Managed) != 0; }

	char *		GetString(void);
	wchar_t *	GetWideString(void);

	MEMBER_FN_PREFIX(GFxValue);
	DEFINE_MEMBER_FN(ReleaseManaged, void, 0x0078F880);
};

STATIC_ASSERT(sizeof(GFxValue) == 0x10);

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

	// callbacks run from 00BF613C
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
