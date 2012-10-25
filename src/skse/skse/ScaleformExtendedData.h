#pragma once

class TESForm;
class ActiveEffect;
class GFxMovieView;
class GFxValue;
class BGSKeywordForm;

#include "GameReferences.h"

void RegisterNumber(GFxValue * dst, const char * name, double value);
void RegisterBool(GFxValue * dst, const char * name, bool value);
void RegisterString(GFxValue * dst, GFxMovieView * view, const char * name, const char * str);
void RegisterKeywords(GFxValue * pFxVal, GFxMovieView * view, BGSKeywordForm * keywordForm);

// Item Card Extensions
namespace scaleformExtend
{
	void CommonItemData(GFxValue* pFxVal, TESForm * pForm);
	void StandardItemData(GFxValue* pFxVal, TESForm * pForm);
	void MagicItemData(GFxValue * pFxVal, GFxMovieView * movieView, TESForm * pForm);
	void ActorData(GFxValue * pFxVal, GFxMovieView * movieView, TESForm * pForm);
	void FormListData(GFxValue * pFxVal, GFxMovieView * movieView, TESForm * pForm);
	void FormData(GFxValue * pFxVal, GFxMovieView * movieView, TESForm * pForm);
	void InventoryData(GFxValue * pFxVal, GFxMovieView * movieView, PlayerCharacter::ObjDesc * objDesc);
};