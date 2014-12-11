#ifndef _QUAKE_3_BSP_
#define _QUAKE_3_BSP_

#include <string>

class Quake3Bsp
{
public:
	Quake3Bsp();
	~Quake3Bsp();

	bool LoadFromFile(std::string fileName);

private:

};

#endif