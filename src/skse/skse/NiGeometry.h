#pragma once

#include "skse/NiNodes.h"

// NiGeometry, NiGeometryData and children

class NiGeometryData;
class NiSkinInstance;
class NiAdditionalGeometryData;

// B8+
class NiGeometry : public NiAVObject
{
public:
	void			* m_spPropertyState;	// A8 - unconfirmed
	void			* m_spEffectState;		// AC - unconfirmed
	NiGeometryData	* m_spModelData;		// B0
	NiSkinInstance	* m_spSkinInstance;		// B4

	// ... materials
};

class NiTriBasedGeom : public NiGeometry
{
public:
};

class NiTriShape : public NiTriBasedGeom
{
public:
};

// 48+
class NiGeometryData : public NiObject
{
public:
	enum
	{
		kDataFlag_HasUVs =	1 << 0,
		kDataFlag_HasNBT =	1 << 12,
	};

	UInt16	m_usVertices;				// 08
	UInt16	m_usID;						// 0A
	UInt16	m_usDirtyFlags;				// 0C
	UInt16	m_usDataFlags;				// 0E
	NiBound	m_kBound;					// 10
	float	* m_pkVertex;				// 20
	float	* m_pkNormal;				// 24 - all normals, then all binormals etc
	float	* m_pkColor;				// 28 - yes really, floats (b g r a)
	float	* m_pkTexture;				// 2C
	UInt32	unk30;						// 30
	UInt32	unk34;						// 34
	UInt32	unkInt2;					// 38
	NiAdditionalGeometryData	* m_spAdditionalGeomData;	// 3C
	UInt32	unk40;						// 40
	UInt8	m_ucKeepFlags;				// 44
	UInt8	m_ucCompressFlags;			// 45
	UInt8	hasGeoData;					// 46

	void	AllocateVerts(UInt32 numVerts);
	void	AllocateNormals(UInt32 numVerts);
	void	AllocateNBT(UInt32 numVerts);
	void	AllocateColors(UInt32 numVerts);
};

// 4C
class NiTriBasedGeomData : public NiGeometryData
{
public:
	UInt16	m_usTriangles;			// 48
	UInt16	m_usActiveTriangles;	// 4A
};

// 54+
class NiTriShapeData : public NiTriBasedGeomData
{
public:
	UInt32	m_uiTriListLength;		// 4C
	UInt16	* m_pusTriList;			// 50
};

// 10
class NiSkinPartition : public NiObject
{
public:
	// 28
	struct Partition
	{
		UInt16		* m_pusBones;			// 00
		float		* m_pfWeights;			// 04
		UInt16		* m_pusVertexMap;		// 08
		UInt8		* m_pucBonePalette;		// 0C
		UInt16		* m_pusTriList;			// 10
		UInt16		* m_pusStripLengths;	// 14
		UInt16		m_usVertices;			// 18
		UInt16		m_usTriangles;			// 1A
		UInt16		m_usBones;				// 1C
		UInt16		m_usStrips;				// 1E
		UInt16		m_usBonesPerVertex;		// 20
		UInt8		pad22[2];				// 22
		UInt32		unk24;					// 24

		void	AllocateWeights(UInt32 numVerts);
	};

	UInt32		m_uiPartitions;		// 08
	Partition	* m_pkPartitions;	// 0C
};

// 44+
class NiSkinData : public NiObject
{
public:
	// 08
	struct BoneVertData
	{
		UInt16	m_usVert;	// 00
		UInt8	pad02[2];	// 02
		float	m_fWeight;	// 04?
	};

	// 4C
	struct BoneData
	{
		NiTransform		m_kSkinToBone;		// 00
		NiBound			m_kBound;			// 34
		BoneVertData	* m_pkBoneVertData;	// 44
		UInt16			m_usVerts;			// 48
		UInt8			pad4A[2];			// 4A

		void	AllocateWeights(UInt32 numVerts);
	};

	NiSkinPartition	* m_spSkinPartition;	// 08
	NiTransform		m_kRootParentToSkin;	// 0C
	BoneData		* m_pkBoneData;			// 40
	UInt32			m_uiBones;				// 44
};

STATIC_ASSERT(sizeof(NiSkinData::BoneVertData) == 0x08);

// 18
class NiSkinInstance : public NiObject
{
public:
	NiSkinData		* m_spSkinData;			// 08
	NiSkinPartition	* m_spSkinPartition;	// 0C
	NiAVObject		* m_pkRootParent;		// 10
	NiAVObject		** m_ppkBones;			// 14
	// ...
};
