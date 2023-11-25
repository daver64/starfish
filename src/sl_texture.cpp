
#ifdef _WIN32
#include <windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include "sl_glext.h"
#else
#include <GL/gl.h>
#include <GL/glext.h>
#endif

#include "sl_texture.h"
 
Texture::Texture(int32 width, int32 height, bool mipmapped)
    : width(width), height(height), mipmapped(mipmapped)
{
    pixel32 *pixeldata=new pixel32[width*height];
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &glref);
	glBindTexture(GL_TEXTURE_2D, glref);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixeldata);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (mipmapped)
	{
		//glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

}
Texture::~Texture()
{
    delete[] pixeldata;
    glDeleteTextures(1,&glref);
}