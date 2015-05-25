#pragma once

#include <map>
#include <string>
#include <vector>

#include "common/ICriticalSection.h"

struct SKSESerializationInterface;
class TESForm;
class VMClassRegistry;

// Serializable classes deriving from ISKSEObject must define a
// serialization constructor that takes SerializationTag as the single argument.
// After it has been called, either Load() is used to fill in the data,
// or in case the load failed, the instance is destroyed again.
struct SerializationTag {};

///
/// ISKSEObject - Interface for a heap allocated, co-save serializable object.
///

class ISKSEObject
{
public:
	virtual ~ISKSEObject() {}

	virtual const char*	ClassName() const    = 0;
	virtual UInt32		ClassVersion() const = 0;

	virtual bool Save(SKSESerializationInterface* intfc) = 0;
	virtual bool Load(SKSESerializationInterface* intfc, UInt32 version) = 0;
};

///
/// SKSEObjectFactory
///

class ISKSEObjectFactory
{
public:
	virtual ~ISKSEObjectFactory() {}

	virtual ISKSEObject* Create() const = 0;
};

template <typename T>
class ConcreteSKSEObjectFactory : public ISKSEObjectFactory
{
public:
	virtual ISKSEObject* Create() const
	{
		SerializationTag tag;
		return new T( tag );
	}
};

///
/// SKSEObjectRegistry
///

class SKSEObjectRegistry
{
private:
	typedef std::map<std::string,UInt32> FactoryMapT;

public:
	template <typename T>
	bool RegisterClass()
	{
		ConcreteSKSEObjectFactory<T> factory;
		UInt32 vtbl = *reinterpret_cast<UInt32*>(&factory);

		SerializationTag tag;
		T tempInstance( tag );

		std::string className( tempInstance.ClassName() );

		factoryMap_[className] = vtbl;

		return true;
	}

	const ISKSEObjectFactory* GetFactoryByName(const char* name) const;

private:
	// Stores the vtables directly
	FactoryMapT factoryMap_;
};

///
/// SKSEPersistentObjectStorage
///

class SKSEPersistentObjectStorage
{
	struct Entry;

	// Note: handle = index + 1
	// +1, because in previous versions the invalid handle was 0 so people
	// might test for != 0
public:

	// Transfer ownership to registry
	template <typename T>
	SInt32 StoreObject(T* obj, UInt32 owningStackId)
	{// lock_
		IScopedCriticalSection scopedLock( &lock_ );

		Entry e = { obj, owningStackId };

		SInt32 index;

		if (freeIndices_.empty())
		{
			index = data_.size();
			data_.push_back(e);
		}
		else
		{
			index = freeIndices_.back();
			freeIndices_.pop_back();
			data_[index] = e;
		}
		
		return index + 1;
	}// ~lock_

	// Access object while keeping in storage
	template <typename T>
	T* AccessObject(SInt32 handle)
	{// lock_
		IScopedCriticalSection scopedLock( &lock_ );

		SInt32 index = handle - 1;

		if (index < 0 || index >= data_.size())
		{
			_MESSAGE("SKSEPersistentObjectStorage::AccessObject(%d): Invalid handle.", handle);
			return NULL;
		}

		Entry& e = data_[index];

		if (e.obj == NULL)
		{
			_MESSAGE("SKSEPersistentObjectStorage::AccessObject(%d): Object was NULL.", handle);
			return NULL;
		}

		T* result = dynamic_cast<T*>(e.obj);
		
		if (result == NULL)
		{
			_MESSAGE("SKSEPersistentObjectStorage::AccessObject(%d): Invalid type (%s).", handle, e.obj->ClassName());
			return NULL;
		}

		return result;
	}// ~lock_

	// Remove object from storage and take ownership of the pointer
	template <typename T>
	T* TakeObject(SInt32 handle)
	{// lock_
		IScopedCriticalSection scopedLock( &lock_ );

		SInt32 index = handle - 1;

		if (index < 0 || index >= data_.size())
		{
			_MESSAGE("SKSEPersistentObjectStorage::AccessObject(%d): Invalid handle.", handle);
			return NULL;
		}

		Entry& e = data_[index];

		if (e.obj == NULL)
		{
			_MESSAGE("SKSEPersistentObjectStorage::TakeObject(%d): Object was NULL.", handle);
			return NULL;
		}

		T* result = dynamic_cast<T*>(e.obj);
		
		if (result != NULL)
		{
			e.obj = NULL;
			freeIndices_.push_back(index);
		}
		else
		{
			_MESSAGE("SKSEPersistentObjectStorage::TakeObject(%d): Invalid type (%s).", handle, e.obj->ClassName());
			return NULL;
		}

		return result;
	}// lock_

	void CleanDroppedStacks();

	void ClearAndRelease();

	enum { kSaveVersion = 1 };

	bool Save(SKSESerializationInterface* intfc);
	bool Load(SKSESerializationInterface* intfc, UInt32 version);

private:
	struct Entry
	{
		ISKSEObject*	obj;
		UInt32			owningStackId;
	};

	typedef std::vector<Entry>		DataT;
	typedef std::vector<size_t>		IndexCacheT;

	ICriticalSection	lock_;
	DataT				data_;
	IndexCacheT			freeIndices_;
};

///
/// Serialization helpers
///

bool WriteSKSEObject(SKSESerializationInterface* intfc, ISKSEObject* obj);
bool ReadSKSEObject(SKSESerializationInterface* intfc, ISKSEObject*& objOut);

///
/// Global instances
///

SKSEObjectRegistry& SKSEObjectRegistryInstance();

SKSEPersistentObjectStorage& SKSEObjectStorageInstance();