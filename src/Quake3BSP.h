#ifndef _QUAKE_3_BSP_
#define _QUAKE_3_BSP_

#include <string>
#include "BSPTypes.h"

class Quake3Bsp
{
public:
	Quake3Bsp();
	~Quake3Bsp();

	bool LoadFromFile(const std::string fileName);

	const BSPLeaf& FindLeaf(Vec3 position) const;

	bool IsLeafVisible(const int fromData, const int toData);

	BSPFace const * Faces() const { return faces; }
	int FaceCount() const { return numFaces; }

	BSPVertex const * Verts() const { return verts; }
	int VertCount() const { return numVerts; }

	int const * Indices() const { return indices; }
	int IndiceCount() const { return numIndices; }

	BSPLeaf const * Leaves() const { return leaves; }
	int LeafCount() const { return numLeaves; }

	BSPLightMap const * LightMaps() const { return lightMaps; }
	int LightMapCount() const { return numLightMaps; }

	BSPVisData const * VisData() const { return visData; }
	int VisDataCount() const { return numVisData; }

private:
	int numVerts;
	BSPVertex *verts;

	int numFaces;
	BSPFace *faces;

	int numIndices;
	int *indices;

	int numNodes;
	BSPNode *nodes;

	int numLeaves;
	BSPLeaf *leaves;

	int numPlanes;
	BSPPlane *planes;

	int numLightMaps;
	BSPLightMap *lightMaps;

	int numVisData;
	BSPVisData *visData;

	void SwizzleVector(Vec3& vec3) const;
	void SwizzleVerts();
	void SwizzleFaces();
	void SwizzlePlanes();
};

#endif