#include "PapyrusObjects.h"

#include "Serialization.h"

#include "PapyrusVM.h"

namespace
{
	static const size_t kMaxNameLen  = 1024;
}

///
/// SKSEObjectRegistry
///

const ISKSEObjectFactory* SKSEObjectRegistry::GetFactoryByName(const char* name) const
{
	std::string t( name );

	const ISKSEObjectFactory* result = NULL;

	FactoryMapT::const_iterator it = factoryMap_.find(t);
	if (it != factoryMap_.end())
	{
		result = reinterpret_cast<const ISKSEObjectFactory*>(&it->second);
	}

	return result;
}

///
/// SKSEPersistentObjectStorage
///

void SKSEPersistentObjectStorage::CleanDroppedStacks()
{
	VMClassRegistry* registry = (*g_skyrimVM)->GetClassRegistry();

	for (UInt32 i=0; i<data_.size(); i++)
	{
		Entry& e = data_[i];

		if (e.obj == NULL)
			continue;

		if (registry->GetStackInfo(e.owningStackId) != NULL)
			continue;

		// Stack no longer active, drop this entry

		delete e.obj;
		e.obj = NULL;

		freeIndices_.push_back(i);

		_MESSAGE("SKSEPersistentObjectStorage::CleanDroppedStacks: Freed object at index %d.", i);
	}
}

void SKSEPersistentObjectStorage::ClearAndRelease()
{
	freeIndices_.clear();

	for (DataT::iterator it = data_.begin(); it != data_.end(); ++it)
	{
		Entry& e = *it;
		if (e.obj != NULL)
			delete e.obj;
	}

	data_.clear();
}

bool SKSEPersistentObjectStorage::Save(SKSESerializationInterface* intfc)
{
	using namespace Serialization;

	// Before saving, purge entries whose owning stack is no longer running.
	// This can happen if someone forgot to release an object.
	// We don't want these resource leaks to pile up in the co-save.
	CleanDroppedStacks();

	// Save data
	UInt32 dataSize = data_.size();
	if (! WriteData(intfc, &dataSize))
		return false;

	UInt32 filledSize = data_.size() - freeIndices_.size();
	if (! WriteData(intfc, &filledSize))
		return false;

	for (UInt32 i=0; i<dataSize; i++)
	{
		Entry& e = data_[i];

		// Data of free indices is null, so we skip these
		if (e.obj == NULL)
			continue;
		
		// Skip to next entry if write failed
		if (! WriteSKSEObject(intfc, e.obj))
			continue;

		WriteData(intfc, &e.owningStackId);

		UInt32 index = i;
		WriteData(intfc, &index);
	}

	return true;
}

bool SKSEPersistentObjectStorage::Load(SKSESerializationInterface* intfc, UInt32 loadedVersion)
{
	using namespace Serialization;

	// Load data
	UInt32 dataSize;
	if (! ReadData(intfc,&dataSize))
		return false;

	data_.resize(dataSize);

	UInt32 filledSize;
	if (! ReadData(intfc,&filledSize))
		return false;

	for (UInt32 i=0; i<filledSize; i++)
	{
		Entry e = { 0 };

		if (! ReadSKSEObject(intfc, e.obj))
			continue;

		ReadData(intfc, &e.owningStackId);

		UInt32 index;
		ReadData(intfc, &index);

		data_[index] = e;
	}
	
	// Rebuild free index list
	for (UInt32 i=0; i<data_.size(); i++)
		if (data_[i].obj == NULL)
			freeIndices_.push_back(i);

	return true;
}

///
/// Serialization helpers
///

bool WriteSKSEObject(SKSESerializationInterface* intfc, ISKSEObject* obj)
{
	using namespace Serialization;

	const char*  name	 = obj->ClassName();
	const UInt32 version = obj->ClassVersion();

	intfc->OpenRecord('OBJE', version);

	size_t rawLen = strlen(name);
	UInt32 len    = (std::min)(rawLen, kMaxNameLen);

	if (! WriteData(intfc, &len))
		return false;

	if (! intfc->WriteRecordData(name, len))
		return false;

	return obj->Save(intfc);
}

bool ReadSKSEObject(SKSESerializationInterface* intfc, ISKSEObject*& objOut)
{
	UInt32 type, length, objVersion;

	if (! intfc->GetNextRecordInfo(&type, &objVersion, &length))
		return false;

	if (type != 'OBJE')
	{
		_MESSAGE("ReadSKSEObject: Error loading unexpected chunk type %08X (%.4s)", type, &type);
		return false;
	}

	// Read the name of the serialized class
	UInt32 len;
	if (! intfc->ReadRecordData(&len, sizeof(len)))
		return false;

	if (len > kMaxNameLen)
	{
		_MESSAGE("ReadSKSEObject: Serialization error. Class name len extended kMaxNameLen.");
		return false;
	}

	char buf[kMaxNameLen+1] = { 0 };
	if (! intfc->ReadRecordData(&buf, len))
		return false;

	// Get the factory
	const ISKSEObjectFactory* factory = SKSEObjectRegistryInstance().GetFactoryByName(buf);
	if (factory == NULL)
	{
		_MESSAGE("ReadSKSEObject: Serialization error. Factory missing for %s.", &buf);
		return false;
	}

	// Intantiate and load the actual data
	ISKSEObject* obj = factory->Create();
	if (! obj->Load(intfc, objVersion))
	{
		// Load failed. clean up.
		objOut = NULL;
		delete obj;

		return false;
	}

	objOut = obj;
	return true;
}

///
/// Global instances
///

SKSEObjectRegistry& SKSEObjectRegistryInstance()
{
	static SKSEObjectRegistry instance;
	return instance;
}

SKSEPersistentObjectStorage& SKSEObjectStorageInstance()
{
	static SKSEPersistentObjectStorage instance;
	return instance;
}
