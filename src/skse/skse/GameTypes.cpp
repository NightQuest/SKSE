#include "GameTypes.h"

StringCache * StringCache::GetSingleton(void)
{
	typedef StringCache * (* _GetSingleton)(void);

	return ((_GetSingleton)0x00BD9E30)();
}

StringCache::Lock * StringCache::GetLock(UInt32 crc16)
{
	return &locks[crc16 & 0x1F];
}

const char * BSString::Get(void)
{
	return m_data ? m_data : "";
}
