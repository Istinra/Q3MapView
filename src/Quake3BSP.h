#ifndef _QUAKE_3_BSP_
#define _QUAKE_3_BSP_

#include <string>
#include "BSPTypes.h"

class Quake3Bsp
{
public:
	Quake3Bsp();
	~Quake3Bsp();

	bool LoadFromFile(std::string fileName);

private:
	int numVerts;
	BSPVertex* verts;

	int numFaces;
	BSPFace* faces;

	void SwizzleVector(BSPVec3& vec3);
	void SwizzleVerts();
	void SwizzleFace();
};

#endif