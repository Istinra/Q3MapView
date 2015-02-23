#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "glew.h"
#include "Common.h"

class Texture
{
public:
	Texture() : glTextureId(0) {}
	Texture(int mapTextureId, int width, int height, const byte* data);
	Texture(Texture &&o);
	Texture& operator=(Texture &&o);
	~Texture();

	void Bind();

private:
	//Can't copy opengl resources, need to move them
	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;

	int mapTextureId;
	GLuint glTextureId;
	unsigned short textureUnit;
};

#endif