
/**
 * (c) 2023 David Rowbotham thedaver64@gmail.com
 */
#ifdef _WIN32
#include <windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include "sl_glext.h"
#else
#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include <cstring>
#endif

#include "sl_draw.h"
#include "sl_texture.h"
#include "sl_primitivebuffer.h"
#include "stb_image.h"

SLTexture::SLTexture(const char *filename, bool clamped,bool mipmapped)
{
	pixel32 *pxd = (pixel32 *)stbi_load(filename, &width, &height, 0, 4);
	if (!pxd)
		return;
	pixeldata = new pixel32[width * height];
	memcpy(pixeldata, pxd, width * height * sizeof(pixel32));
	stbi_image_free((void *)pxd);
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
SLTexture::SLTexture(int32 width, int32 height,bool clamped, bool mipmapped)
	: width(width), height(height), mipmapped(mipmapped)
{
	pixeldata = new pixel32[width * height];
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
	glDeleteTextures(1, &glref);
}



SLTextureAtlas::SLTextureAtlas(SLPrimitiveBuffer *target, const char* filename, int32 numtiles_x, int32 numtiles_y,
	bool clamped,bool mipmapped )
	:target(target),numtiles_x(numtiles_x), numtiles_y(numtiles_y), valid(false), clamped(clamped), mipmapped(mipmapped)
{
	texture = new SLTexture(filename, clamped, mipmapped);
	tile_width = texture->width / numtiles_x;
	tile_height = texture->height / numtiles_y;
}

SLTextureAtlas::~SLTextureAtlas()
{
	delete texture;
}
void SLTextureAtlas::bind()
{
	sl_bind_texture(target,texture);
}
void SLTextureAtlas::draw_tile(int32 x1, int32 y1, int32 width, int32 height, int32 index, pixel32 colour )
{
	draw_tile((float32)x1, (float32)y1, (float32)width, (float32)height, index, colour);
}
void SLTextureAtlas::batch_draw_tile(int32 x1, int32 y1, int32 width, int32 height, int32 index, pixel32 colour)
{
	batch_draw_tile((float32)x1, (float32)y1, (float32)width, (float32)height, index, colour);
}
void SLTextureAtlas::draw_tile(float32 x1, float32 y1, float32 width, float32 height, int32 index, pixel32 colour)
{

	const float32 x2 = x1 + width;
	const float32 y2 = y1 + height;

	const int32 tile_x = index % (numtiles_x);
	const int32 tile_y = index / (numtiles_x);

	const float32 u1 = (float32)tile_width * (float32)tile_x / (float32)texture->width;
	const float32 v1 = (float32)tile_height * (float32)tile_y / (float32)texture->height;
	const float32 u_span = (float32)(tile_width) / (float32)texture->width;
	const float32 v_span = (float32)(tile_height) / (float32)texture->height;
	const float32 u2 = u1 + u_span;
	const float32 v2 = v1 + v_span;

	target->colour(colour);

	target->begin(GL_QUADS);
	target->texcoord0(vec2(u1, v1));
	target->vertex(vec2(x1, y1));

	target->texcoord0(vec2(u2, v1));
	target->vertex(vec2(x2, y1));

	target->texcoord0(vec2(u2, v2));
	target->vertex(vec2(x2, y2));

	target->texcoord0(vec2(u1, v2));
	target->vertex(vec2(x1, y2));
	target->end();
}
void SLTextureAtlas::batch_begin()
{
	target->begin(GL_QUADS);
}
void SLTextureAtlas::batch_draw_tile(float32 x1, float32 y1, float32 width, float32 height, int32 index, uint32 colour)
{
	const float32 x2 = x1 + width;
	const float32 y2 = y1 + height;

	const int32 tile_x = index % (numtiles_x);
	const int32 tile_y = index / (numtiles_x);

	const float32 u1 = (float32)tile_width * (float32)tile_x / (float32)texture->width;
	const float32 v1 = (float32)tile_height * (float32)tile_y / (float32)texture->height;
	const float32 u_span = (float32)(tile_width) / (float32)texture->width;
	const float32 v_span = (float32)(tile_height) / (float32)texture->height;
	const float32 u2 = u1 + u_span;
	const float32 v2 = v1 + v_span;

	target->colour(colour);

	target->texcoord0(vec2(u1, v1));
	target->vertex(vec2(x1, y1));

	target->texcoord0(vec2(u2, v1));
	target->vertex(vec2(x2, y1)); 

	target->texcoord0(vec2(u2, v2));
	target->vertex(vec2(x2, y2));

	target->texcoord0(vec2(u1, v2));
	target->vertex(vec2(x1, y2));
}
void SLTextureAtlas::batch_end()
{
	target->end();
}