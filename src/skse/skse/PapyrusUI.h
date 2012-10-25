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

		GFxValue fxValue;
		SetGFxValue<T>(&fxValue, value, view);

		view->SetVariable(targetStr.data, &fxValue, 1);
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

		GFxValue args;
		SetGFxValue<T>(&args, arg, view);

		view->Invoke(targetStr.data, NULL, &args, 1);

		args.CleanManaged();
	}

	template <typename T>
	void InvokeArrayT(StaticFunctionTag* thisInput, BSFixedString menuName, BSFixedString targetStr, VMArray<T> args)
	{
		GFxValue fxArgsBuf[128];

		if (!menuName.data || !targetStr.data)
			return;

		MenuManager * mm = MenuManager::GetSingleton();
		if (!mm)
			return;

		GFxMovieView * view = mm->GetMovieView(&menuName);
		if (!view)
			return;

		UInt32 argCount = args.Length();
		for (UInt32 i=0; i<argCount; i++)
		{
			T arg;
			args.Get(&arg, i);
			SetGFxValue<T>(&fxArgsBuf[i], arg, view);
		}

		view->Invoke(targetStr.data, NULL, (GFxValue*) &fxArgsBuf, argCount);

		// Release
		for (UInt32 i=0; i<argCount; i++)
			fxArgsBuf[i].CleanManaged();
	}

	bool IsMenuOpen(StaticFunctionTag* thisInput, BSFixedString menuName);
}