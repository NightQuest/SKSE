#pragma once

#include "GameMenus.h"
#include "ScaleformCallbacks.h"
#include "ScaleformMovie.h"

struct StaticFunctionTag;
class VMClassRegistry;
template <typename T> class VMArray;


namespace papyrusUI
{
	template <typename T> void SetGFxValue(GFxValue * val, T arg, GFxMovieView * view);
	template <> void SetGFxValue<bool> (GFxValue * val, bool arg, GFxMovieView * view);
	template <> void SetGFxValue<float> (GFxValue * val, float arg, GFxMovieView * view);
	template <> void SetGFxValue<BSFixedString> (GFxValue * val, BSFixedString arg, GFxMovieView * view);

	template <typename T> T GetGFxValue(GFxValue * val);
	template <> bool GetGFxValue<bool> (GFxValue * val);
	template <> float GetGFxValue<float> (GFxValue * val);
	template <> BSFixedString GetGFxValue<BSFixedString> (GFxValue * val);

	void RegisterFuncs(VMClassRegistry* registry);

	bool CreateObjectRoot(GFxMovieView * view, const char * dest);
	bool ExtractTargetData(const char * target, std::string & dest, std::string & name);
	bool PrepareSet(const char * target, GFxMovieView * view, GFxValue * fxDest, std::string & dest, std::string & name);
	
	template <typename T>
	void SetT(StaticFunctionTag* thisInput, BSFixedString menuName, BSFixedString targetStr, T value)
	{
		if (!menuName.data || !targetStr.data)
			return;

		MenuManager * mm = MenuManager::GetSingleton();
		if (!mm)
			return;

		GFxMovieView * view = mm->GetMovieView(&menuName);
		if (!view)
			return;

		GFxValue fxDest;
		std::string valueDest, valueName;
		if (!PrepareSet(targetStr.data, view, &fxDest, valueDest, valueName))
			return;

		GFxValue fxValue;
		SetGFxValue<T>(&fxValue, value, view);
		fxDest.SetMember(valueName.c_str(), &fxValue);
	}

	template <typename T>
	T GetT(StaticFunctionTag* thisInput, BSFixedString menuName, BSFixedString sourceStr)
	{
		if (!menuName.data || !sourceStr.data)
			return 0;

		MenuManager * mm = MenuManager::GetSingleton();
		if (!mm)
			return 0;

		GFxMovieView * view = mm->GetMovieView(&menuName);
		if (!view)
			return 0;

		GFxValue fxResult;
		if (! view->GetVariable(&fxResult, sourceStr.data))
			return 0;

		return GetGFxValue<T>(&fxResult);
	}

	template <typename T>
	void InvokeArgT(StaticFunctionTag* thisInput, BSFixedString menuName, BSFixedString targetStr, T arg)
	{
		if (!menuName.data || !targetStr.data)
			return;

		MenuManager * mm = MenuManager::GetSingleton();
		if (!mm)
			return;

		GFxMovieView * view = mm->GetMovieView(&menuName);
		if (!view)
			return;

		std::string dest, name;
		if (! ExtractTargetData(targetStr.data, dest, name))
			return;

		GFxValue fxDest;
		if (! view->GetVariable(&fxDest, dest.c_str()))
			return;

		GFxValue args;
		SetGFxValue<T>(&args, arg, view);
		fxDest.Invoke(name.c_str(), NULL, &args, 1);		
	}

	template <typename T>
	void InvokeArrayT(StaticFunctionTag* thisInput, BSFixedString menuName, BSFixedString targetStr, VMArray<T> args)
	{
		// TODO: Is this ok?
		GFxValue fxArgsBuf[128];

		if (!menuName.data || !targetStr.data)
			return;

		MenuManager * mm = MenuManager::GetSingleton();
		if (!mm)
			return;

		GFxMovieView * view = mm->GetMovieView(&menuName);
		if (!view)
			return;

		std::string dest, name;
		if (! ExtractTargetData(targetStr.data, dest, name))
			return;

		GFxValue fxDest;
		if (! view->GetVariable(&fxDest, dest.c_str()))
			return;

		UInt32 argCount = args.Length();
		GFxValue * pArgs = NULL;
		if (argCount > 0)
		{
			pArgs = (GFxValue*) &fxArgsBuf;
			for (UInt32 i=0; i<argCount; i++, pArgs++)
			{
				pArgs->CleanManaged();
				T arg;
				args.Get(&arg, i);
				SetGFxValue<T>(pArgs, arg, view);
			}
		}
		
		fxDest.Invoke(name.c_str(), NULL, (GFxValue*) &fxArgsBuf, argCount);
	}

	bool IsMenuOpen(StaticFunctionTag* thisInput, BSFixedString menuName);
}