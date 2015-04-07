#include "Serialization.h"
#include "common/IFileStream.h"
#include "PluginManager.h"
#include "GameAPI.h"
#include "skse_version.h"
#include <vector>
#include <shlobj.h>
#include "GameData.h"
#include "InternalSerialization.h"
#include "GameSettings.h"

namespace Serialization
{
	const char * kSavegamePath = "\\My Games\\Skyrim\\";

	// file format internals

	//	general format:
	//	Header			header
	//		PluginHeader	plugin[header.numPlugins]
	//			ChunkHeader		chunk[plugin.numChunks]
	//				UInt8			data[chunk.length]

	struct Header
	{
		enum
		{
			kSignature =		MACRO_SWAP32('SKSE'),	// endian-swapping so the order matches
			kVersion =			1,

			kVersion_Invalid =	0
		};

		UInt32	signature;
		UInt32	formatVersion;
		UInt32	skseVersion;
		UInt32	runtimeVersion;
		UInt32	numPlugins;
	};

	struct PluginHeader
	{
		UInt32	signature;
		UInt32	numChunks;
		UInt32	length;		// length of following data including ChunkHeader
	};

	struct ChunkHeader
	{
		UInt32	type;
		UInt32	version;
		UInt32	length;
	};

	// locals

	std::string		s_savePath;
	IFileStream		s_currentFile;

	typedef std::vector <PluginCallbacks>	PluginCallbackList;
	PluginCallbackList	s_pluginCallbacks;

	PluginHandle	s_currentPlugin = 0;

	Header			s_fileHeader = { 0 };

	UInt64			s_pluginHeaderOffset = 0;
	PluginHeader	s_pluginHeader = { 0 };

	bool			s_chunkOpen = false;
	UInt64			s_chunkHeaderOffset = 0;
	ChunkHeader		s_chunkHeader = { 0 };

	// utilities

	// make full path from save name
	std::string MakeSavePath(std::string name, const char * extension)
	{
		char	path[MAX_PATH];
		ASSERT(SUCCEEDED(SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, SHGFP_TYPE_CURRENT, path)));

		std::string	result = path;
		result += kSavegamePath;
		Setting* localSavePath = GetINISetting("sLocalSavePath:General");
		if(localSavePath && (localSavePath->GetType() == Setting::kType_String))
			result += localSavePath->data.s;
		else
			result += "Saves\\";

		result += "\\";
		result += name;
		if (extension)
			result += extension;
		return result;
	}

	// plugin API
	void SetRevertCallback(PluginHandle plugin, SKSESerializationInterface::EventCallback callback)
	{
		if(plugin >= s_pluginCallbacks.size())
			s_pluginCallbacks.resize(plugin + 1);

		s_pluginCallbacks[plugin].revert = callback;
	}

	void SetSaveCallback(PluginHandle plugin, SKSESerializationInterface::EventCallback callback)
	{
		if(plugin >= s_pluginCallbacks.size())
			s_pluginCallbacks.resize(plugin + 1);

		s_pluginCallbacks[plugin].save = callback;
	}

	void SetLoadCallback(PluginHandle plugin, SKSESerializationInterface::EventCallback callback)
	{
		if(plugin >= s_pluginCallbacks.size())
			s_pluginCallbacks.resize(plugin + 1);

		s_pluginCallbacks[plugin].load = callback;
	}

	void SetFormDeleteCallback(PluginHandle plugin, SKSESerializationInterface::EventCallback callback)
	{
		if(plugin >= s_pluginCallbacks.size())
			s_pluginCallbacks.resize(plugin + 1);

		s_pluginCallbacks[plugin].formDelete = callback;
	}

	void SetSaveName(const char * name)
	{
		if(name)
		{
			_MESSAGE("save name is %s", name);
			s_savePath = MakeSavePath(name, ".skse");
			_MESSAGE("full save path: %s", s_savePath.c_str());
		}
		else
		{
			_MESSAGE("cleared save path");
			s_savePath.clear();
		}
	}

	bool WriteRecord(UInt32 type, UInt32 version, const void * buf, UInt32 length)
	{
		if(!OpenRecord(type, version))
			return false;

		return WriteRecordData(buf, length);
	}

	// flush a chunk header to the file if one is currently open
	static void FlushWriteChunk(void)
	{
		if(!s_chunkOpen)
			return;

		UInt64	curOffset = s_currentFile.GetOffset();
		UInt64	chunkSize = curOffset - s_chunkHeaderOffset - sizeof(s_chunkHeader);

		ASSERT(chunkSize < 0x80000000);	// stupidity check

		s_chunkHeader.length = (UInt32)chunkSize;

		s_currentFile.SetOffset(s_chunkHeaderOffset);
		s_currentFile.WriteBuf(&s_chunkHeader, sizeof(s_chunkHeader));

		s_currentFile.SetOffset(curOffset);

		s_pluginHeader.length += chunkSize + sizeof(s_chunkHeader);

		s_chunkOpen = false;
	}

	bool OpenRecord(UInt32 type, UInt32 version)
	{
		if(!s_pluginHeader.numChunks)
		{
			ASSERT(!s_chunkOpen);

			s_pluginHeaderOffset = s_currentFile.GetOffset();
			s_currentFile.Skip(sizeof(s_pluginHeader));
		}

		FlushWriteChunk();

		s_chunkHeaderOffset = s_currentFile.GetOffset();
		s_currentFile.Skip(sizeof(s_chunkHeader));

		s_pluginHeader.numChunks++;

		s_chunkHeader.type = type;
		s_chunkHeader.version = version;
		s_chunkHeader.length = 0;

		s_chunkOpen = true;

		return true;
	}

	bool WriteRecordData(const void * buf, UInt32 length)
	{
		s_currentFile.WriteBuf(buf, length);

		return true;
	}

	static void FlushReadRecord(void)
	{
		if(s_chunkOpen)
		{
			if(s_chunkHeader.length)
			{
				// _WARNING("plugin didn't finish reading chunk");
				s_currentFile.Skip(s_chunkHeader.length);
			}

			s_chunkOpen = false;
		}
	}

	bool GetNextRecordInfo(UInt32 * type, UInt32 * version, UInt32 * length)
	{
		FlushReadRecord();

		if(!s_pluginHeader.numChunks)
			return false;

		s_pluginHeader.numChunks--;

		s_currentFile.ReadBuf(&s_chunkHeader, sizeof(s_chunkHeader));

		*type =		s_chunkHeader.type;
		*version =	s_chunkHeader.version;
		*length =	s_chunkHeader.length;

		s_chunkOpen = true;

		return true;
	}

	UInt32 ReadRecordData(void * buf, UInt32 length)
	{
		ASSERT(s_chunkOpen);

		if(length > s_chunkHeader.length)
			length = s_chunkHeader.length;

		s_currentFile.ReadBuf(buf, length);

		s_chunkHeader.length -= length;

		return length;
	}

	bool ResolveHandle(UInt64 handle, UInt64 * handleOut)
	{
		UInt8	modID = handle >> 24;

		// should not have been saved anyway?
		if (modID == 0xFF)
			return false;

		UInt8	loadedModID = ResolveModIndex(modID);

		if (loadedModID == 0xFF) 
			return false;

		// fixup ID, success
		*handleOut = (loadedModID << 24) | (handle & 0xFFFFFFFF00FFFFFF);

		return true;
	}

	// internal event handlers
	void HandleRevertGlobalData(void)
	{
		for(UInt32 i = 0; i < s_pluginCallbacks.size(); i++)
			if(s_pluginCallbacks[i].revert)
				s_pluginCallbacks[i].revert(&g_SKSESerializationInterface);
	}

	void HandleSaveGlobalData(void)
	{
		_MESSAGE("creating co-save");
		if(!s_currentFile.Create(s_savePath.c_str()))
		{
			_ERROR("HandleSaveGlobalData: couldn't create save file (%s)", s_savePath.c_str());
			return;
		}

		try
		{
			// init header
			s_fileHeader.signature =		Header::kSignature;
			s_fileHeader.formatVersion =	Header::kVersion;
			s_fileHeader.skseVersion =		PACKED_SKSE_VERSION;
			s_fileHeader.runtimeVersion =	RUNTIME_VERSION;
			s_fileHeader.numPlugins =		0;

			s_currentFile.Skip(sizeof(s_fileHeader));

			// iterate through plugins
			for(UInt32 i = 0; i < s_pluginCallbacks.size(); i++)
			{
				if(s_pluginCallbacks[i].save)
				{
					// set up header info
					s_currentPlugin = i;

					// TODO:
					// Set s_pluginHeader.signature to value from plugin header.

					s_pluginHeader.numChunks = 0;
					s_pluginHeader.length = 0;

					s_chunkOpen = false;

					// call the plugin
					s_pluginCallbacks[i].save(&g_SKSESerializationInterface);

					// flush the remaining chunk data
					FlushWriteChunk();

					if(s_pluginHeader.numChunks)
					{
						UInt64	curOffset = s_currentFile.GetOffset();

						s_currentFile.SetOffset(s_pluginHeaderOffset);
						s_currentFile.WriteBuf(&s_pluginHeader, sizeof(s_pluginHeader));

						s_currentFile.SetOffset(curOffset);

						s_fileHeader.numPlugins++;
					}
				}
			}

			// write header
			s_currentFile.SetOffset(0);
			s_currentFile.WriteBuf(&s_fileHeader, sizeof(s_fileHeader));
		}
		catch(...)
		{
			_ERROR("HandleSaveGame: exception during save");
		}

		s_currentFile.Close();
	}

	void HandleLoadGlobalData(void)
	{
		_MESSAGE("loading co-save");

		if(!s_currentFile.Open(s_savePath.c_str()))
		{
			return;
		}

		try
		{
			Header	header;

			s_currentFile.ReadBuf(&header, sizeof(header));

			if(header.signature != Header::kSignature)
			{
				_ERROR("HandleLoadGame: invalid file signature (found %08X expected %08X)", header.signature, Header::kSignature);
				goto done;
			}

			if(header.formatVersion <= Header::kVersion_Invalid)
			{
				_ERROR("HandleLoadGame: version invalid (%08X)", header.formatVersion);
				goto done;
			}

			if(header.formatVersion > Header::kVersion)
			{
				_ERROR("HandleLoadGame: version too new (found %08X current %08X)", header.formatVersion, Header::kVersion);
				goto done;
			}

			// reset flags
			for(PluginCallbackList::iterator iter = s_pluginCallbacks.begin(); iter != s_pluginCallbacks.end(); ++iter)
				iter->hadData = false;
			
			// iterate through plugin data chunks
			while(s_currentFile.GetRemain() >= sizeof(PluginHeader))
			{
				s_currentFile.ReadBuf(&s_pluginHeader, sizeof(s_pluginHeader));

				UInt64	pluginChunkStart = s_currentFile.GetOffset();

				// TODO:
				// This would have to look up the plugin index by signature
				
				//find the corresponding plugin
				UInt32	pluginIdx = 0;
				if(pluginIdx != kPluginHandle_Invalid)
				{
					s_pluginCallbacks[pluginIdx].hadData = true;

					if(s_pluginCallbacks[pluginIdx].load)
					{
						s_chunkOpen = false;
						s_pluginCallbacks[pluginIdx].load(&g_SKSESerializationInterface);
					}
				}

				UInt64	expectedOffset = pluginChunkStart + s_pluginHeader.length;
				if(s_currentFile.GetOffset() != expectedOffset)
				{
					_WARNING("plugin did not read all of its data (at %016I64X expected %016I64X)", s_currentFile.GetOffset(), expectedOffset);
					s_currentFile.SetOffset(expectedOffset);
				}
			}
		}
		catch(...)
		{
			_ERROR("HandleLoadGame: exception during load");

			// ### this could be handled better, individually catch around each plugin so one plugin can't mess things up for everyone else
		}

	done:
		s_currentFile.Close();
	}

	void HandleDeleteSave(std::string saveName)
	{
		std::string savePath = MakeSavePath(saveName, NULL);
		std::string coSavePath = savePath;
		savePath += ".ess";
		coSavePath += ".skse";

		// Old save file really gone?
		IFileStream	saveFile;
		if (!saveFile.Open(savePath.c_str()))
		{
			_MESSAGE("deleting co-save %s", coSavePath.c_str());	
			DeleteFile(coSavePath.c_str());
		}
		else
		{
			_MESSAGE("skipped delete of co-save %s", coSavePath.c_str());	
		}
	}

	template <>
	bool WriteData<BSFixedString>(SKSESerializationInterface * intfc, const BSFixedString * str)
	{
		UInt16 len = strlen(str->data);

		if (! intfc->WriteRecordData(&len, sizeof(len)))
			return false;
		if (! intfc->WriteRecordData(str->data, len))
			return false;
		return true;
	}

	template <>
	bool ReadData<BSFixedString>(SKSESerializationInterface * intfc, BSFixedString * str)
	{
		char buf[256] = {0};
		UInt16 len = 0;
		if (! intfc->ReadRecordData(&len, sizeof(len)))
			return false;
		if (! intfc->ReadRecordData(buf, len))
			return false;

		*str = BSFixedString(buf);
		return true;
	}
}

SKSESerializationInterface	g_SKSESerializationInterface =
{
	SKSESerializationInterface::kVersion,

	Serialization::SetRevertCallback,
	Serialization::SetSaveCallback,
	Serialization::SetLoadCallback,
	Serialization::SetFormDeleteCallback,

	Serialization::WriteRecord,
	Serialization::OpenRecord,
	Serialization::WriteRecordData,

	Serialization::GetNextRecordInfo,
	Serialization::ReadRecordData,
	Serialization::ResolveHandle
};
