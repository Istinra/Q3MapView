#ifndef _BSP_TYPES_H_
#define _BSP_TYPES_H_

#include "Common.h"

struct BSPVec2
{
	float x, y;
};

struct BSPVec3
{
	float x, y, z;
};

enum BSPLumps
{
    ENTITIES = 0,
    TEXTURES,
    PLANES,
    NODES,
    LEAFS,
    LEAF_FACES,
    LEAF_BRUSHES,
    MODELS,
    BRUSHES,
    BRUSH_SIDES,
    VERTICIES,
    INDICES,
    SHADERS,
    FACES,
    LIGHT_MAPS,
    LIGHT_VOLMES,
    VIS_DATA,
    MAX_LUMPS
};

struct BSPLump
{
	int offset;
	int length;
};

struct BSPHeader
{
	char typeId[4];
	int version;
};

struct BSPVertex
{
	BSPVec3 pos;
	BSPVec2 texCoords;
	BSPVec2 lightMapCoords;
    byte colour;
};

enum BSPFaceType
{
	POLYGON = 1,
	PATCH,
	MESH,
	BILLBOARD
};

struct BSPFace
{
	int textureId;
	int effect;
	BSPFaceType type;
	int startVertIndex;
	int numVerts;
	int startIndex;
	int numIndices;
	int lightmapId;
	BSPVec2 lightMapCorner;
	BSPVec2 lightMapSize;
	BSPVec3 lightMapPos;
	float lMapVecs[2][3];
	BSPVec3 normal;
	int size[2];
};

#endif