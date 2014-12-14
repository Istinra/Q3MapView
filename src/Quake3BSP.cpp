#include "Quake3BSP.h"
#include <cstdio>

Quake3Bsp::Quake3Bsp() : verts(nullptr), faces(nullptr), indices(nullptr), nodes(nullptr), leaves(nullptr)
{
}

Quake3Bsp::~Quake3Bsp()
{
	if (verts)
		delete [] verts;
	if (faces)
		delete[] faces;
	if (indices)
		delete[] indices;
	if (nodes)
		delete[] nodes;
	if (leaves)
		delete[] leaves;
}

bool Quake3Bsp::LoadFromFile(std::string fileName)
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
	SwizzleFace();

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

	fclose(f);
	return true;
}

void Quake3Bsp::SwizzleVector(Vec3& vec3)
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

void Quake3Bsp::SwizzleFace()
{
	for (int i = 0; i < numFaces; ++i)
	{
		SwizzleVector(faces[i].normal);
	}
}