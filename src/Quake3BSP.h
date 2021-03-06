#ifndef _QUAKE_3_BSP_
#define _QUAKE_3_BSP_

#include <string>
#include <memory>
#include "BSPTypes.h"

struct TextureData
{
	bool loaded;
	int height, width;
	std::unique_ptr<byte []> data;
};

class Quake3Bsp
{
public:
	Quake3Bsp();
	~Quake3Bsp();

	//Loads and initialises the BSP
	bool LoadFromFile(const std::string fileName);

	const BSPLeaf& FindLeaf(Vec3 position) const;

	//Checks if the to leaf is visible from the from leaf
	bool IsLeafVisible(const int fromData, const int toData);
	
	//Texture data not needed after GL textures have been created
	void CleanUpTextures();

	BSPFace const * Faces() const { return faces; }
	int FaceCount() const { return numFaces; }

	BSPVertex const * Verts() const { return verts; }
	int VertCount() const { return numVerts; }

	int const * Indices() const { return indices; }
	int IndiceCount() const { return numIndices; }

	BSPLeaf const * Leaves() const { return leaves; }
	int LeafCount() const { return numLeaves; }

	int const * LeafFaces() const { return leafFaces; }
	int LeafFaceCount() const { return numLeafFaces; }

	BSPLightMap const * LightMaps() const { return lightMaps; }
	int LightMapCount() const { return numLightMaps; }

	BSPVisData const * VisData() const { return visData; }
	int VisDataCount() const { return numVisData; }

	BSPTexture const * TexInfo() const { return textureInfo; }
	TextureData const * TexeData() const { return textureData; }
	int TextureCount() const { return numTextures; }

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

	int numLeafFaces;
	int *leafFaces;
	
	int numPlanes;
	BSPPlane *planes;

	int numLightMaps;
	BSPLightMap *lightMaps;

	int numVisData;
	BSPVisData *visData;

	int numTextures;
	BSPTexture *textureInfo;
	TextureData *textureData;

	void SwizzleVector(Vec3& vec3) const;
	void SwizzleVerts();
	void SwizzleFaces();
	void SwizzlePlanes();
	void LoadTextures();
};

#endif