#if NUM_PARAMS > 10
#error PapyrusNativeFunctionDef: too many params
#endif

template <typename T_Base

#if !VOID_SPEC
, typename T_Result
#endif

#if NUM_PARAMS >= 1
,typename T_Arg0
#endif
#if NUM_PARAMS >= 2
,typename T_Arg1
#endif
#if NUM_PARAMS >= 3
,typename T_Arg2
#endif
#if NUM_PARAMS >= 4
,typename T_Arg3
#endif
#if NUM_PARAMS >= 5
,typename T_Arg4
#endif
#if NUM_PARAMS >= 6
,typename T_Arg5
#endif
#if NUM_PARAMS >= 7
,typename T_Arg6
#endif
#if NUM_PARAMS >= 8
,typename T_Arg7
#endif
#if NUM_PARAMS >= 9
,typename T_Arg8
#endif
#if NUM_PARAMS >= 10
,typename T_Arg9
#endif

>

class CLASS_NAME
#if VOID_SPEC

	<T_Base, void

#if NUM_PARAMS >= 1
	, T_Arg0
#endif
#if NUM_PARAMS >= 2
	, T_Arg1
#endif
#if NUM_PARAMS >= 3
	, T_Arg2
#endif
#if NUM_PARAMS >= 4
	, T_Arg3
#endif
#if NUM_PARAMS >= 5
	, T_Arg4
#endif
#if NUM_PARAMS >= 6
	, T_Arg5
#endif
#if NUM_PARAMS >= 7
	, T_Arg6
#endif
#if NUM_PARAMS >= 8
	, T_Arg7
#endif
#if NUM_PARAMS >= 9
	, T_Arg8
#endif
#if NUM_PARAMS >= 10
	, T_Arg9
#endif

	>

#endif
	: public NativeFunction
{
public:
	typedef
#if VOID_SPEC
		void
#else
		T_Result
#endif
		(* CallbackType)(T_Base * base);

	CLASS_NAME(const char * fnName, const char * className, CallbackType callback)
		:NativeFunction(fnName, className, 0, NUM_PARAMS)
	{
		// store callback
		m_callback = (void *)callback;

		// ### set up argument list/result
	}

	virtual ~CLASS_NAME()	{ }

	virtual bool	Run(VMValue * baseValue, PapyrusClassRegistry * registry, UInt32 arg2, VMValue * resultValue, VMState * state)
	{
		// get argument list
		UInt32	argOffset = CALL_MEMBER_FN(state->argList, GetOffset)(state);

		// extract base object pointer
		T_Base	* base = NULL;
		UnpackValue(&base, baseValue, registry);

		// extract parameters
#if NUM_PARAMS >= 1
		T_Arg0	arg0;
		UnpackValue(&arg0, CALL_MEMBER_FN(state->argList, Get)(state, 0, argOffset), registry);
#endif
#if NUM_PARAMS >= 2
		T_Arg1	arg1;
		UnpackValue(&arg1, CALL_MEMBER_FN(state->argList, Get)(state, 1, argOffset), registry);
#endif
#if NUM_PARAMS >= 3
		T_Arg2	arg2;
		UnpackValue(&arg2, CALL_MEMBER_FN(state->argList, Get)(state, 2, argOffset), registry);
#endif
#if NUM_PARAMS >= 4
		T_Arg3	arg3;
		UnpackValue(&arg3, CALL_MEMBER_FN(state->argList, Get)(state, 3, argOffset), registry);
#endif
#if NUM_PARAMS >= 5
		T_Arg4	arg4;
		UnpackValue(&arg4, CALL_MEMBER_FN(state->argList, Get)(state, 4, argOffset), registry);
#endif
#if NUM_PARAMS >= 6
		T_Arg5	arg5;
		UnpackValue(&arg5, CALL_MEMBER_FN(state->argList, Get)(state, 5, argOffset), registry);
#endif
#if NUM_PARAMS >= 7
		T_Arg6	arg6;
		UnpackValue(&arg6, CALL_MEMBER_FN(state->argList, Get)(state, 6, argOffset), registry);
#endif
#if NUM_PARAMS >= 8
		T_Arg7	arg7;
		UnpackValue(&arg7, CALL_MEMBER_FN(state->argList, Get)(state, 7, argOffset), registry);
#endif
#if NUM_PARAMS >= 9
		T_Arg8	arg8;
		UnpackValue(&arg8, CALL_MEMBER_FN(state->argList, Get)(state, 8, argOffset), registry);
#endif
#if NUM_PARAMS >= 10
		T_Arg9	arg9;
		UnpackValue(&arg9, CALL_MEMBER_FN(state->argList, Get)(state, 9, argOffset), registry);
#endif

		// call the callback
#if !VOID_SPEC
		T_Result	result =
#endif
			((CallbackType)m_callback)(base

#if NUM_PARAMS >= 1
			, arg0
#endif
#if NUM_PARAMS >= 2
			, arg1
#endif
#if NUM_PARAMS >= 3
			, arg2
#endif
#if NUM_PARAMS >= 4
			, arg3
#endif
#if NUM_PARAMS >= 5
			, arg4
#endif
#if NUM_PARAMS >= 6
			, arg5
#endif
#if NUM_PARAMS >= 7
			, arg6
#endif
#if NUM_PARAMS >= 8
			, arg7
#endif
#if NUM_PARAMS >= 9
			, arg8
#endif
#if NUM_PARAMS >= 10
			, arg9
#endif

			);

		// pack the result
#if VOID_SPEC
		resultValue->SetNone();
#else
		PackValue(resultValue, &result);
#endif

		return true;
	}

private:
	// hide
	CLASS_NAME();
};

#undef VOID_SPEC
