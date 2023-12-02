
/**
 * (c) 2023 David Rowbotham thedaver64@gmail.com
*/
#ifdef _WIN32
#include <windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include "sl_glext.h"
#else
//#include <GL/glew.h>
//#include <GL/gl.h>
#define GL_GLEXT_PROTOTYPES
//#include <GL/glext.h>
#include <GLFW/glfw3.h>
#include <cstring>
#endif

#include "sl_texture.h"
#include "stb_image.h"


SLTexture::SLTexture(const char *filename, bool mipmapped)
{
	pixel32* pxd=(pixel32*)stbi_load(filename,&width,&height,0,4);
	pixeldata=new pixel32[width*height];
	memcpy(pixeldata,pxd,width*height*sizeof(pixel32));
	stbi_image_free((void*)pxd);
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &glref);
	glBindTexture(GL_TEXTURE_2D, glref);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixeldata);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (mipmapped)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
}
SLTexture::SLTexture(int32 width, int32 height, bool mipmapped)
    : width(width), height(height), mipmapped(mipmapped)
{
    pixeldata=new pixel32[width*height];
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &glref);
	glBindTexture(GL_TEXTURE_2D, glref);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixeldata);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (mipmapped)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

}
SLTexture::~SLTexture()
{
    delete[] pixeldata;
    glDeleteTextures(1,&glref);
}


