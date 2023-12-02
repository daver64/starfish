/**
 * (c) 2023 David Rowbotham thedaver64@gmail.com
*/
#include "sl.h"
#include "sl_draw.h"
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
#include "sl_framebuffer.h"


FrameBuffer* gl_create_fp_framebuffer(int32_t width, int32_t height)
{
	FrameBuffer* fbo = (FrameBuffer*)malloc(sizeof(FrameBuffer));
	//log_printf("gl_create_fp_framebuffer()1a glerror=%s\n", gl_geterror());
	//log_printf( "Create Floating Point Framebuffer\n");
	 
	fbo->width = width;
	fbo->height = height;
	glEnable(GL_TEXTURE_2D);


	glGenTextures(1, &fbo->glref);
	//log_printf("gl_create_fp_framebuffer()1b glerror=%s\n", gl_geterror());
	//log_printf( "Bind Texture\n");
	// 
	glBindTexture(GL_TEXTURE_2D, fbo->glref);
	//log_printf("gl_create_fp_framebuffer()1c glerror=%s\n", gl_geterror());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//log_printf("gl_create_fp_framebuffer()1d glerror=%s\n", gl_geterror());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//log_printf("gl_create_fp_framebuffer()1e glerror=%s\n", gl_geterror());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//log_printf("gl_create_fp_framebuffer()1f glerror=%s\n", gl_geterror());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//log_printf("gl_create_fp_framebuffer()1g glerror=%s\n", gl_geterror());
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	//log_printf("gl_create_fp_framebuffer()1h glerror=%s\n", gl_geterror());
	//log_printf( "TexImage2D\n");
	// 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, fbo->width, fbo->height, 0, GL_RGBA, GL_FLOAT, 0);
	//log_printf("gl_create_fp_framebuffer()1i glerror=%s\n", gl_geterror());
	glBindTexture(GL_TEXTURE_2D, 0);
	//log_printf("gl_create_fp_framebuffer()1j glerror=%s\n", gl_geterror());

	//log_printf( "glGenRenderbuffers %d x %d\n", fbo->width, fbo->height);
	// 
	uint32_t id = 0;
	glGenRenderbuffers(1, &id);
	//log_printf("gl_create_fp_framebuffer()1k glerror=%s\n", gl_geterror());
	fbo->render_id = id;
	//log_printf( "Bind Render Buffer\n");
	// 
	glBindRenderbuffer(GL_RENDERBUFFER, fbo->render_id);
	//log_printf("gl_create_fp_framebuffer()1l glerror=%s\n", gl_geterror());
	//log_printf( "RenderbufferStorage Depth\n");
	// 
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, fbo->width, fbo->height);
	//log_printf("gl_create_fp_framebuffer()1m glerror=%s\n", gl_geterror());
	//log_printf( "unbind renderbffer\n");
	// 
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	//log_printf("gl_create_fp_framebuffer()1n glerror=%s\n", gl_geterror());
	//log_printf( "GenFrameBuffers\n");
	// 
	glGenFramebuffers(1, &fbo->frame_id);
	//log_printf("gl_create_fp_framebuffer()1o glerror=%s\n", gl_geterror());
	glBindFramebuffer(GL_FRAMEBUFFER, fbo->frame_id);
	//log_printf("gl_create_fp_framebuffer()1p glerror=%s\n", gl_geterror());
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo->glref, 0);
	//log_printf("gl_create_fp_framebuffer()1q glerror=%s\n", gl_geterror());
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, fbo->frame_id);
	//log_printf("gl_create_fp_framebuffer()1r glerror=%s\n", gl_geterror());
	fbo->valid = (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
	//if (!fbo->valid)
	//{
	//	log_printf("VBO not valid!\n");
	//}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//log_printf("gl_create_fp_framebuffer()1s glerror=%s\n", gl_geterror());
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	//log_printf("gl_create_fp_framebuffer()1t glerror=%s\n", gl_geterror());
	//log_printf( "made fbo ok\n");
	 
	return fbo;
}
FrameBuffer* gl_create_framebuffer(int32_t width, int32_t height)
{
	FrameBuffer* fbo = (FrameBuffer*)malloc(sizeof(FrameBuffer));

	//log_printf( "Create ARGB Framebuffer\n");
	//log_printf("gl_create_framebuffer()1a glerror=%s\n", gl_geterror());
	fbo->width = width;
	fbo->height = height;
	glEnable(GL_TEXTURE_2D);
	//log_printf("gl_create_framebuffer()1b glerror=%s\n", gl_geterror());

	glGenTextures(1, &fbo->glref);
	//log_printf("gl_create_framebuffer()1c glerror=%s\n", gl_geterror());
	glBindTexture(GL_TEXTURE_2D, fbo->glref);
	//log_printf("gl_create_framebuffer()1d glerror=%s\n", gl_geterror());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//log_printf("gl_create_framebuffer()1e glerror=%s\n", gl_geterror());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//log_printf("gl_create_framebuffer()1f glerror=%s\n", gl_geterror());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//log_printf("gl_create_framebuffer()1g glerror=%s\n", gl_geterror());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//log_printf("gl_create_framebuffer()1h glerror=%s\n", gl_geterror());
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	//log_printf("gl_create_framebuffer()1i glerror=%s\n", gl_geterror());
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, fbo->width, fbo->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	//log_printf("gl_create_framebuffer()1j glerror=%s\n", gl_geterror());
	glBindTexture(GL_TEXTURE_2D, 0);
	//log_printf("gl_create_framebuffer()1k glerror=%s\n", gl_geterror());
	glGenRenderbuffers(1, &fbo->render_id);
	//log_printf("gl_create_framebuffer()1l glerror=%s\n", gl_geterror());
	glBindRenderbuffer(GL_RENDERBUFFER, fbo->render_id);
	//log_printf("gl_create_framebuffer()1m glerror=%s\n", gl_geterror());
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, fbo->width, fbo->height);
	//log_printf("gl_create_framebuffer()1n glerror=%s\n", gl_geterror());
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	//log_printf("gl_create_framebuffer()1o glerror=%s\n", gl_geterror());
	glGenFramebuffers(1, &fbo->frame_id);
	//log_printf("gl_create_framebuffer()1p glerror=%s\n", gl_geterror());
	glBindFramebuffer(GL_FRAMEBUFFER, fbo->frame_id);
	//log_printf("gl_create_framebuffer()1q glerror=%s\n", gl_geterror());
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo->glref, 0);
	//log_printf("gl_create_framebuffer()1r glerror=%s\n", gl_geterror());
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, fbo->frame_id);
	//log_printf("gl_create_framebuffer()1s glerror=%s\n", gl_geterror());
	fbo->valid = (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
	//if (!fbo->valid)
	//{
	//	log_printf("INVALID FBO %s\n", gl_geterror());
	//}
	//else
	//{
	//	log_printf("VALID FBO %s\n", gl_geterror());
	//}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	//log_printf( "made fbo ok\n");
	 
	return fbo;
}
void gl_destroy_framebuffer(FrameBuffer* fbo)
{
	glDeleteFramebuffers(1, &fbo->frame_id);
	glDeleteFramebuffers(1, &fbo->render_id);
	free(fbo);
}
void gl_bind_framebuffer(FrameBuffer* fbo)
{
	glPushAttrib(GL_VIEWPORT_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo->frame_id);
	glBindRenderbuffer(GL_RENDERBUFFER, fbo->render_id);
	glViewport(0, 0, fbo->width, fbo->height);
}
void gl_unbind_framebuffer(FrameBuffer* fbo)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glPopAttrib();
}


SLFrameBuffer::SLFrameBuffer(int32 width, int32 height, GLenum format)
	:format(format)
{
	
	if (format == GL_RGBA)
		fbo = gl_create_framebuffer(width, height);
	else if (format == GL_RGBA32F)
		fbo = gl_create_fp_framebuffer(width, height);
	else
		fbo = nullptr;

	//if (!fbo)
	//{
	//	log_printf("INVALID NULL FBO\n");
	//}
}
SLFrameBuffer::~SLFrameBuffer()
{
	if (fbo)
	{
		//gl_unbind_framebuffer(fbo);
		gl_destroy_framebuffer(fbo);
		fbo = nullptr;
	}
}
void SLFrameBuffer::resize(int32_t width, int32_t height)
{
	if (fbo)
	{
		gl_unbind_framebuffer(fbo);
		gl_destroy_framebuffer(fbo);
		if (format == GL_RGBA)
			fbo = gl_create_framebuffer(width, height);
		else if (format == GL_RGBA32F)
			fbo = gl_create_fp_framebuffer(width, height);
		else
			fbo = nullptr;
	}
}
void SLFrameBuffer::bind()
{
	if (fbo)
	{
		gl_bind_framebuffer(fbo);
	}
}
void SLFrameBuffer::unbind()
{
	if (fbo)
	{
		gl_unbind_framebuffer(fbo);
	}
}
const int32_t SLFrameBuffer::glref() const
{
	if (fbo)
	{
		return fbo->glref;
	}
	return 0;
}
void SLFrameBuffer::ortho()
{
	if (fbo)
	{
		bind();
		sl_ortho(fbo->width, fbo->height, TRUE);
	}
}
void SLFrameBuffer::clr()
{
	if (fbo)
	{
		bind();
		sl_clrscr(nullptr);
		unbind();
	}
}

const int32_t SLFrameBuffer::width() const
{
	if (fbo)
	{
		return fbo->width;
	}
	return 0;
}
const int32_t SLFrameBuffer::height() const
{
	if (fbo)
	{
		return fbo->height;
	}
	return 0;
}
bool SLFrameBuffer::read_colour_data(std::vector<uint32_t>& colour_data)
{
	if (format != GL_RGBA || !fbo)
		return false;
	const int32_t w = width();
	const int32_t h = height();
	const int32_t len = w * h * 4;
	if (colour_data.size() < len)
		colour_data.resize(len);

	//gl_read_texture(w, h, (void*)&colour_data[0], glref(), GL_RGBA);

	return true;
}