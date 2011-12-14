#pragma once

#include "skse/ScaleformTypes.h"

class GFxState : public GRefCountBase
{
public:
	enum
	{
		kInterface_Unknown =		0x00,

		kInterface_Translator =		0x03,
		kInterface_ImageLoader =	0x05,
		kInterface_External =		0x09,
		kInterface_FileOpener =		0x0A,
		kInterface_ZlibSupport =	0x1E,
	};

	UInt32	interfaceType;	// 08
};
