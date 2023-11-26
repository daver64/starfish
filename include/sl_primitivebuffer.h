
/**
 * (c) 2023 David Rowbotham thedaver64@gmail.com
*/
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
#define GL_GLEXT_PROTOTYPES

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
	const vec3 get_vertex(int32 index);
	vec2 get_vertex2(int32 index);
	vec3 get_normal(int32 index);
	vec2 get_texcoord(int32 index, int32 texture_index=0);
	void colour(pixel32 c);
	void colour(float r, float g, float b, float a);
	//void colour(RGBAf c);
	void point(float x1, float y1, pixel32 colour);
	void line(float x1, float y1, float x2, float y2, pixel32 colour);
	void line(float x1, float y1, float x2, float y2, pixel32 colours[2]);
	void rect(float x1, float y1, float width, float height, pixel32 colour);
	void rect(float x1, float y1, float width, float height, pixel32 colours[4]);
	void circle(float x, float y, float radius, pixel32 colour, int32 numsegments);
	void ellipse(float x, float y, float width, float height, pixel32 ccolour, int32 numsegments);
	void triangle(float x1, float y1, float x2, float y2, float x3, float y3, pixel32 colours[3]);
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
	vec3* vertex_pointer(int32 index);
	vec3* normal_pointer(int32 index);
	vec4* colour_pointer(int32 index);
	vec2* texcoord0_pointer(int32 index);
	vec2* texcoord1_pointer(int32 index);
	vec2* texcoord2_pointer(int32 index);
	vec2* texcoord3_pointer(int32 index);
	void set_active_texture_unit(int32 unit);
	int32_t get_active_texture_unit();
	GLenum primitive;
	GLenum usage;
	vec3 current_vertex;
	vec3 current_normal;
	vec4 current_colour;
	vec2 current_texcoord0;
	vec2 current_texcoord1;
	vec2 current_texcoord2;
	vec2 current_texcoord3;

	GLuint vbo_id = 0;
	uint64 vert_offset = 0;
	uint64 norm_offset = 0;
	uint64 col_offset = 0;
	uint64 tex0_offset = 0;
	uint64 tex1_offset = 0;
	uint64 tex2_offset = 0;
	uint64 tex3_offset = 0;
	int32 active_texture_unit = 0;
	std::vector<vec3> vertices;
	std::vector<vec3> normals;
	std::vector<vec4> colours;
	std::vector<vec2> vtexcoord0;
	std::vector<vec2> vtexcoord1;
	std::vector<vec2> vtexcoord2;
	std::vector<vec2> vtexcoord3;

	void bind_tex0(int32 gl) { tex0_glref = gl; }
	void bind_tex1(int32 gl) { tex1_glref = gl; }
	void bind_tex2(int32 gl) { tex2_glref = gl; }
	void bind_tex3(int32 gl) { tex3_glref = gl; }

	int32 tex0_glref = 0;
	int32 tex1_glref = 0;
	int32 tex2_glref = 0;
	int32 tex3_glref = 0;
	vec2 offset2d;
	vec3 offset3d;
	bool vbo_deleted{ false };
};