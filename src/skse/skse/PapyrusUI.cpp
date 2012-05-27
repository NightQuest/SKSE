#include "PapyrusUI.h"

#include "PapyrusVM.h"
#include "PapyrusNativeFunctions.h"

#include "ScaleformCallbacks.h"
#include "ScaleformMovie.h"

#include "GameMenus.h"

#include "Utilities.h"

GFxMovieView * GetMovieView(const char * menuName)
{
	MenuManager * mm = MenuManager::GetSingleton();

	StringCache::Ref menuNameRef;
	CALL_MEMBER_FN(&menuNameRef, ctor)(menuName);

	GFxMovieView * view = mm->GetMovieView(&menuNameRef);

	CALL_MEMBER_FN(&menuNameRef, Release)();
	
	return view;
}

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
	UInt32 lastDelim = 0;
	std::string t(target);

	// Try to forward to last delim (if there even are any)
	for (UInt32 i=0; target[i]; i++)
		if (target[i] == '.')
			lastDelim = i;

	// Need at least 1 delim
	if (lastDelim == 0)
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

namespace papyrusUI
{
#if 0
	// Tested
	void SetBool(StaticFunctionTag* thisInput, BSFixedString menuName, BSFixedString targetStr, bool value)
	{
		if (!menuName.data || !targetStr.data)
			return;

		GFxMovieView * view = GetMovieView(menuName.data);
		if (!view)
			return;

		GFxValue fxDest;
		std::string valueDest, valueName;
		if (!PrepareSet(targetStr.data, view, &fxDest, valueDest, valueName))
			return;

		GFxValue fxValue;
		fxValue.SetBool(value);
		fxDest.SetMember(valueName.c_str(), &fxValue);
	}

	// Tested
	void SetNumber(StaticFunctionTag* thisInput, BSFixedString menuName, BSFixedString targetStr, float value)
	{
		if (!menuName.data || !targetStr.data)
			return;

		GFxMovieView * view = GetMovieView(menuName.data);
		if (!view)
			return;

		GFxValue fxDest;
		std::string valueDest, valueName;
		if (!PrepareSet(targetStr.data, view, &fxDest, valueDest, valueName))
			return;

		GFxValue fxValue;
		fxValue.SetNumber(value);
		fxDest.SetMember(valueName.c_str(), &fxValue);
	}

	// Tested
	void SetString(StaticFunctionTag* thisInput, BSFixedString menuName, BSFixedString targetStr, BSFixedString value)
	{
		if (!menuName.data || !targetStr.data)
			return;

		GFxMovieView * view = GetMovieView(menuName.data);
		if (!view)
			return;

		GFxValue fxDest;
		std::string dest, name;
		if (!PrepareSet(targetStr.data, view, &fxDest, dest, name))
			return;

		GFxValue fxValue;
		view->CreateString(&fxValue, value.data);
		fxDest.SetMember(name.c_str(), &fxValue);
	}
	
	// Tested
	bool GetBool(StaticFunctionTag* thisInput, BSFixedString menuName, BSFixedString sourceStr)
	{
		if (!menuName.data || !sourceStr.data)
			return false;

		GFxMovieView * view = GetMovieView(menuName.data);
		if (!view)
			return false;

		GFxValue fxResult;
		if (! view->GetVariable(&fxResult, sourceStr.data))
			return false;

		if (fxResult.GetType() != GFxValue::kType_Bool)
			return false;

		return fxResult.GetBool();
	}

	// Tested
	float GetNumber(StaticFunctionTag* thisInput, BSFixedString menuName, BSFixedString sourceStr)
	{
		if (!menuName.data || !sourceStr.data)
			return 0;

		GFxMovieView * view = GetMovieView(menuName.data);
		if (!view)
			return 0;

		GFxValue fxResult;
		if (! view->GetVariable(&fxResult, sourceStr.data))
			return 0;

		if (fxResult.GetType() != GFxValue::kType_Number)
			return 0;

		return fxResult.GetNumber();
	}

	// Tested
	BSFixedString GetString(StaticFunctionTag* thisInput, BSFixedString menuName, BSFixedString sourceStr)
	{
		if (!menuName.data || !sourceStr.data)
			return NULL;

		GFxMovieView * view = GetMovieView(menuName.data);
		if (!view)
			return NULL;

		GFxValue fxResult;
		if (! view->GetVariable(&fxResult, sourceStr.data))
			return NULL;

		if (fxResult.GetType() != GFxValue::kType_String)
			return NULL;

		return fxResult.GetString();
	}

	// Tested
	void Invoke(StaticFunctionTag* thisInput, BSFixedString menuName, BSFixedString targetStr)
	{
		if (!menuName.data || !targetStr.data)
			return;

		GFxMovieView * view = GetMovieView(menuName.data);
		if (!view)
			return;

		std::string dest, name;
		if (! ExtractTargetData(targetStr.data, dest, name))
			return;

		GFxValue fxDest;
		if (! view->GetVariable(&fxDest, dest.c_str()))
			return;

		fxDest.Invoke(name.c_str(), NULL, NULL, 0);
	}

	// Tested
	void InvokeBool(StaticFunctionTag* thisInput, BSFixedString menuName, BSFixedString targetStr, bool arg)
	{
		if (!menuName.data || !targetStr.data)
			return;

		GFxMovieView * view = GetMovieView(menuName.data);
		if (!view)
			return;

		std::string dest, name;
		if (! ExtractTargetData(targetStr.data, dest, name))
			return;

		GFxValue fxDest;
		if (! view->GetVariable(&fxDest, dest.c_str()))
			return;

		GFxValue args;
		args.SetBool(arg);
		fxDest.Invoke(name.c_str(), NULL, &args, 1);
		
	}

	// Tested
	void InvokeNumber(StaticFunctionTag* thisInput, BSFixedString menuName, BSFixedString targetStr, float arg)
	{
		if (!menuName.data || !targetStr.data)
			return;

		GFxMovieView * view = GetMovieView(menuName.data);
		if (!view)
			return;

		std::string dest, name;
		if (! ExtractTargetData(targetStr.data, dest, name))
			return;

		GFxValue fxDest;
		if (! view->GetVariable(&fxDest, dest.c_str()))
			return;

		GFxValue args;
		args.SetNumber(arg);
		fxDest.Invoke(name.c_str(), NULL, &args, 1);
	}

	// Tested
	void InvokeString(StaticFunctionTag* thisInput, BSFixedString menuName, BSFixedString targetStr, BSFixedString arg)
	{
		if (!menuName.data || !targetStr.data || !arg.data)
			return;

		GFxMovieView * view = GetMovieView(menuName.data);
		if (!view)
			return;

		std::string dest, name;
		if (! ExtractTargetData(targetStr.data, dest, name))
			return;

		GFxValue fxDest;
		if (! view->GetVariable(&fxDest, dest.c_str()))
			return;

		GFxValue args;
		view->CreateString(&args, arg.data);
		fxDest.Invoke(name.c_str(), NULL, &args, 1);
	}
#endif

	// Tested
	bool IsMenuOpen(StaticFunctionTag* thisInput, BSFixedString menuName)
	{
		if (! menuName.data)
			return false;

		MenuManager * mm = MenuManager::GetSingleton();
		StringCache::Ref menuNameRef;

		CALL_MEMBER_FN(&menuNameRef, ctor)(menuName.data);
		bool result = CALL_MEMBER_FN(mm, IsMenuOpen)(&menuNameRef);
		CALL_MEMBER_FN(&menuNameRef, Release)();

		return result;
	}

	void RegisterFuncs(VMClassRegistry* registry)
	{
#if 0
		registry->RegisterFunction(
			new NativeFunction3 <StaticFunctionTag, void, BSFixedString, BSFixedString, bool> ("SetBool", "UI", papyrusUI::SetBool, registry));
		
		registry->RegisterFunction(
			new NativeFunction3 <StaticFunctionTag, void, BSFixedString, BSFixedString, float> ("SetNumber", "UI", papyrusUI::SetNumber, registry));

		registry->RegisterFunction(
			new NativeFunction3 <StaticFunctionTag, void, BSFixedString, BSFixedString, BSFixedString> ("SetString", "UI", papyrusUI::SetString, registry));

		registry->RegisterFunction(
			new NativeFunction2 <StaticFunctionTag, bool, BSFixedString, BSFixedString> ("GetBool", "UI", papyrusUI::GetBool, registry));

		registry->RegisterFunction(
			new NativeFunction2 <StaticFunctionTag, float, BSFixedString, BSFixedString> ("GetNumber", "UI", papyrusUI::GetNumber, registry));

		registry->RegisterFunction(
			new NativeFunction2 <StaticFunctionTag, BSFixedString, BSFixedString, BSFixedString> ("GetString", "UI", papyrusUI::GetString, registry));

		registry->RegisterFunction(
			new NativeFunction2 <StaticFunctionTag, void, BSFixedString, BSFixedString> ("Invoke", "UI", papyrusUI::Invoke, registry));

		registry->RegisterFunction(
			new NativeFunction3 <StaticFunctionTag, void, BSFixedString, BSFixedString, bool> ("InvokeBool", "UI", papyrusUI::InvokeBool, registry));

		registry->RegisterFunction(
			new NativeFunction3 <StaticFunctionTag, void, BSFixedString, BSFixedString, float> ("InvokeNumber", "UI", papyrusUI::InvokeNumber, registry));

		registry->RegisterFunction(
			new NativeFunction3 <StaticFunctionTag, void, BSFixedString, BSFixedString, BSFixedString> ("InvokeString", "UI", papyrusUI::InvokeString, registry));
#endif
		registry->RegisterFunction(
			new NativeFunction1 <StaticFunctionTag, bool, BSFixedString> ("IsMenuOpen", "UI", papyrusUI::IsMenuOpen, registry));
	}
}
