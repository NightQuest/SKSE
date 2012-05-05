#pragma once

#include "skse/Utilities.h"

// core library types (lists, strings, vectors)
// preferably only the ones that bethesda created (non-netimmerse)

class BSIntrusiveRefCounted
{
public:
	volatile UInt32	m_refCount;	// 00
};

// 04
template <typename T>
class BSTSmartPointer
{
public:
	// refcounted
	T	* ptr;
};

class SimpleLock
{
private:
	volatile UInt32	threadID;
	UInt32			lockCount;
};

// refcounted threadsafe string storage
// use StringCache::Ref to access everything, other internals are for documentation only
class StringCache
{
public:
	// BSFixedString?
	struct Ref
	{
		const char	* data;

		MEMBER_FN_PREFIX(Ref);
		DEFINE_MEMBER_FN(ctor, Ref *, 0x00A38C90, const char * buf);
		DEFINE_MEMBER_FN(Set, Ref *, 0x00A38CE0, const char * buf);
		DEFINE_MEMBER_FN(Release, void, 0x00A38C80);

		Ref() :data(NULL) { }
		Ref(const char * buf);
	};

	struct Lock
	{
		SimpleLock	lock;
	};

	StringCache();
	~StringCache();

	static StringCache *	GetSingleton(void);

	Lock *	GetLock(UInt32 crc16);

private:
	struct Entry
	{
		Entry	* next;		// 00
		union
		{
			struct  
			{
				UInt16	refCount;	// invalid if 0x8000 is set
				UInt16	hash;
			};
			UInt32	refCountAndHash;
		} state;	// 04
		UInt32	length;		// 08
		// data follows
	};

	Entry	* table[0x10000];	// crc16
	Lock	locks[0x20];		// crc16 & 0x1F
	UInt8	unk;
};

typedef StringCache::Ref	BSFixedString;

// 08
class BSString
{
public:
	const char *	Get(void);

private:
	char	* m_data;	// 00
	UInt16	m_dataLen;	// 04
	UInt16	m_bufLen;	// 06
};

template <class T>
class tArray
{
public:
	struct Array {
		T* entries;
		UInt32 unk4;
	};

	Array arr;
	UInt32 count;
	
	bool GetNthItem(UInt32 index, T& pT)
	{
		if (index < count) {
			pT = arr.entries[index];
			return true;
		}
		return false;
	}

	UInt32 GetItemIndex(T pFind)
	{
		for (UInt32 n = 0; n < count; n++) {
			T& pT = arr.entries[n];
			if (pT == pFind)
				return n;
		}
		return -1;
	}
};

typedef tArray<UInt32> UnkArray;

enum {
	eListCount = -3,
	eListEnd = -2,
	eListInvalid = -1,		
};

template <class Item>
class tList
{
	typedef Item tItem;
	struct _Node {
		
		tItem*	item;
		_Node*	next;

		tItem* Item() const { return item; }
		_Node* Next() const { return next; }

		// become the next entry and return my item
		tItem* RemoveMe() {
			tItem* pRemoved = item;
			_Node* pNext = next;
			if (pNext) {
				item = pNext->item;
				next = pNext->next;
				FormHeap_Free(pNext);
			} else {
				item = NULL;
				next = NULL;
			}
			return pRemoved;
		}
	};

	_Node m_listHead;


private:

	template <class Op>
	UInt32 FreeNodes(_Node* node, Op &compareOp) const
	{
		static UInt32 nodeCount = 0;
		static UInt32 numFreed = 0;
		static _Node* lastNode = NULL;
		static bool bRemovedNext = false;

		if (node->Next())
		{
			nodeCount++;
			FreeNodes(node->Next(), compareOp);
			nodeCount--;
		}

		if (compareOp.Accept(node->Item()))
		{
			if (nodeCount)
				node->Delete();
			else
				node->DeleteHead(lastNode);
			numFreed++;
			bRemovedNext = true;
		}
		else
		{
			if (bRemovedNext)
				node->SetNext(lastNode);
			bRemovedNext = false;
			lastNode = node;
		}

		if (!nodeCount)	//reset vars after recursing back to head
		{
			numFreed = 0;
			lastNode = NULL;
			bRemovedNext = false;
		}

		return numFreed;
	}


	struct NodePos {
		NodePos(): node(NULL), index(eListInvalid) {}

		_Node*	node;
		SInt32	index;
	};


	NodePos GetNthNode(SInt32 index) const {
		NodePos pos;
		SInt32 n = 0;
		_Node* pCur = Head();

		while (pCur && pCur->Item()) {
			if (n == index) break;
			if (eListEnd == index && !pCur->Next()) break;
			pCur = pCur->Next();
			++n;
		}

		pos.node = pCur;
		pos.index = n;

		return pos;
	}

public:

	_Node* Head() const { return const_cast<_Node*>(&m_listHead); }

	class Iterator
	{
		_Node*	m_cur;
	public:
		Iterator() : m_cur(NULL) {}
		Iterator(_Node* node) : m_cur(node) { }
		Iterator operator++()	{ if (!End()) m_cur = m_cur->Next(); return *this;}
		bool End()	{	return m_cur == NULL;	}
		const Item* operator->() { return (m_cur) ? m_cur->Item() : NULL; }
		const Item* operator*() { return (m_cur) ? m_cur->Item() : NULL; }
		const Iterator& operator=(const Iterator& rhs) {
			m_cur = rhs.m_cur;
			return *this;
		}
		Item* Get() { return (m_cur) ? m_cur->Item() : NULL; }
	};
	
	const Iterator Begin() const { return Iterator(Head()); }


	UInt32 Count() const {
		NodePos pos = GetNthNode(eListCount);
		return (pos.index > 0) ? pos.index : 0;
	};

	Item* GetNthItem(SInt32 n) const {
		NodePos pos = GetNthNode(n);
		return (pos.index == n && pos.node) ? pos.node->Item() : NULL;
	}

	Item* GetLastItem() const {
		NodePos pos = GetNthNode(eListEnd);
		return pos.node->Item();
	}

	SInt32 AddAt(Item* item, SInt32 index) {
		if (!m_listHead.item) {
			m_listHead.item = item;
			return 0;
		}

		NodePos pos = GetNthNode(index);
		_Node* pTargetNode = pos.node;
		_Node* newNode = (_Node*)FormHeap_Allocate(sizeof(newNode));
		if (newNode && pTargetNode) {
			if (index == eListEnd) {
				pTargetNode->next = newNode;
				newNode->item = item;
				newNode->next = NULL;
			} else {
				newNode->item = pTargetNode->item;
				newNode->next = pTargetNode->next;
				pTargetNode->item = item;
				pTargetNode->next = newNode;
			}
			return pos.index;
		}
		return eListInvalid;
	}

	template <class Op>
	void Visit(Op& op, _Node* prev = NULL) const {
		const _Node* pCur = (prev) ? prev->next : Head();
		bool bContinue = true;
		while (pCur && bContinue) {
			bContinue = op.Accept(pCur->Item());
			if (bContinue) {
				pCur = pCur->next;
			}
		}
	}

	template <class Op>
	Item* Find(Op& op) const
	{
		const _Node* pCur = Head(); 

		bool bFound = false;
		while (pCur && !bFound)
		{
			if (!pCur->Item())
				pCur = pCur->Next();
			else
			{
				bFound = op.Accept(pCur->Item());
				if (!bFound)
					pCur = pCur->Next();
			}
		}
		return (bFound && pCur) ? pCur->Item() : NULL;
	}

	template <class Op>
	Iterator Find(Op& op, Iterator prev) const
	{
		Iterator curIt = (prev.End()) ? Begin() : ++prev;
		bool bFound = false;
		
		while(!curIt.End() && !bFound) {
			const tItem * pCur = *curIt;
			if (pCur) {
				bFound = op.Accept(pCur);
			}
			if (!bFound) {
				++curIt;
			}	
		}
		return curIt;
	}

	const _Node* FindString(char* str, Iterator prev) const
	{
		return Find(StringFinder_CI(str), prev);
	}

	template <class Op>
	UInt32 CountIf(Op& op) const
	{
		UInt32 count = 0;
		const _Node* pCur = Head();
		while (pCur)
		{
			if (pCur->Item() && op.Accept(pCur->Item()))
				count++;
			pCur = pCur->Next();
		}
		return count;
	}

	class AcceptAll {
	public:
		bool Accept(Item* item) {
			return true;
		}
	};

	void RemoveAll() const
	{
		FreeNodes(const_cast<_Node*>(Head()), AcceptAll());
	}

	Item* RemoveNth(SInt32 n) 
	{
		Item* pRemoved = NULL;
		if (n == 0) {
			pRemoved =  m_listHead.RemoveMe();
		} else if (n > 0) {
			NodePos nodePos = GetNthNode(n);
			if (nodePos.node && nodePos.index == n) {
				pRemoved = nodePos.node->RemoveMe();
			}
		}
		return pRemoved;
	};

	Item* ReplaceNth(SInt32 n, tItem* item) 
	{
		Item* pReplaced = NULL;
		NodePos nodePos = GetNthNode(n);
		if (nodePos.node && nodePos.index == n) {
			pReplaced = nodePos.node->item;
			nodePos.node->item = item;
		}
		return pReplaced;
	}

	template <class Op>
	UInt32 RemoveIf(Op& op)
	{
		return FreeNodes(const_cast<_Node*>(Head()), op);
	}

	template <class Op>
	SInt32 GetIndexOf(Op& op)
	{
		SInt32 idx = 0;
		const _Node* pCur = Head();
		while (pCur && pCur->Item() && !op.Accept(pCur->Item()))
		{
			idx++;
			pCur = pCur->Next();
		}

		if (pCur && pCur->Item())
			return idx;
		else
			return -1;
	}

};

STATIC_ASSERT(sizeof(tList<void *>) == 0x8);
