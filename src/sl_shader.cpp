/**
 * (c) 2023 David Rowbotham thedaver64@gmail.com
*/
#include "sl.h"
#ifdef _WIN32
#include <windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include "sl_glext.h"
#else
#include <GL/gl.h>
#include <GL/glext.h>
#include <cstring>
#endif
#include "sl_shader.h"

SLShader::SLShader(const char *vertex_file, const char *fragment_file, const char *geometry_file)
{
    
}
SLShader::~SLShader()
{
    
}
bool SLShader::load_from_string(const char *vertex_src, const char *fragment_src, const char *geometry_src)
{
    return false;
}
bool SLShader::load_from_file(const char *vertex_file, const char *fragment_file, const char *geometry_file)
{
    return false;   
}

void SLShader::bind()
{
    
}
void SLShader::unbind()
{
    
}

void SLShader::set_uniform_int(const char *name, int32 v)
{
    
}
void SLShader::set_uniform_float(const char *name, float32 v)
{
    
}
void SLShader::set_uniform_vec2(const char *name, vec2 v)
{
    
}
void SLShader::set_uniform_vec3(const char *name, vec3 v)
{
    
}
void SLShader::set_uniform_matrix(const char *name, mat4x4 v)
{

}