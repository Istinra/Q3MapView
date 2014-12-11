#ifndef _BSP_TYPES_H_
#define _BSP_TYPES_H_

#include "Common.h"

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

struct BSPHeader
{
	char typeId[4];
	int version;
};

struct BSPVertex
{
    float x, y, z;
    float u, v;
    float lu, lv;
    byte colour;
};

#endif