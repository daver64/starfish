/**
 * (c) 2023 David Rowbotham thedaver64@gmail.com
*/

#pragma once

#include "glm/glm.hpp"

#include <xmmintrin.h>
#include <vector>

extern const double_t PI;
extern const double_t TAU;
extern const double_t PIDIV2;
extern double ROUNDING_ERROR;

extern const float_t PIf;
extern const float_t TAUf;
extern const float_t PIDIV2f;
extern float_t ROUNDING_ERRORf;

typedef int8_t int8;
typedef uint8_t uint8;
typedef int16_t int16;
typedef uint16_t uint16;
typedef int32_t int32;
typedef uint32_t uint32;
typedef int64_t int64;
typedef uint64_t uint64;
typedef uint32_t pixel32;
typedef float float32;
typedef double float64;

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::ivec2;
using glm::ivec3;
using glm::ivec4;
using glm::mat4x4;
using glm::dvec2;
using glm::dvec3;
using glm::dvec4;
using glm::dmat4x4;

inline float32 lerp(float32 v1, float32 v2, float32 a) { return (v1 * (1.0f - a) + v2 * a); }
inline float64 lerp(float64 v1, float64 v2, float64 a) { return (v1 * (1.0 - a) + v2 * a); }
inline float64 degtorad(float64 val) { return val * 0.0174532925; }
inline float32 degtorad(float32 val) { return val * 0.0174532925f; }
inline float64 radtodeg(float64 val) { return val * 57.2957795; }
inline float32 radtodeg(float32 val) { return val * 57.2957795f; }

class polar {
public:
	union
	{
		float32 d[4] = { 0,0,0,0 };
		struct { float32 ra, dec, rad, w; };
		struct { float32 lon, lat, alt, p; };
	};
	polar(const float32& lon = 0,
		const float32& lat = 0,
		const float32& alt = 0);
	polar(const float32 p[3]);
	polar(const vec3& pos);
	float32& operator[](size_t index);
	vec3 polar_to_cartesian(const polar& pos);
	polar cartesian_to_polar(const vec3& pos);
	vec3 to_cartesian();
	void from_cartesian(const vec3& pos);
};

class dpolar {
public:
	union
	{
		float64 d[4] = { 0,0,0,0 };
		struct { float64 ra, dec, rad, w; };
		struct { float64 lon, lat, alt, p; };
	};
	dpolar(const float64& lon = 0,
		const float64& lat = 0,
		const float64& alt = 0);
	dpolar(const float64 p[3]);
	dpolar(const dvec3& pos);
	float64& operator[](size_t index);
	dvec3 polar_to_cartesian(const dpolar& pos);
	dpolar cartesian_to_polar(const dvec3& pos);
	dvec3 to_cartesian();
	void from_cartesian(const vec3& pos);
};

class quat {
public:
	union
	{
		float32 d[4]{ 0,0,0,0 };
		struct { float32 w, x, y, z; };
	};
	quat();
	quat(float32 h, float32 p, float32 b);
	quat(const mat4x4& m);
	float32& operator[](size_t index);
	void set(float32 h, float32 p, float32 b);
	void set(const quat& q);
	void set(const polar& p);
	quat mult(const quat& q1, const quat& q2);
	quat& mult(const quat& q2);
	mat4x4 to_matrix();
	void apply();
	void pitch(float32 a);
	void yaw(float32 a);
	void roll(float32 a);
	void set(vec3 v, float32 a);
	void get_headings(float32* heading, float32* attitude, float32* bank);
	const float32 length();
	void normalise();
	void conjugate(const quat& q);
	const quat& operator*(const quat& oq);
	quat slerp(quat a, quat b, float32 t);
};

class dquat {

};


void cubic_plot(vec2 startpos, vec2 controlpos1, vec2 endpos, vec2 controlpos2, std::vector< vec2>& plotresult, int32 numsegments);
void quadratic_plot(vec2 startpos, vec2 controlpos, vec2 endpos, std::vector< vec2>& plotresult, int32 numsegments);
bool get_line_intersection(float32 p0_x, float32 p0_y,
	float32 p1_x, float32 p1_y,
	float32 p2_x, float32 p2_y,
	float32 p3_x, float32 p3_y,
	float32& i_x, float32& i_y);
vec2 get_line_intersection(vec2 v0, vec2 v1, vec2 v2, vec2 v3,bool& success);
void gcircle_destination(float64 from_lon, float64 from_lat, float64 bearing, float64 distance, 
    float64& to_lon, float64& to_lat, float64 R);
float64 gcircle_bearing(float64 from_lon, float64 from_lat, float64 to_lon, float64 to_lat);
float64 gcircle_distance(float64 lon1, float64 lat1, float64 lon2, float64 lat2, float64 R);

void matrix_apply(mat4x4 &m);



#define sgn(x) ((x<0)?-1:((x>0)?1:0))

