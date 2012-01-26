#pragma once

#include "Utilities.h"

// C
class Setting
{
public:
	Setting();
	virtual ~Setting();

	enum
	{
		kType_Unknown = 0,
		kType_Integer,
		kType_Float,
		kType_String,
		kType_Bool,
		kType_ID6,	// need to find an example of this
		kType_ID,
	};

	union Data
	{
		UInt32	u32;
		SInt32	s32;
		float	f32;
		UInt8	u8;		// used for bool
		char	* s;
	};

//	void	** _vtbl;	// 00
	Data	data;		// 04
	char	* name;		// 08

	UInt32	GetType(void) const;

	bool	GetDouble(double * out) const;
	bool	SetDouble(double value);
};

// 114
class GameSettingCollection
{
public:
	virtual ~GameSettingCollection();

	struct Entry
	{
		Setting	* setting;
		Entry	* next;
	};

//	void	** _vtbl;	// 000
	UInt32	pad004[(0x10C - 0x004) / 4];
	Entry	items;	// 10C

	MEMBER_FN_PREFIX(GameSettingCollection);
	DEFINE_MEMBER_FN(Get_Internal, bool, 0x00521510, const char * name, Setting ** out);

	Setting	* Get(const char * name);
};

extern GameSettingCollection	** g_iniSettingCollection;
extern GameSettingCollection	** g_iniPrefSettingCollection;

extern Setting	* g_gameLanguage;
