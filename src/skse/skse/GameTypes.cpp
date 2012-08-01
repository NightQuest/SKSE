#include "GameTypes.h"

void SimpleLock::Lock(void)
{
	SInt32 myThreadID = GetCurrentThreadId();
	if (threadID == myThreadID) {
		lockCount++;
		return;
	}

	UInt32 spinCount = 0;
	while (InterlockedCompareExchange(&threadID, myThreadID, 0))
		Sleep(++spinCount > kFastSpinThreshold);

    lockCount = 1;
}

void SimpleLock::Release(void)
{
	if (--lockCount == 0)
		InterlockedCompareExchange(&threadID, 0, threadID);
}

StringCache * StringCache::GetSingleton(void)
{
	typedef StringCache * (* _GetSingleton)(void);

	return ((_GetSingleton)0x00A47A40)();
}

StringCache::Lock * StringCache::GetLock(UInt32 crc16)
{
	return &locks[crc16 & 0x1F];
}

StringCache::Ref::Ref(const char * buf)
{
	CALL_MEMBER_FN(this, ctor)(buf);
}

const char * BSString::Get(void)
{
	return m_data ? m_data : "";
}

const _CRC32_Calc4 CRC32_Calc4 = (_CRC32_Calc4)0x00A41480;
const _CRC32_Calc8 CRC32_Calc8 = (_CRC32_Calc8)0x00A414E0;

template <> UInt32 GetHash<UInt32> (UInt32 * key)				{ UInt32 hash; CRC32_Calc4(&hash, *key); return hash; }
template <> UInt32 GetHash<UInt64> (UInt64 * key)				{ UInt32 hash; CRC32_Calc8(&hash, *key); return hash; }
template <> UInt32 GetHash<BSFixedString> (BSFixedString * key)	{ UInt32 hash; CRC32_Calc4(&hash, (UInt32)key->data); return hash; }
