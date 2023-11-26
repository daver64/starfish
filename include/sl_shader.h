/**
 * (c) 2023 David Rowbotham thedaver64@gmail.com
*/
#pragma once
#include "sl.h"

class SLShader {
public:
	SLShader(const char* vertex_file = NULL, const char* fragment_file = NULL, const char* geometry_file = NULL);
	~SLShader();
	bool load_from_string(const char* vertex_src, const char* fragment_src, const char* geometry_src = NULL);
	bool load_from_file(const char* vertex_file, const char* fragment_file, const char* geometry_file = NULL);

	void bind();
	void unbind();
	void set_uniform_int(const char* name, int32 v);
	void set_uniform_float(const char* name, float32 v);
	void set_uniform_vec2(const char* name, vec2 v);
	void set_uniform_vec3(const char* name, vec3 v);
	void set_uniform_matrix(const char* name, mat4x4 v);

	uint32 program{0};
	uint32 geometry{0};
	uint32 vertex{0};
	uint32 fragment{0};
};