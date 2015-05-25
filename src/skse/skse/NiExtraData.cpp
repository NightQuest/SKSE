#include "NiExtraData.h"
#include "NiGeometry.h"

static const UInt32 s_BSFaceGenBaseMorphExtraDataVtbl = 0x010BE944;

NiExtraData* NiExtraData::Create(UInt32 size, UInt32 vtbl)
{
	void* memory = FormHeap_Allocate(size);
	memset(memory, 0, size);
	NiExtraData* xData = (NiExtraData*)memory;
	((UInt32*)memory)[0] = vtbl;
	return xData;
}

BSFaceGenBaseMorphExtraData* BSFaceGenBaseMorphExtraData::Create(NiGeometryData * geometryData, bool copy)
{
	BSFaceGenBaseMorphExtraData* data = (BSFaceGenBaseMorphExtraData*)NiExtraData::Create(sizeof(BSFaceGenBaseMorphExtraData), s_BSFaceGenBaseMorphExtraDataVtbl);
	data->m_pcName = const_cast<char*>(BSFixedString("FOD").data);
	data->m_uiRefCount = 0;
	data->modelVertexCount = 0;
	data->vertexCount = 0;
	data->vertexData = NULL;

	if (geometryData) {
		data->vertexCount = geometryData->m_usVertices;
		data->modelVertexCount = geometryData->m_usVertices;

		data->vertexData = (NiPoint3*)FormHeap_Allocate(sizeof(NiPoint3) * data->vertexCount);
		if(copy)
			memcpy(data->vertexData, geometryData->m_pkVertex, sizeof(NiPoint3) * data->vertexCount);
		else
			memset(data->vertexData, 0, sizeof(NiPoint3) * data->vertexCount);
	}

	return data;
}