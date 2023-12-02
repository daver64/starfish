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

#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include <cstring>
#endif

#include "sl_shader.h"

Shader *gl_create_shader(const char *vertex_file, const char *fragment_file, const char *geometry_file)
{
    Shader *shader = NULL;

    // geometry shader is optional, vertex and fragment shaders are not.
    if (!vertex_file || !fragment_file)
        return shader;

    char *infobuffer = NULL;
    shader = (Shader *)malloc(sizeof(Shader));
    shader->program = 0;
    shader->vertex = 0;
    shader->fragment = 0;
    shader->geometry = 0;

    int32_t vert_bytes = 0;
    int32_t frag_bytes = 0;
    int32_t geom_bytes = 0;
    int32_t success = 0;
    int32_t buflen = 0;
    int32_t infolen = 0;
    int32_t p_vert_lines = 0;
    int32_t p_frag_lines = 0;
    int32_t p_geom_lines = 0;
    char *vertex_source = NULL;
    char *fragment_source = NULL;
    char *geometry_source = NULL;
    char **vertex_source_lines = NULL;
    char **fragment_source_lines = NULL;
    char **geometry_source_lines = NULL;

    // load shader sources
    vertex_source = load_text_file(vertex_file, vert_bytes);
    fragment_source = load_text_file(fragment_file, frag_bytes);
    p_vert_lines = string_split_c(vertex_source, '\n', &vertex_source_lines);
    p_frag_lines = string_split_c(fragment_source, '\n', &fragment_source_lines);
    if (geometry_file)
    {
        geometry_source = load_text_file(geometry_file, geom_bytes);
        p_geom_lines = string_split_c(geometry_source, '\n', &geometry_source_lines);
    }

    // compile vertex shader
    shader->vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader->vertex, p_vert_lines, (const char **)vertex_source_lines, 0);
    glCompileShader(shader->vertex);

    glGetShaderiv(shader->vertex, GL_COMPILE_STATUS, &success);
    glGetShaderiv(shader->vertex, GL_INFO_LOG_LENGTH, &buflen);
    infobuffer = (char *)malloc(buflen + 1);
    glGetShaderInfoLog(shader->vertex, buflen, &infolen, infobuffer);

    // if (!success)
    //	log_printf( "Vertex Shader Compile Error:%s\n%s",vertex_file, infobuffer);
    /// else
    //	log_printf( "Vertex Shader Compile OK:%s\n",vertex_file);

    // compile fragment shader
    shader->fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader->fragment, p_frag_lines, (const char **)fragment_source_lines, 0);
    glCompileShader(shader->fragment);
    glGetShaderiv(shader->fragment, GL_COMPILE_STATUS, &success);
    glGetShaderiv(shader->fragment, GL_INFO_LOG_LENGTH, &buflen);
    free(infobuffer);
    infobuffer = (char *)malloc(buflen + 1);
    glGetShaderInfoLog(shader->fragment, buflen, &infolen, infobuffer);

    // if (!success)
    //	log_printf( "Fragment Shader Compile Error:%s\n%s",fragment_file, infobuffer);
    // else
    //	log_printf( "Fragment Shader Compile OK:%s\n",fragment_file);

    // compile geometry shader if supplied
    if (geometry_file)
    {
        shader->geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(shader->geometry, 1, (const char **)geometry_source_lines, NULL);
        glCompileShader(shader->geometry);
        glGetShaderiv(shader->geometry, GL_COMPILE_STATUS, &success);
        glGetShaderiv(shader->geometry, GL_INFO_LOG_LENGTH, &buflen);
        free(infobuffer);
        infobuffer = (char *)malloc(buflen + 1);
        glGetShaderInfoLog(shader->geometry, buflen, &infolen, infobuffer);

        // if (!success)
        //	log_printf( "Geometry Shader Compile Error:%s\n%s",geometry_file, infobuffer);
        // else
        //	log_printf( "Geometry Shader Compile OK:%s\n",geometry_file);
    }

    // link shader programs
    shader->program = glCreateProgram();
    glAttachShader(shader->program, shader->fragment);
    glAttachShader(shader->program, shader->vertex);
    if (geometry_file)
        glAttachShader(shader->program, shader->geometry);
    glLinkProgram(shader->program);

    // clean up
    for (int32_t i = 0; i < p_vert_lines; i++)
    {
        free(vertex_source_lines[i]);
    }
    for (int32_t i = 0; i < p_frag_lines; i++)
    {
        free(fragment_source_lines[i]);
    }
    for (int32_t i = 0; i < p_geom_lines; i++)
    {
        free(geometry_source_lines[i]);
    }
    return shader;
}
Shader *gl_create_shader_ex(const char *vertex_source, const char *fragment_source, const char *geometry_source)
{
    Shader *shader = NULL;

    // geometry shader is optional, vertex and fragment shaders are not.
    if (!vertex_source || !fragment_source)
        return shader;

    char *infobuffer = NULL;
    shader = (Shader *)malloc(sizeof(Shader));
    shader->program = 0;
    shader->vertex = 0;
    shader->fragment = 0;
    shader->geometry = 0;

    int32_t vert_bytes = 0;
    int32_t frag_bytes = 0;
    int32_t geom_bytes = 0;
    int32_t success = 0;
    int32_t buflen = 0;
    int32_t infolen = 0;
    int32_t p_vert_lines = 0;
    int32_t p_frag_lines = 0;
    int32_t p_geom_lines = 0;
    char **vertex_source_lines = NULL;
    char **fragment_source_lines = NULL;
    char **geometry_source_lines = NULL;

    // load shader sources
    p_vert_lines = string_split_c(vertex_source, '\n', &vertex_source_lines);
    p_frag_lines = string_split_c(fragment_source, '\n', &fragment_source_lines);

    // compile vertex shader
    shader->vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader->vertex, p_vert_lines, (const char **)vertex_source_lines, 0);
    glCompileShader(shader->vertex);

    glGetShaderiv(shader->vertex, GL_COMPILE_STATUS, &success);
    glGetShaderiv(shader->vertex, GL_INFO_LOG_LENGTH, &buflen);
    infobuffer = (char *)malloc(buflen + 1);
    glGetShaderInfoLog(shader->vertex, buflen, &infolen, infobuffer);

    // if (!success)
    //	log_printf( "Vertex Shader Compile Error:\n%s",infobuffer);
    // else
    //	log_printf( "Vertex Shader Compile OK:\n");

    // compile fragment shader
    shader->fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader->fragment, p_frag_lines, (const char **)fragment_source_lines, 0);
    glCompileShader(shader->fragment);
    glGetShaderiv(shader->fragment, GL_COMPILE_STATUS, &success);
    glGetShaderiv(shader->fragment, GL_INFO_LOG_LENGTH, &buflen);
    free(infobuffer);
    infobuffer = (char *)malloc(buflen + 1);
    glGetShaderInfoLog(shader->fragment, buflen, &infolen, infobuffer);

    // if (!success)
    //	log_printf( "Fragment Shader Compile Error:\n%s",  infobuffer);
    // else
    //	log_printf( "Fragment Shader Compile: OK\n");

    // compile geometry shader if supplied
    if (geometry_source)
    {
        shader->geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(shader->geometry, 1, &geometry_source, NULL);
        glCompileShader(shader->geometry);
        glGetShaderiv(shader->geometry, GL_COMPILE_STATUS, &success);
        glGetShaderiv(shader->geometry, GL_INFO_LOG_LENGTH, &buflen);
        free(infobuffer);
        infobuffer = (char *)malloc(buflen + 1);
        glGetShaderInfoLog(shader->geometry, buflen, &infolen, infobuffer);

        // if (!success)
        //	log_printf( "Geometry Shader Compile Error:\n%s", infobuffer);
        // else
        //	log_printf( "Geometry Shader Compile OK:\n");
    }

    // link shader programs
    shader->program = glCreateProgram();
    glAttachShader(shader->program, shader->fragment);
    glAttachShader(shader->program, shader->vertex);
    if (geometry_source)
        glAttachShader(shader->program, shader->geometry);
    glLinkProgram(shader->program);

    // clean up
    for (int32_t i = 0; i < p_vert_lines; i++)
    {
        free(vertex_source_lines[i]);
    }
    for (int32_t i = 0; i < p_frag_lines; i++)
    {
        free(fragment_source_lines[i]);
    }
    for (int32_t i = 0; i < p_geom_lines; i++)
    {
        free(geometry_source_lines[i]);
    }
    return shader;
}

void gl_destroy_shader(Shader *shader)
{
    glUseProgram(0);
    glDetachShader(shader->program, shader->vertex);
    glDetachShader(shader->program, shader->fragment);
    glDetachShader(shader->program, shader->geometry);
    glDeleteShader(shader->vertex);
    glDeleteShader(shader->fragment);
    glDeleteShader(shader->geometry);
    free(shader);
}
void gl_bind_shader(Shader *shader)
{
    glUseProgram(shader->program);
}
void gl_unbind_shader(Shader *shader)
{
    glUseProgram(0);
}
int32_t gl_set_uniform_float(Shader *shader, const char *uniform, float32 var)
{
    int32_t loc = glGetUniformLocation(shader->program, uniform);
    if (loc != -1)
    {
        glUniform1f(loc, var);
    }
    return loc;
}

void gl_set_uniform2v(Shader *shader, const char *name, int32 num_elements, float32 *value)
{
    GLint uniform_loc = glGetUniformLocation(shader->program, name);
    glUniform2fv(uniform_loc, num_elements, value);
}
void gl_set_uniform3v(Shader *shader, const char *name, int32 num_elements, float32 *value)
{
    GLint uniform_loc = glGetUniformLocation(shader->program, name);
    glUniform3fv(uniform_loc, num_elements, value);
}
void gl_set_uniform4v(Shader *shader, const char *name, int32 num_elements, float32 *value)
{
    GLint uniform_loc = glGetUniformLocation(shader->program, name);
    glUniform4fv(uniform_loc, num_elements, value);
}
void gl_set_uniform_vec2(Shader *shader, const char *name, vec2 &value)
{
    float32 v[2]{value.x, value.y};
    gl_set_uniform2v(shader, name, 1, &v[0]);
}
void gl_set_uniform_vec3(Shader *shader, const char *name, vec3 &value)
{
    float32 v[3]{value.x, value.y, value.z};
    gl_set_uniform3v(shader, name, 1, &v[0]);
}
void gl_set_uniform1i(Shader *shader, const char *name, int32 value)
{
    GLint uniform_loc = glGetUniformLocation(shader->program, name);
    glUniform1i(uniform_loc, value);
}
void gl_set_uniform_matrix4v(Shader *shader, const char *name, int32 num_elements, mat4x4 value)
{
    GLint uniform_loc = glGetUniformLocation(shader->program, name);
    glUniformMatrix4fv(uniform_loc, num_elements, GL_FALSE, (const GLfloat *)&value);
}
SLShader::SLShader(const char *vertex_file, const char *fragment_file, const char *geometry_file)
{
    shader = gl_create_shader(vertex_file, fragment_file, geometry_file);
}
SLShader::~SLShader()
{
    if (shader)
    {
        gl_unbind_shader(shader);
        gl_destroy_shader(shader);
    }
}
bool SLShader::load_from_string(const char *vertex_src, const char *fragment_src, const char *geometry_src)
{
    if (shader)
    {
        gl_unbind_shader(shader);
        gl_destroy_shader(shader);
    }
    shader = gl_create_shader_ex(vertex_src, fragment_src, geometry_src);
    return (bool)shader;
}
bool SLShader::load_from_file(const char *vertex_file, const char *fragment_file, const char *geometry_file)
{
    if (shader)
    {
        gl_unbind_shader(shader);
        gl_destroy_shader(shader);
    }
    shader = gl_create_shader(vertex_file, fragment_file, geometry_file);
    return (bool)shader;
}

void SLShader::bind()
{
    if (shader)
        gl_bind_shader(shader);
}
void SLShader::unbind()
{
    if (shader)
        gl_unbind_shader(shader);
}

void SLShader::set_uniform_int(const char *name, int32 v)
{
    if (shader)
        gl_set_uniform1i(shader, name, v);
}
void SLShader::set_uniform_float(const char *name, float32 v)
{
    if (shader)
        gl_set_uniform_float(shader, name, v);
}
void SLShader::set_uniform_vec2(const char *name, vec2 v)
{
    if (shader)
        gl_set_uniform_vec2(shader, name, v);
}
void SLShader::set_uniform_vec3(const char *name, vec3 v)
{
    if (shader)
        gl_set_uniform_vec3(shader, name, v);
}
void SLShader::set_uniform_matrix(const char *name, mat4x4 v)
{
    if (shader)
        gl_set_uniform_matrix4v(shader, name, 1, v);
}