#include "Hooks_SaveLoad.h"
#include "SafeWrite.h"
#include "Utilities.h"
#include "Serialization.h"
#include "GlobalLocks.h"

class SaveLoadManager
{
public:
	MEMBER_FN_PREFIX(SaveLoadManager);
	DEFINE_MEMBER_FN(SaveGame_Internal, void, 0x00675F20, const char * fileName);
	DEFINE_MEMBER_FN(LoadGame_Internal, bool, 0x00678440, const char * fileName, bool unk0);

	void SaveGame_Hook(const char * saveName)
	{
#ifdef DEBUG
		_MESSAGE("Executing SaveLoadManager::SaveGame_Hook. saveName: %s", saveName);
#endif

		Serialization::SetSaveName(saveName);
		CALL_MEMBER_FN(this, SaveGame_Internal)(saveName);
		Serialization::SetSaveName(NULL);

#ifdef DEBUG
		_MESSAGE("Executed SaveLoadManager::SaveGame_Hook.");
#endif
	}

	bool LoadGame_Hook(const char * saveName, bool unk1)
	{
#ifdef DEBUG
		_MESSAGE("Executing SaveLoadManager::LoadGame_Hook. saveName: %s", saveName);
#endif

		g_loadGameLock.Enter();

		Serialization::SetSaveName(saveName);
		bool result = CALL_MEMBER_FN(this, LoadGame_Internal)(saveName, unk1);
		Serialization::SetSaveName(NULL);

		g_loadGameLock.Leave();

#ifdef DEBUG
		_MESSAGE("Executed SaveLoadManager::LoadGame_Hook.");
#endif

		return result;
	}
};

#if 0

// 008
class BSStorage
{
public:
	virtual	~BSStorage();

	virtual SInt32	Unk_01(void);						// pure
	virtual UInt32	Unk_02(void);						// pure
	virtual SInt32	Unk_03(UInt32 unk0, UInt32 unk1);	// pure
	virtual SInt32	Unk_04(UInt32 len, void * out);		// pure
	virtual UInt32	Unk_05(UInt32 unk0, UInt32 unk1);	// pure

//	void					** _vtbl;	// 000
	BSIntrusiveRefCounted	refCount;	// 004
	UInt32					unk008;		// 008
	void					* unk00C;	// 00C
	void					* unk010;	// 010
};


// vtbl 0107F8E4
class SaveStorageWrapper : public BSStorage
{
public:
	virtual	~SaveStorageWrapper();

	virtual SInt32	Unk_01(void);
	virtual UInt32	Unk_02(void);
	virtual SInt32	Unk_03(UInt32 unk0, UInt32 unk1);
	virtual SInt32	Unk_04(UInt32 len, void * out);
	virtual UInt32	Unk_05(UInt32 unk0, UInt32 unk1);
};

// vtbl 0107F8FC
class LoadStorageWrapper : public BSStorage
{
public:
	virtual	~LoadStorageWrapper();

	virtual SInt32	Unk_01(void);						// 04
	virtual UInt32	Unk_02(void);						// 08
	virtual SInt32	Unk_03(UInt32 unk0, UInt32 unk1);	// 0C
	virtual SInt32	Unk_04(UInt32 len, void * out);		// 10
	virtual UInt32	Unk_05(UInt32 unk0, UInt32 unk1);	// 14
};

class IHandleReaderWriter
{
};

class BaseHandleReaderWriter : public IHandleReaderWriter
{
};

// vtbl 0109D0F0
class SaveFileHandleReaderWriter : public BaseHandleReaderWriter
{
public:
	virtual	~SaveFileHandleReaderWriter();
	//	void					** _vtbl;	// 000

	virtual SInt32	Unk_01(void);	// 04
	virtual UInt8	Unk_02(void);	// 08
	virtual UInt8	Unk_03(BSStorage * storageWrapper, UInt64 * handleOut);	// 0C
	virtual UInt8	Unk_04(void);	// 10
	virtual UInt8	Unk_05(void);	// 14
};

#endif

void Hooks_SaveLoad_Commit(void)
{
	// Load & save
	WriteRelCall(0x0067E272, GetFnAddr(&SaveLoadManager::SaveGame_Hook));
	WriteRelCall(0x0067EC35, GetFnAddr(&SaveLoadManager::LoadGame_Hook));
}
