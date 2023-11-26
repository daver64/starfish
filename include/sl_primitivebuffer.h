#pragma once
#include "sl.h"
#ifdef _WIN32
#include <windows.h>
#undef max
#undef min
#include <GL/GL.h>
#include <GL/GLU.h>
#include "sl_glext.h"
#else
#include <GL/gl.h>
#include <GL/glext.h>
#endif

#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
class PrimitiveBuffer {
public:
	PrimitiveBuffer(GLenum primitive = GL_TRIANGLES, GLenum usage = GL_DYNAMIC_DRAW);
	~PrimitiveBuffer();
	void vertex(vec3 v);
	void vertex(vec2 v);
	void vertex(float x, float y, float z);
	void normal(vec3 n);
	void normal(float nx, float ny, float nz);
	void texcoord(vec2 t);
	void texcoord(float u, float v);
	void texcoord0(vec2 t);
	void texcoord1(vec2 t);
	void texcoord2(vec2 t);
	void texcoord3(vec2 t);
	void texcoord0(float u, float v);
	void texcoord1(float u, float v);
	void texcoord2(float u, float v);
	void texcoord3(float u, float v);
	const vec3 get_vertex(int32_t index);
	vec2 get_vertex2(int32_t index);
	vec3 get_normal(int32_t index);
	vec2 get_texcoord(int32_t index, int32_t texture_index=0);
	void colour(uint32_t c);
	void colour(float r, float g, float b, float a);
	//void colour(RGBAf c);
	void point(float x1, float y1, uint32_t colour);
	void line(float x1, float y1, float x2, float y2, uint32_t colour);
	void line(float x1, float y1, float x2, float y2, uint32_t colours[2]);
	void rect(float x1, float y1, float width, float height, uint32_t colour);
	void rect(float x1, float y1, float width, float height, uint32_t colours[4]);
	void circle(float x, float y, float radius, uint32_t colour, int32_t numsegments);
	void ellipse(float x, float y, float width, float height, uint32_t ccolour, int32_t numsegments);
	void triangle(float x1, float y1, float x2, float y2, float x3, float y3, uint32_t colours[3]);
	void quad(vec3 p1, vec3 p2, vec3 p3, vec3 p4);
	void quadratic_bezier(vec2 startpos, vec2 controlpos, vec2 endpos, int32_t numseg);
	void draw_sphere_patch(float slon, float slat,
		float elon, float elat,
		int subdivide, int ysubdivide,
		float radius, float texture_width, float texture_height);
	void sphere(float radius, float texture_width, float texture_height);
	//std::vector<Line3<float> > get_lines();
	void alphasort();
	void build();
	void draw();
	void reset();
	void begin(GLenum type);
	void end();
	vec3* vertex_pointer(int32_t index);
	vec3* normal_pointer(int32_t index);
	vec4* colour_pointer(int32_t index);
	vec2* texcoord0_pointer(int32_t index);
	vec2* texcoord1_pointer(int32_t index);
	vec2* texcoord2_pointer(int32_t index);
	vec2* texcoord3_pointer(int32_t index);
	void set_active_texture_unit(int32_t unit);
	int32_t get_active_texture_unit();
	GLenum primitive;
	GLenum usage;
	vec3 current_vertex;
	vec3 current_normal;
	vec3 current_colour;
	vec3 current_texcoord0;
	vec3 current_texcoord1;
	vec3 current_texcoord2;
	vec3 current_texcoord3;

	GLuint vbo_id = 0;
	uint64_t vert_offset = 0;
	uint64_t norm_offset = 0;
	uint64_t col_offset = 0;
	uint64_t tex0_offset = 0;
	uint64_t tex1_offset = 0;
	uint64_t tex2_offset = 0;
	uint64_t tex3_offset = 0;
	int32_t active_texture_unit = 0;
	std::vector<vec3> vertices;
	std::vector<vec3> normals;
	std::vector<vec4> colours;
	std::vector<vec2> vtexcoord0;
	std::vector<vec2> vtexcoord1;
	std::vector<vec2> vtexcoord2;
	std::vector<vec2> vtexcoord3;

	void bind_tex0(int32_t gl) { tex0_glref = gl; }
	void bind_tex1(int32_t gl) { tex1_glref = gl; }
	void bind_tex2(int32_t gl) { tex2_glref = gl; }
	void bind_tex3(int32_t gl) { tex3_glref = gl; }

	int32_t tex0_glref = 0;
	int32_t tex1_glref = 0;
	int32_t tex2_glref = 0;
	int32_t tex3_glref = 0;
	vec2 offset2d;
	vec3 offset3d;
	bool vbo_deleted{ false };
};