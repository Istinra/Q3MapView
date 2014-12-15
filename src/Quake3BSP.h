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

	int FindLeaf(Vec3 position);

	void SwizzleVector(Vec3& vec3);
	void SwizzleVerts();
	void SwizzleFaces();
	void SwizzlePlanes();
};

#endif