#include "Hooks_Diagnostics.h"
#include "SafeWrite.h"
#include "Utilities.h"
#include <vector>
#include <string>

// ???
struct MissingMasterHookData
{
	UInt32	unk000;	// 000
	UInt32	unk004;	// 004
	UInt32	unk008;	// 008
	UInt32	unk00C;	// 00C
	UInt32	unk010;	// 010
	UInt32	unk014;	// 014
	UInt32	unk018;	// 018
	UInt32	unk01C;	// 01C

	char	pluginName[260]; // 020
	// more ...

	const char* CheckMaster_Hook(UInt32 unk1);

	MEMBER_FN_PREFIX(MissingMasterHookData);
	DEFINE_MEMBER_FN(CheckMaster_Hooked, const char*, 0x004449E0, UInt32 unk1);
};

const char* MissingMasterHookData::CheckMaster_Hook(UInt32 unk1)
{
	const char* result = CALL_MEMBER_FN(this,CheckMaster_Hooked)(unk1);

	if (result)
	{
		char	buf[4096];
		sprintf_s(buf, sizeof(buf), "Unable to find masterfile:\n%s\n\nRequired by:\n%s", result, &pluginName);

		MessageBox(NULL, buf, "Error", MB_OK | MB_ICONEXCLAMATION);
	}

	return result;
}

static std::vector<std::string> s_missingFiles;
static std::string				s_loadWarningText;

// The hooked function contains a loop that detects missing plugins.
// This outer hook just clears the list of collected files.
struct CheckMissingFilesHelper
{
	bool CheckMissingFiles_Hook(UInt32 unk1);

	MEMBER_FN_PREFIX(CheckMissingFilesHelper);
	DEFINE_MEMBER_FN(CheckMissingFiles_Hooked, bool, 0x00678930, UInt32 unk1);
};

bool CheckMissingFilesHelper::CheckMissingFiles_Hook(UInt32 unk1)
{
	s_missingFiles.clear();
	return CALL_MEMBER_FN(this,CheckMissingFiles_Hooked)(unk1);
}

// The inner hook collects the filenames
typedef void (__cdecl * _PrintMissingFileWarning_Hooked)(const char* fmt, const char* name);
static const _PrintMissingFileWarning_Hooked PrintMissingFileWarning_Hooked = (_PrintMissingFileWarning_Hooked)0x00677230;

void __cdecl PrintMissingFileWarning_Hook(const char* fmt, const char* name)
{
	s_missingFiles.push_back(name);

	PrintMissingFileWarning_Hooked(fmt, name);
}

// The last hook appends the collected names to the load warning
typedef void (__cdecl * _ShowLoadWarning_Hooked)(const char* text, int unk1, char unk2, int unk3, int unk4, const char* buttonText);
static const _ShowLoadWarning_Hooked ShowLoadWarning_Hooked = (_ShowLoadWarning_Hooked)0x0087AC60;

void __cdecl ShowLoadWarning_Hook(const char* text, int unk1, char unk2, int unk3, int unk4, const char* buttonText)
{
	s_loadWarningText.clear();

	// The old default text
	s_loadWarningText += text;
	
	s_loadWarningText += "\n\nMissing files:\n";
	for (size_t i=0; i<s_missingFiles.size(); ++i)
	{
		s_loadWarningText += s_missingFiles[i];
		s_loadWarningText += "\n";

		// Limited height
		if (i >= 6)
		{
			s_loadWarningText += "(... more)";
			break;
		}
	}

	ShowLoadWarning_Hooked(s_loadWarningText.c_str(), unk1, unk2, unk3, unk4, buttonText);
}

void Hooks_Diagnostics_Commit(void)
{
	UInt32	enableDiagnostics = 0;
	if (GetConfigOption_UInt32("General", "EnableDiagnostics", &enableDiagnostics))
	{
		if (enableDiagnostics)
		{
			// Show us which master is missing before the game crashes on load
			WriteRelCall(0x0043CFE5, GetFnAddr(&MissingMasterHookData::CheckMaster_Hook));

			// Show us which files are missing when warning about content that is no longer present
			//   Clear collected names ...
			WriteRelCall(0x0067B7D5, GetFnAddr(&CheckMissingFilesHelper::CheckMissingFiles_Hook));
			//   ... collect names of missing files during load...
			WriteRelCall(0x00678A48, (UInt32) &PrintMissingFileWarning_Hook);
			//   ... and append them to the warning message text
			WriteRelCall(0x006822CF, (UInt32) &ShowLoadWarning_Hook);

		}
	}
}
