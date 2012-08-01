#include "PapyrusUI.h"
#include "ScaleformCallbacks.h"
#include "ScaleformMovie.h"
#include "GameMenus.h"
#include "Utilities.h"
#include "GameEvents.h"


namespace papyrusUI
{
	template <> void SetGFxValue<bool> (GFxValue * val, bool arg, GFxMovieView * view)						{ val->SetBool(arg); }
	template <> void SetGFxValue<float> (GFxValue * val, float arg, GFxMovieView * view)					{ val->SetNumber(arg); }
	template <> void SetGFxValue<BSFixedString> (GFxValue * val, BSFixedString arg, GFxMovieView * view)	{ view->CreateString(val, arg.data); }

	template <> bool GetGFxValue<bool> (GFxValue * val)						{ return (val->GetType() == GFxValue::kType_Bool ? val->GetBool() : false); }
	template <> float GetGFxValue<float> (GFxValue * val)					{ return (val->GetType() == GFxValue::kType_Number ? val->GetNumber() : 0); }
	template <> BSFixedString GetGFxValue<BSFixedString> (GFxValue * val)	{ return (val->GetType() == GFxValue::kType_String ? val->GetString() : NULL); }

	bool CreateObjectRoot(GFxMovieView * view, const char * dest)
	{
		std::string s;
		Tokenizer tokens(dest, ".");

		if (tokens.NextToken(s) == -1)
			return false;

		// Invalid root?
		if (s.compare("_global") != 0 && s.compare("_root") != 0)
			return false;

		std::string curDest(s);

		while(tokens.NextToken(s) != -1)
		{
			GFxValue root;
			view->GetVariable(&root, curDest.c_str());
			const char * name = s.c_str();

			if (! root.HasMember(name))
			{
				GFxValue obj;
				view->CreateObject(&obj);
				root.SetMember(name, &obj);
			}

			curDest.append(".");
			curDest.append(s);
		}

		return true;
	}

	bool ExtractTargetData(const char * target, std::string & dest, std::string & name)
	{
		// target format: [_global|_root].d.e.s.t.ValueName
		
		std::string t(target);
		UInt32 lastDelim = t.rfind('.');

		// Need at least 1 delim
		if (lastDelim == std::string::npos)
			return false;

		dest = t.substr(0, lastDelim);
		name = t.substr(lastDelim+1);

		return true;
	}

	bool PrepareSet(const char * target, GFxMovieView * view, GFxValue * fxDest, std::string & dest, std::string & name)
	{
		if (! ExtractTargetData(target, dest, name))
			return false;

		// If dest exists, done
		if (view->GetVariable(fxDest, dest.c_str()))
			return true;

		// Dest has to be created first
		if (!CreateObjectRoot(view, dest.c_str()))
			return false;

		// Try again now
		return view->GetVariable(fxDest, dest.c_str());
	}

	bool IsMenuOpen(StaticFunctionTag* thisInput, BSFixedString menuName)
	{
		if (!menuName.data)
			return 0;

		MenuManager * mm = MenuManager::GetSingleton();
		if (!mm)
			return false;

		return CALL_MEMBER_FN(mm, IsMenuOpen)(&menuName);
	}
};

#include "PapyrusVM.h"
#include "PapyrusNativeFunctions.h"

void papyrusUI::RegisterFuncs(VMClassRegistry* registry)
{
	registry->RegisterFunction(
		new NativeFunction3 <StaticFunctionTag, void, BSFixedString, BSFixedString, bool> ("SetBool", "UI", papyrusUI::SetT<bool>, registry));
	
	registry->RegisterFunction(
		new NativeFunction3 <StaticFunctionTag, void, BSFixedString, BSFixedString, float> ("SetNumber", "UI", papyrusUI::SetT<float>, registry));

	registry->RegisterFunction(
		new NativeFunction3 <StaticFunctionTag, void, BSFixedString, BSFixedString, BSFixedString> ("SetString", "UI", papyrusUI::SetT<BSFixedString>, registry));

	registry->RegisterFunction(
		new NativeFunction2 <StaticFunctionTag, bool, BSFixedString, BSFixedString> ("GetBool", "UI", papyrusUI::GetT<bool>, registry));

	registry->RegisterFunction(
		new NativeFunction2 <StaticFunctionTag, float, BSFixedString, BSFixedString> ("GetNumber", "UI", papyrusUI::GetT<float>, registry));

	registry->RegisterFunction(
		new NativeFunction2 <StaticFunctionTag, BSFixedString, BSFixedString, BSFixedString> ("GetString", "UI", papyrusUI::GetT<BSFixedString>, registry));

	registry->RegisterFunction(
		new NativeFunction3 <StaticFunctionTag, void, BSFixedString, BSFixedString, bool> ("InvokeBool", "UI", papyrusUI::InvokeArgT<bool>, registry));

	registry->RegisterFunction(
		new NativeFunction3 <StaticFunctionTag, void, BSFixedString, BSFixedString, float> ("InvokeNumber", "UI", papyrusUI::InvokeArgT<float>, registry));

	registry->RegisterFunction(
		new NativeFunction3 <StaticFunctionTag, void, BSFixedString, BSFixedString, BSFixedString> ("InvokeString", "UI", papyrusUI::InvokeArgT<BSFixedString>, registry));

	registry->RegisterFunction(
		new NativeFunction3 <StaticFunctionTag, void, BSFixedString, BSFixedString, VMArray<bool>> ("InvokeBoolA", "UI", papyrusUI::InvokeArrayT<bool>, registry));

	registry->RegisterFunction(
		new NativeFunction3 <StaticFunctionTag, void, BSFixedString, BSFixedString, VMArray<float>> ("InvokeNumberA", "UI", papyrusUI::InvokeArrayT<float>, registry));

	registry->RegisterFunction(
		new NativeFunction3 <StaticFunctionTag, void, BSFixedString, BSFixedString, VMArray<BSFixedString>> ("InvokeStringA", "UI", papyrusUI::InvokeArrayT<BSFixedString>, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, bool, BSFixedString> ("IsMenuOpen", "UI", papyrusUI::IsMenuOpen, registry));
}
