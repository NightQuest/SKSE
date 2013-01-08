#include "NiGeometry.h"
#include "GameAPI.h"

void NiGeometryData::AllocateVerts(UInt32 numVerts)
{
	m_pkVertex = (float *)FormHeap_Allocate(sizeof(float) * 3 * numVerts);
	m_pkTexture = (float *)FormHeap_Allocate(sizeof(float) * 2 * numVerts);

	memset(m_pkVertex, 0, sizeof(float) * 3 * numVerts);
	memset(m_pkTexture, 0, sizeof(float) * 2 * numVerts);
}

void NiGeometryData::AllocateNormals(UInt32 numVerts)
{
	m_pkNormal = (float *)FormHeap_Allocate(sizeof(float) * 3 * numVerts);
	memset(m_pkNormal, 0, sizeof(float) * 3 * numVerts);
}

void NiGeometryData::AllocateNBT(UInt32 numVerts)
{
	m_pkNormal = (float *)FormHeap_Allocate(sizeof(float) * 3 * 3 * numVerts);
	memset(m_pkNormal, 0, sizeof(float) * 3 * 3 * numVerts);
}

void NiGeometryData::AllocateColors(UInt32 numVerts)
{
	m_pkColor = (float *)FormHeap_Allocate(sizeof(float) * 4 * numVerts);
	memset(m_pkColor, 0, sizeof(float) * 4 * numVerts);
}

void NiSkinPartition::Partition::AllocateWeights(UInt32 numVerts)
{
	m_pfWeights = (float *)FormHeap_Allocate(sizeof(float) * 4 * numVerts);
	m_pucBonePalette = (UInt8 *)FormHeap_Allocate(sizeof(UInt8) * 4 * numVerts);

	memset(m_pfWeights, 0, sizeof(float) * 4 * numVerts);
	memset(m_pucBonePalette, 0, sizeof(UInt8) * 4 * numVerts);
}

void NiSkinData::BoneData::AllocateWeights(UInt32 numWeights)
{
	m_pkBoneVertData = (BoneVertData *)FormHeap_Allocate(sizeof(BoneVertData) * numWeights);
	memset(m_pkBoneVertData, 0, sizeof(BoneVertData) * numWeights);
}
