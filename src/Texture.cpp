#include "Texture.h"


Texture::Texture(int mapTextureId, int width, int height, const byte* data) : mapTextureId(mapTextureId)
{
	glGenTextures(1, &glTextureId);
	Bind();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
}

Texture::Texture(Texture&& o) : mapTextureId(o.mapTextureId), glTextureId(o.glTextureId), textureUnit(o.textureUnit)
{
	o.glTextureId = 0;
}

Texture& Texture::operator=(Texture&& o)
{
	mapTextureId = o.mapTextureId;
	glTextureId = o.glTextureId;
	textureUnit = o.textureUnit;
	o.glTextureId = 0;
	return *this;
}

Texture::~Texture()
{
	if (glTextureId)
	{
		glDeleteTextures(1, &glTextureId);
	}
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, glTextureId);
}
