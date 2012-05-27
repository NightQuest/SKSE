#include "GameMenus.h"

GFxMovieView * MenuManager::GetMovieView(BSFixedString * menuName)
{
	Result result;
	UInt32	hash;

	CRC32_Calc4(&hash, (UInt32)menuName->data);

	CALL_MEMBER_FN(&list, GetMenu)(list.data, hash, menuName, &result);
	IMenu * menu = result.menu;

	if(!menu)
		return NULL;

	GFxMovieView * view = menu->view;
	menu->Release();

	return view;
}
