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

	BSPFace const * const Faces() const { return faces; }
	int FaceCount() const { return numFaces; }

	BSPVertex const * const Verts() const { return verts; }
	int VertCount() const { return numVerts; }

	int const * const Indices() const { return indices; }
	int IndiceCount() const { return numIndices; }

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

	int FindLeaf(Vec3 position) const;

	void SwizzleVector(Vec3& vec3) const;
	void SwizzleVerts();
	void SwizzleFaces();
	void SwizzlePlanes();
};

#endif