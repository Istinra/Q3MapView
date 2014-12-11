#include "Quake3BSP.h"
#include "BSPTypes.h"
#include <cstdio>

Quake3Bsp::Quake3Bsp()
{
}

Quake3Bsp::~Quake3Bsp()
{
}

bool Quake3Bsp::LoadFromFile(std::string fileName)
{
	FILE *f = fopen(fileName.c_str(), "rb");
	if (!f)
	{
		return false;
	}

	BSPHeader header;
	fread(&header, sizeof(header), 1, f);

	fclose(f);
	return true;
}