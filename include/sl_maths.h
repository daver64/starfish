/**
 * (c) 2023 David Rowbotham thedaver64@gmail.com
*/

#pragma once

#include "glm/glm.hpp"

#include <xmmintrin.h>
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



class quat {

};

class dquat {

};

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

#define sgn(x) ((x<0)?-1:((x>0)?1:0))

