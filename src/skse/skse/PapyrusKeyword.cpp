#include "PapyrusKeyword.h"

#include "GameForms.h"
#include "GameObjects.h"
#include "GameData.h"

#include "PapyrusVM.h"
#include "PapyrusNativeFunctions.h"
#include <set>

extern UInt32 g_invalidateKeywordCache;

struct compKeyword
{
	bool operator()(BGSKeyword*rhs, BGSKeyword*lhs)
	{
		return strcmp(rhs->keyword.Get(), lhs->keyword.Get()) < 0;
	}
};

struct compFixedString
{
	bool operator()(BSFixedString rhs, BSFixedString lhs) const
	{
		return strcmp(rhs.data, lhs.data) < 0;
	}
};

namespace papyrusKeyword
{
	BGSKeyword* GetKeyword(StaticFunctionTag*, BSFixedString keyword)
	{
		typedef std::map<BSFixedString, BGSKeyword*,compFixedString> KeywordCache;
		static KeywordCache s_keywordCache;
		
		if(g_invalidateKeywordCache == 1) {
			s_keywordCache.clear();
		}

		if (s_keywordCache.empty()) {
			DataHandler* pDataHandler = DataHandler::GetSingleton();
			tArray<BGSKeyword*>& keywords = pDataHandler->keywords;
			for (UInt32 n = 0; n < 	keywords.count; n++) {
				BGSKeyword* pKeyword = NULL;
				keywords.GetNthItem(n, pKeyword);
				if (pKeyword) {
					BSFixedString key(pKeyword->keyword.Get());
					s_keywordCache.insert(KeywordCache::value_type(key, pKeyword));
				}
			}
		}

		BGSKeyword* pKeyword = s_keywordCache[keyword.data];
		return pKeyword;
	}


	BSFixedString GetString(BGSKeyword* thisKeyword)
	{
		return (thisKeyword) ? thisKeyword->keyword.Get() : NULL;
	}

	void RegisterFuncs(VMClassRegistry* registry)
	{
		registry->RegisterFunction(
			new NativeFunction0 <BGSKeyword, BSFixedString> ("GetString", "Keyword", papyrusKeyword::GetString, registry));

		registry->RegisterFunction(
			new NativeFunction1 <StaticFunctionTag, BGSKeyword*, BSFixedString> ("GetKeyword", "Keyword", papyrusKeyword::GetKeyword, registry));

	}
}