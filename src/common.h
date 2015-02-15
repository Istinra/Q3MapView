#ifndef _COMMON_H_
#define _COMMON_H_

#include <string>

typedef unsigned char byte;

struct Time
{
	double dt, total;
};

void StringReplaceAll(std::string& str, const std::string& from, const std::string& to);

#endif