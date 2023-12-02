/**
 * (c) 2023 David Rowbotham thedaver64@gmail.com
*/
#pragma once
#include "sl.h"

struct FrameBuffer
{
	int32_t width;
	int32_t height;
	uint32_t glref;
	uint32_t frame_id;
	uint32_t render_id;
	uint32_t depth_id;
	int32_t valid;
};
class SLFrameBuffer {
public:
#ifndef GL_RGBA
    SLFrameBuffer(int32 width,int32 height, GLenum format=0x1908);
#else
    SLFrameBuffer(int32 width,int32 height, GLenum format=GL_RGBA);
#endif
    ~SLFrameBuffer();
	void resize(int32 width, int32 height);
	void bind();
	void unbind();
	const int32 glref() const;
	void ortho();
	void clr();
	const int32 width() const;
	const int32 height() const;
	bool read_colour_data(std::vector<pixel32>& colour_data);
    FrameBuffer *fbo{nullptr};
    GLenum format;
};