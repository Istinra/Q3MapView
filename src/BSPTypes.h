#ifndef _BSP_TYPES_H_
#define _BSP_TYPES_H_

#include "Common.h"

struct Vec2
{
	float x, y;
};

struct Vec3
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
	Vec3 pos;
	Vec2 texCoords;
	Vec2 lightMapCoords;
	Vec3 normal;
    byte colour[4];
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
	Vec2 lightMapCorner;
	Vec2 lightMapSize;
	Vec3 lightMapPos;
	float lMapVecs[2][3];
	Vec3 normal;
	int size[2];
};

struct BSPNode
{
	int planeIndex;
	int front;
	int back;
	int minsBounding[3];
	int maxBounding[3];
};

struct BSPPlane
{
	Vec3 normal;
	float distance; //Plane distance from origin
};

struct BSPLeaf
{
	int visData;
	int area;
	int minsBounding[3];
	int maxBounding[3];
	int firstLeafFace;
	int numLeafFace;
	int firstLeafBrush;
	int numLeafBrushes;
};

struct BSPVisData
{
	int numVecs;
	int vecSize;
	byte *vectors;
};

#endif