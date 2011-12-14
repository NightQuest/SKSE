#ifndef __SKSE_VERSION_H__
#define __SKSE_VERSION_H__

// these have to be macros so they can be used in the .rc
#define SKSE_VERSION_INTEGER		1
#define SKSE_VERSION_INTEGER_MINOR	1
#define SKSE_VERSION_INTEGER_BETA	0
#define SKSE_VERSION_VERSTRING		"0, 1, 1, 0"
#define SKSE_VERSION_PADDEDSTRING	"0001"

#define MAKE_SKYRIM_VERSION_EX(major, minor, build, sub)	(((major & 0xFF) << 24) | ((minor & 0xFF) << 16) | ((build & 0xFFF) << 4) | (sub & 0xF))
#define MAKE_SKYRIM_VERSION(major, minor, build)			MAKE_SKYRIM_VERSION_EX(major, minor, build, 0)

// assume the major version number is 1.x
#define RUNTIME_VERSION_1_1_21_0	MAKE_SKYRIM_VERSION(1, 21, 0)		// 0x01150000

#define PACKED_SKSE_VERSION		MAKE_SKYRIM_VERSION(SKSE_VERSION_INTEGER, SKSE_VERSION_INTEGER_MINOR, SKSE_VERSION_INTEGER_BETA)

#endif /* __SKSE_VERSION_H__ */
