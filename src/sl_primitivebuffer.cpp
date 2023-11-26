/**
 * (c) 2023 David Rowbotham thedaver64@gmail.com
*/

#include "sl_primitivebuffer.h"
#include <algorithm>
#include <functional>
#include <cmath>

PrimitiveBuffer::PrimitiveBuffer(GLenum primitive, GLenum usage) 
	:primitive(primitive), usage(usage)
{
	current_vertex = vec3{ 0.0f,0.0f,0.0f };
	current_normal = vec3{ 0.0f,1.0f,0.0f };
	current_colour = vec4{ 1.0f,1.0f,1.0f,1.0f };
	current_texcoord0 = vec2{ 0.0f,0.0f };
	current_texcoord1 = vec2{ 0.0f,0.0f };
	current_texcoord2 = vec2{ 0.0f,0.0f };
	current_texcoord3 = vec2{ 0.0f,0.0f };
	vbo_id = 0;
	vert_offset = 0;
	norm_offset = 0;
	col_offset = 0;
	tex0_offset = 0;
	tex1_offset = 0;
	tex2_offset = 0;
	tex3_offset = 0;
	offset2d = vec2(0.5f, 0.5f);
	offset3d=vec3(0.0f,0.0f,0.0f);
	vertices.reserve(64000);
	normals.reserve(64000);
	colours.reserve(64000);
	vtexcoord0.reserve(64000);
	vtexcoord1.reserve(64000);
	vtexcoord2.reserve(64000);
	vtexcoord3.reserve(64000);
	glGenBuffers(1, &vbo_id);
}
PrimitiveBuffer::~PrimitiveBuffer()
{
	if(!vbo_deleted)
		glDeleteBuffers(1, &vbo_id);
}
void PrimitiveBuffer::vertex(vec3 v)
{
	current_vertex = vec3{ v.x + offset3d.x ,v.y + offset3d.y, v.z + offset3d.z };
	vertices.emplace_back(current_vertex);
	colours.emplace_back(current_colour);
	normals.emplace_back(current_normal);
	vtexcoord0.emplace_back(current_texcoord0);
	vtexcoord1.emplace_back(current_texcoord1);
	vtexcoord2.emplace_back(current_texcoord2);
	vtexcoord3.emplace_back(current_texcoord3);
}
void PrimitiveBuffer::vertex(vec2 v)
{
	current_vertex = vec3{ v.x + offset2d.x, v.y + offset2d.y, 0.0f };
	vertices.emplace_back(current_vertex);
	colours.emplace_back(current_colour);
	normals.emplace_back(current_normal);
	vtexcoord0.emplace_back(current_texcoord0);
	vtexcoord1.emplace_back(current_texcoord1);
	vtexcoord2.emplace_back(current_texcoord2);
	vtexcoord3.emplace_back(current_texcoord3);
}
void PrimitiveBuffer::vertex(float x, float y, float z)
{
	vertex(vec3(x + offset3d.x,y + offset3d.y, z + offset3d.z));
}
void PrimitiveBuffer::normal(vec3 n)
{
	current_normal = vec3{ n.x,n.y,n.z };
}
void PrimitiveBuffer::normal(float nx, float ny, float nz)
{
	normal(vec3(nx,ny,nz));
}
void PrimitiveBuffer::set_active_texture_unit(int32 unit)
{
	active_texture_unit = clamp(unit, 0, 3);
}
int32_t PrimitiveBuffer::get_active_texture_unit()
{
	return active_texture_unit;
}
void PrimitiveBuffer::texcoord(vec2 t)
{
	switch (active_texture_unit)
	{
	case 0:
		texcoord0(t);
		break;
	case 1:
		texcoord1(t);
		break;
	case 2:
		texcoord2(t);
		break;
	case 3:
		texcoord3(t);
		break;
	default:
		texcoord0(t);
		break;
	}
}
void PrimitiveBuffer::texcoord(float_t u, float_t v)
{
	switch (active_texture_unit)
	{
	case 0:
		current_texcoord0 = vec2{ u,v };
		break;
	case 1:
		current_texcoord1 = vec2{ u,v };
		break;
	case 2:
		current_texcoord2 = vec2{ u,v };
		break;
	case 3:
		current_texcoord3 = vec2{ u,v };
		break;
	default:
		current_texcoord0 = vec2{ u,v };
		break;
	}
}
void PrimitiveBuffer::texcoord0(vec2 t)
{
	current_texcoord0 = vec2{ t.s,t.t };
}
void PrimitiveBuffer::texcoord1(vec2 t)
{
	current_texcoord1 = vec2{ t.s,t.t };
}
void PrimitiveBuffer::texcoord2(vec2 t)
{
	current_texcoord2 = vec2{ t.s,t.t };
}
void PrimitiveBuffer::texcoord3(vec2 t)
{
	current_texcoord3 = vec2{ t.s,t.t };
}
void PrimitiveBuffer::texcoord0(float u, float v)
{
	texcoord0(vec2(u, v));
}
void PrimitiveBuffer::texcoord1(float u, float v)
{
	texcoord1(vec2(u, v));
}
void PrimitiveBuffer::texcoord2(float u, float v)
{
	texcoord2(vec2(u, v));
}
void PrimitiveBuffer::texcoord3(float u, float v)
{
	texcoord3(vec2(u, v));
}
const vec3 PrimitiveBuffer::get_vertex(int32 index)
{
	return vec3(vertices[index].x, vertices[index].y, vertices[index].y);
}
vec2 PrimitiveBuffer::get_vertex2(int32 index)
{
	return vec2(vertices[index].x, vertices[index].y);
}
vec3 PrimitiveBuffer::get_normal(int32 index)
{
	return vec3(normals[index].x, normals[index].y, normals[index].z);
}
vec2 PrimitiveBuffer::get_texcoord(int32 index, int32 texture_index)
{
	vec2 result{ 0,0 };
	switch (texture_index)
	{
	case 0:
		result.x = vtexcoord0[index].x;
		result.y = vtexcoord0[index].y;
		break;
	case 1:
		result.x = vtexcoord1[index].x;
		result.y = vtexcoord1[index].y;
		break;
	case 2:
		result.x = vtexcoord2[index].x;
		result.y = vtexcoord2[index].y;
		break;
	case 3:
		result.x = vtexcoord3[index].x;
		result.y = vtexcoord3[index].y;
		break;
	}
	return result;
}
//void PrimitiveBuffer::colour(RGBAf c)
//{
//	current_colour.d[0] = c.d[0];
//	current_colour.d[1] = c.d[1];
//	current_colour.d[2] = c.d[2];
//	current_colour.d[3] = c.d[3];

//	current_colour.a = c.a;
//	current_colour.r = c.r;
//	current_colour.g = c.g;
//	current_colour.b = c.b;

//}
void PrimitiveBuffer::colour(pixel32 c)
{
	const float r = getr_nf(c);
	const float g = getg_nf(c);
	const float b = getb_nf(c);
	const float a = geta_nf(c);
	current_colour = vec4{ r,g,b,a };
	//current_colour.r = r;
	//current_colour.g = g;
	//current_colour.b = b;
	//current_colour.a = a;
}
void PrimitiveBuffer::colour(float r, float g, float b, float a)
{
	current_colour = vec4{ r,g,b,a };
	//current_colour.r = r;
	//current_colour.g = g;
	//current_colour.b = b;
	//current_colour.a = a;
}

void PrimitiveBuffer::point(float x1, float y1, pixel32 c)
{
	colour(c);
	vertex(vec2(x1 , y1 ));
}
void PrimitiveBuffer::line(float x1, float y1, float x2, float y2, pixel32 c)
{
	pixel32 colours[2]{ c,c };
	line(x1 , y1 , x2 , y2 , colours);
}
void PrimitiveBuffer::line(float x1, float y1, float x2, float y2, pixel32 colours[2])
{
	colour(colours[0]);
	vertex(vec2(x1 , y1 ));
	colour(colours[1]);
	vertex(vec2(x2 , y2 ));
}
void PrimitiveBuffer::rect(float x1, float y1, float width, float height, pixel32 c)
{
	pixel32 colours[4]{ c,c,c,c };
	rect(x1 , y1 , width, height, colours);
}

void PrimitiveBuffer::rect(float x1, float y1, float width, float height, pixel32 colours[4])
{
	float x2 = x1 + width;
	float y2 = y1 + height;

	texcoord(vec2(0, 0));
	colour(colours[0]);
	normal(vec3(0, 0, 1));
	vertex(vec2(x1 , y1 ));

	texcoord(vec2(1, 0));
	colour(colours[1]);
	normal(vec3(0, 0, 1));
	vertex(vec2(x2 , y1 ));


	texcoord(vec2(1, 1));
	colour(colours[2]);
	normal(vec3(0, 0, 1));
	vertex(vec2(x2 , y2 ));

	texcoord(vec2(0, 1));
	colour(colours[3]);
	normal(vec3(0, 0, 1));
	vertex(vec2(x1 , y2 ));

}
#ifndef PIf
#define PIf (3.1415926f)
#endif

void PrimitiveBuffer::circle(float x, float y, float radius, pixel32 ccolour, int32 numsegments)
{
	colour(ccolour);
	const float dth = PIf / numsegments;
	if (primitive == GL_LINES)
	{
		for (float theta = 0; theta <= 2.0f * PIf; theta += dth)
		{
			const float x1 = (x + radius * cosf(theta));
			const float y1 = (y + radius * sinf(theta));
			theta += dth;
			const float x2 = (x + radius * cosf(theta));
			const float y2 = (y + radius * sinf(theta));
			vertex(vec2(x1 , y1 ));
			vertex(vec2(x2 , y2 ));
			theta -= dth;
		}
	}
	else if (primitive == GL_TRIANGLES)
	{
		colour(ccolour);
		for (float theta = 0; theta <= 2.0f * PIf; theta += dth)
		{
			const float x1 = (x + radius * cosf(theta));
			const float y1 = (y + radius * sinf(theta));
			const float last_theta = theta;
			theta += dth;
			const float x2 = (x + radius * cosf(theta));
			const float y2 = (y + radius * sinf(theta));
			vertex(vec2(x2 , y2 ));
			vertex(vec2(x1 , y1 ));
			vertex(vec2(x , y ));
			theta = last_theta;
		}
	}
}
void PrimitiveBuffer::ellipse(float x, float y, float width, float height, uint32 ccolour, int32 numsegments)
{
	colour(ccolour);
	if (primitive == GL_LINES)
	{
		for (float theta = 0.0f; theta < (2.0f * PIf); theta += (PIf / (float)numsegments))
		{
			const float x1 = width * cosf(theta) + x;
			const float y1 = height * sinf(theta) + y;
			const float x2 = width * cosf(theta + (PIf / (float)numsegments)) + x;
			const float y2 = height * sinf(theta + (PIf / (float)numsegments)) + y;
			vertex(vec2(x1 , y1 ));
			vertex(vec2(x2 , y2 ));
		}
	}
	else if (primitive == GL_TRIANGLES)
	{
		for (float theta = 0.0f; theta < (2.0f * PIf); theta += (PIf / (float)numsegments))
		{
			const float x1 = width * cosf(theta) + x;
			const float y1 = height * sinf(theta) + y;
			const float x2 = width * cosf(theta + (PIf / (float)numsegments)) + x;
			const float y2 = height * sinf(theta + (PIf / (float)numsegments)) + y;
			vertex(vec2(x2 , y2 ));
			vertex(vec2(x1 , y1 ));
			vertex(vec2(x , y ));
		}
	}
}
void PrimitiveBuffer::triangle(float x1, float y1, float x2, float y2, float x3, float y3, uint32 colours[3])
{
	colour(colours[0]);
	vertex(vec2(x1 , y1 ));
	colour(colours[1]);
	vertex(vec2(x2 , y2 ));
	colour(colours[2]);
	vertex(vec2(x3 , y3 ));
}
void PrimitiveBuffer::quad(vec3 p1, vec3 p2, vec3 p3, vec3 p4)
{
	texcoord0(vec2(0.0f, 0.0f));
	vertex(p1);
	texcoord0(vec2(1.0f, 0.0f));
	vertex(p2);
	texcoord0(vec2(1.0f, 1.0f));
	vertex(p3);
	texcoord0(vec2(0.0f, 1.0f));
	vertex(p4);
}
void PrimitiveBuffer::quadratic_bezier(vec2 startpos, vec2 controlpos, vec2 endpos, int32_t numseg)
{
	/*std::vector<vec2> plotresult;
	quadratic_plot(startpos, controlpos, endpos, plotresult, numseg);
	for (size_t i = 1; i < numseg; i++)
	{
		const vec2 v1 = plotresult[i - 1];
		vertex(v1);
		const vec2 v2 = plotresult[i];
		vertex(v2);
	}*/
}
 
void PrimitiveBuffer::draw_sphere_patch(float slon, float slat,
	float elon, float elat,
	int32 subdivide, int32 ysubdivide,
	float radius, float texture_width, float texture_height)
{
/*	float_t lon, lat;
	vec3 vert;
	vec3 norm;
	float_t u, v;

	if (!ysubdivide)
		ysubdivide = subdivide;

	for (int32_t patch_y = 0; patch_y < ysubdivide; patch_y++)
	{
		for (int32_t x = 0; x <= subdivide; x++)
		{
			for (int32_t y = patch_y; y <= patch_y + 1; y++)
			{
				lon = slon + ((elon - slon) / subdivide) * x;
				lat = slat + ((elat - slat) / ysubdivide) * y;
				u = (float_t)x / (float_t)subdivide;
				v = (float_t)y / (float_t)ysubdivide;
				float_t tu, tv;
				get_patch((float_t)lon, (float_t)lat, &tu, &tv, texture_width, texture_height);
				Polar<float_t> pol(degtorad(lon),degtorad(lat), radius);
				vert = pol.to_cartesian();
				norm = vert;
				norm.normalise();

				vertex(vert);
				normal(norm);
				texcoord(vec2(u, v));

			}
		}
	}
	draw();
    */
}
void PrimitiveBuffer::sphere(float radius, float texture_width, float texture_height)
{
	int32_t nslice = 128;
	draw_sphere_patch(-179.995, -89.995, 179.995, 89.995, nslice, nslice / 2, radius, texture_width, texture_height);
}
 
/*std::vector<Line3<float_t> > GLPrimitiveBuffer::get_lines()
{
	std::vector<Line3<float_t>> lines;
	size_t numvert = vertices.size();
	for (size_t i1 = 0; i1 < numvert; i1++)
	{
		size_t i2 = (i1 + 1) % numvert;
		Line3<float_t> l(get_vertex((int32_t)i1), get_vertex((int32_t)i2));
		lines.emplace_back(l);
	}
	return lines;
}*/
void PrimitiveBuffer::alphasort()
{//
	//std::sort(std::begin(colours), std::end(colours), [](vec4 a, vec4 b) {return a.a > b.a; });
}


void PrimitiveBuffer::build()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	const GLsizei vert_size = (GLsizei)(sizeof(vec3) * vertices.size());
	const GLsizei norm_size = (GLsizei)(sizeof(vec3) * normals.size());
	const GLsizei col_size = (GLsizei)(sizeof(vec4) * colours.size());
	const GLsizei tex0_coord_size = (GLsizei)(sizeof(vec2) * vtexcoord0.size());
	const GLsizei tex1_coord_size =(GLsizei)(sizeof(vec2) * vtexcoord1.size());
	const GLsizei tex2_coord_size = 0;// (GLsizei)(sizeof(vec2) * vtexcoord2.size());
	const GLsizei tex3_coord_size = 0;// (GLsizei)(sizeof(vec2) * vtexcoord3.size());

	vert_offset = 0;
	norm_offset = vert_offset + vert_size;
	col_offset = norm_offset + norm_size;
	tex0_offset = col_offset + col_size;
	tex1_offset = tex0_offset + tex0_coord_size;
	tex2_offset = tex1_offset + tex1_coord_size;
	tex3_offset = tex2_offset + tex2_coord_size;

	glBufferData(GL_ARRAY_BUFFER, vert_size + norm_size + col_size + tex0_coord_size
		+ tex1_coord_size + tex2_coord_size + tex3_coord_size, 0, usage);
	if (vert_size)
		glBufferSubData(GL_ARRAY_BUFFER, (GLint)vert_offset, vert_size, &vertices[0]);
	if (norm_size)
		glBufferSubData(GL_ARRAY_BUFFER, (GLint)norm_offset, norm_size, &normals[0]);
	if (col_size)
		glBufferSubData(GL_ARRAY_BUFFER, (GLint)col_offset, col_size, &colours[0]);

	//gl_bind_texture_to_unit(tex0_glref,0);
	if (tex0_glref > 0)
	{
		glActiveTexture(GL_TEXTURE0);
		glClientActiveTexture(GL_TEXTURE0);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		if (tex0_coord_size)
			glBufferSubData(GL_ARRAY_BUFFER, (GLint)tex0_offset, tex0_coord_size, &vtexcoord0[0]);
	}


	//gl_bind_texture_to_unit(tex1_glref,1);
	if (tex1_glref > 0)
	{
		glActiveTexture(GL_TEXTURE0 + 1);
		glClientActiveTexture(GL_TEXTURE0 + 1);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		if (tex1_coord_size)
			glBufferSubData(GL_ARRAY_BUFFER, (GLint)tex1_offset, tex1_coord_size, &vtexcoord1[0]);
	}
	//gl_bind_texture_to_unit(tex2_glref,2);
	//glActiveTexture(GL_TEXTURE0 + 2);
	//glClientActiveTexture(GL_TEXTURE0 + 2);
	//if (tex2_coord_size)
	//	glBufferSubData(GL_ARRAY_BUFFER, (GLint)tex2_offset, tex2_coord_size, &vtexcoord2[0]);

	//gl_bind_texture_to_unit(tex3_glref,3);
	//glActiveTexture(GL_TEXTURE0 + 3);
	//glClientActiveTexture(GL_TEXTURE0 + 3);
	//if (tex3_coord_size)
	//	glBufferSubData(GL_ARRAY_BUFFER, (GLint)tex3_offset, tex3_coord_size, &vtexcoord3[0]);
	//glActiveTexture(GL_TEXTURE0);
	//glClientActiveTexture(GL_TEXTURE0);

}
void PrimitiveBuffer::draw()
{
	if (usage != GL_STATIC_DRAW)
		build();
	const GLsizei vert_size = (GLsizei)(sizeof(vec3) * vertices.size());
	const GLsizei norm_size = (GLsizei)(sizeof(vec3) * normals.size());
	const GLsizei col_size = (GLsizei)(sizeof(vec4) * colours.size());
	const GLsizei tex0_coord_size = (GLsizei)(sizeof(vec2) * vtexcoord0.size());
	const GLsizei tex1_coord_size = (GLsizei)(sizeof(vec2) * vtexcoord1.size());
	const GLsizei tex2_coord_size = 0;// (GLsizei)(sizeof(vec2) * vtexcoord2.size());
	const GLsizei tex3_coord_size = 0;// (GLsizei)(sizeof(vec2) * vtexcoord3.size());

	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	if (vert_size)
		glVertexPointer(3, GL_FLOAT, 0, (void*)vert_offset);
	if (norm_size)
		glNormalPointer(GL_FLOAT, 0, (void*)norm_offset);
	if (col_size)
		glColorPointer(4, GL_FLOAT, 0, (void*)col_offset);


	bool textured = false;
	if (tex0_glref > 0)
	{
		//gl_enable_texturing();
		//gl_bind_texture_to_unit(tex0_glref, 0);

		glActiveTexture(GL_TEXTURE0);
		glClientActiveTexture(GL_TEXTURE0);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		if (tex0_coord_size)
			glTexCoordPointer(2, GL_FLOAT, 0, (void*)tex0_offset);
		textured = true;
	}

	if (tex1_glref > 0)
	{
		//gl_enable_texturing();
		//gl_bind_texture_to_unit(tex1_glref, 1);

		glActiveTexture(GL_TEXTURE0 + 1);
		glClientActiveTexture(GL_TEXTURE0 + 1);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		if (tex1_coord_size)
			glTexCoordPointer(2, GL_FLOAT, 0, (void*)tex1_offset);
		textured = true;
	}


	if (!textured)
	{
		//gl_disable_texturing();
	}
	else
	{
		//gl_enable_texturing();
	}


	//gl_enable_arrays();
	glDrawArrays(primitive, 0, (GLsizei)vertices.size());
	//gl_disable_arrays();

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (usage != GL_STATIC_DRAW)
		reset();

	//gl_bind_texture_to_unit(0, 0);
	//gl_bind_texture_to_unit(0, 1);

	glActiveTexture(GL_TEXTURE0);
	glClientActiveTexture(GL_TEXTURE0);

}
void PrimitiveBuffer::reset()
{
	vertices.clear();
	normals.clear();
	vtexcoord0.clear();
	vtexcoord1.clear();
	vtexcoord2.clear();
	vtexcoord3.clear();
	colours.clear();
}
void PrimitiveBuffer::begin(GLenum type)
{
	primitive = type;
}

void PrimitiveBuffer::end()
{
	if (usage != GL_STATIC_DRAW)
		draw();
}

vec3* PrimitiveBuffer::vertex_pointer(int32 index)
{
	if (index < vertices.size())
		return &vertices[index];
	return NULL;
}
vec3* PrimitiveBuffer::normal_pointer(int32 index)
{
	if (index < normals.size())
		return &normals[index];
	return NULL;
}
vec4* PrimitiveBuffer::colour_pointer(int32 index)
{
	if (index < colours.size())
		return &colours[index];
	return NULL;
}
vec2* PrimitiveBuffer::texcoord0_pointer(int32 index)
{
	if (index < vtexcoord0.size())
		return &vtexcoord0[index];
	return NULL;
}
vec2* PrimitiveBuffer::texcoord1_pointer(int32 index)
{
	if (index < vtexcoord1.size())
		return &vtexcoord1[index];
	return NULL;
}
vec2* PrimitiveBuffer::texcoord2_pointer(int32 index)
{
	if (index < vtexcoord2.size())
		return &vtexcoord2[index];
	return NULL;
}
vec2* PrimitiveBuffer::texcoord3_pointer(int32 index)
{
	if (index < vtexcoord3.size())
		return &vtexcoord3[index];
	return NULL;
}
