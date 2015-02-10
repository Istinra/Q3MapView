#include "Quake3BSP.h"
#include <cstdio>

Quake3Bsp::Quake3Bsp() : verts(nullptr), faces(nullptr), indices(nullptr),
nodes(nullptr), leaves(nullptr), planes(nullptr), lightMaps(nullptr), visData(nullptr)
{
}

Quake3Bsp::~Quake3Bsp()
{
	if (verts)
		delete [] verts;
	if (faces)
		delete [] faces;
	if (indices)
		delete [] indices;
	if (nodes)
		delete [] nodes;
	if (leaves)
		delete [] leaves;
	if (planes)
		delete [] planes;
	if (lightMaps)
		delete[] lightMaps;
	if (visData)
		delete[] visData;
}

bool Quake3Bsp::LoadFromFile(const std::string fileName)
{
	FILE *f = fopen(fileName.c_str(), "rb");
	if (!f)
		return false;

	//Load and check the header
	BSPHeader header;
	fread(&header, sizeof(header), 1, f);
	if (strncmp(header.typeId, "IBSP", 4) != 0)
		return false;

	//Load lump indexes
	BSPLump lumps[MAX_LUMPS];
	fread(&lumps, sizeof(lumps), 1, f);

	//Load Verts
	numVerts = lumps[VERTICIES].length / sizeof(BSPVertex);
	verts = new BSPVertex[numVerts];
	fseek(f, lumps[VERTICIES].offset, 0);
	fread(verts, sizeof(BSPVertex), numVerts, f);
	SwizzleVerts();

	//Load Faces
	numFaces = lumps[FACES].length / sizeof(BSPFace);
	faces = new BSPFace[numFaces];
	fseek(f, lumps[FACES].offset, 0);
	fread(faces, sizeof(BSPFace), numFaces, f);
	SwizzleFaces();

	//Load Indices
	numIndices = lumps[INDICES].length / sizeof(int);
	indices = new int[numIndices];
	fseek(f, lumps[INDICES].offset, 0);
	fread(indices, sizeof(int), numIndices, f);

	//Load Nodes
	numNodes = lumps[NODES].length / sizeof(BSPNode);
	nodes = new BSPNode[numNodes];
	fseek(f, lumps[NODES].offset, 0);
	fread(nodes, sizeof(BSPNode), numNodes, f);

	//Load Leaves
	numLeaves = lumps[LEAFS].length / sizeof(BSPLeaf);
	leaves = new BSPLeaf[numLeaves];
	fseek(f, lumps[LEAFS].offset, 0);
	fread(leaves, sizeof(BSPLeaf), numLeaves, f);

	//Load Planes
	numPlanes = lumps[PLANES].length / sizeof(BSPPlane);
	planes = new BSPPlane[numPlanes];
	fseek(f, lumps[PLANES].offset, 0);
	fread(planes, sizeof(BSPPlane), numPlanes, f);
	SwizzlePlanes();

	//Load Light Maps
	numLightMaps = lumps[LIGHT_MAPS].length / sizeof(BSPLightMap);
	lightMaps = new BSPLightMap[numLightMaps];
	fseek(f, lumps[LIGHT_MAPS].offset, 0);
	fread(lightMaps, sizeof(BSPLightMap), numLightMaps, f);

	//Load Vis Data
	numVisData = lumps[VIS_DATA].length / sizeof(BSPVisData);
	visData = new BSPVisData[numVisData];
	fseek(f, lumps[VIS_DATA].offset, 0);
	fread(visData, sizeof(BSPVisData), numVisData, f);

	fclose(f);
	return true;
}

const BSPLeaf& Quake3Bsp::FindLeaf(Vec3 position) const
{
	int nodeIndex = 0;

	float distance;
	while (nodeIndex > 0)
	{
		const BSPNode &node = nodes[nodeIndex];
		const BSPPlane &plane = planes[node.planeIndex];

		distance = plane.normal.x * position.x +
			plane.normal.x * position.y +
			plane.normal.x * position.x - plane.distance;

		if (distance > 0)
		{
			nodeIndex = node.front;
		}
		else
		{
			nodeIndex = node.back;
		}
	}
	//When the node references a leaf the number is negative -(nodeIndex + 1)
	return leaves[~nodeIndex];
}

bool Quake3Bsp::IsLeafVisible(const int fromData, const int toData)
{
	if (!visData->vectors || fromData < 0)
		return true;
	byte vector = visData->vectors[fromData * visData->vecSize + toData / 8];
	return vector & (1 << (toData & 7));
}

void Quake3Bsp::SwizzleVector(Vec3& vec3) const
{
	float temp = vec3.y;
	vec3.y = vec3.z;
	vec3.z = -temp;
}

void Quake3Bsp::SwizzleVerts()
{
	for (int i = 0; i < numVerts; ++i)
	{
		SwizzleVector(verts[i].pos);
	}
}

void Quake3Bsp::SwizzleFaces()
{
	for (int i = 0; i < numFaces; ++i)
	{
		SwizzleVector(faces[i].normal);
	}
}

void Quake3Bsp::SwizzlePlanes()
{
	for (int i = 0; i < numPlanes; ++i)
	{
		SwizzleVector(planes[i].normal);
	}
}