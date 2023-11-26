/**
 * (c) 2023 David Rowbotham thedaver64@gmail.com
*/
#include "sl.h"

const float64 PI = 3.14159265358979323846264338327950288;
const float64 TAU = 2.0 * PI;
const float64 PIDIV2 = PI / 2.0;
float64 ROUNDING_ERROR = std::numeric_limits<float64>::epsilon();

const float32 PIf = 3.14159265358979323846;
const float32 TAUf = 2.0f * PIf;
const float32 PIDIV2f = PIf / 2.0f;
float32 ROUNDING_ERRORf = std::numeric_limits<float32>::epsilon();


polar::polar(const float32 &lon,
             const float32 &lat,
             const float32 &alt) : lon(lon), lat(lat), alt(alt) {}
polar::polar(const float32 p[3]) : lon(p[0]), lat(p[1]), alt(p[0]) {}
polar::polar(const vec3 &pos)
{
    rad = std::sqrt(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z);
    lon = std::atan(pos.y / pos.x);
    lat = std::atan(std::sqrt(pos.x * pos.x + pos.y * pos.y) / pos.z);
}
float32 &polar::operator[](size_t index)
{
    return d[index];
}
vec3 polar::polar_to_cartesian(const polar &pos)
{
    return vec3(std::cos(pos.lon) * std::cos(pos.lat) * pos.rad,
                std::sin(pos.lon) * std::cos(pos.lat) * pos.rad,
                std::sin(pos.lat) * pos.rad);
}
polar polar::cartesian_to_polar(const vec3 &pos)
{
    return polar(pos);
}
vec3 polar::to_cartesian()
{
    return polar_to_cartesian(*this);
}

void polar::from_cartesian(const vec3 &pos)
{
    *this = cartesian_to_polar(pos);
}

dpolar::dpolar(const float64 &lon,
               const float64 &lat,
               const float64 &alt) : lon(lon), lat(lat), alt(alt) {}
dpolar::dpolar(const float64 p[3]) : lon(p[0]), lat(p[1]), alt(p[0]) {}
dpolar::dpolar(const dvec3 &pos)
{
    rad = std::sqrt(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z);
    lon = std::atan(pos.y / pos.x);
    lat = std::atan(std::sqrt(pos.x * pos.x + pos.y * pos.y) / pos.z);
}
float64 &dpolar::operator[](size_t index)
{
    return d[index];
}
dvec3 dpolar::polar_to_cartesian(const dpolar &pos)
{
    return dvec3(std::cos(pos.lon) * std::cos(pos.lat) * pos.rad,
                 std::sin(pos.lon) * std::cos(pos.lat) * pos.rad,
                 std::sin(pos.lat) * pos.rad);
}
dpolar dpolar::cartesian_to_polar(const dvec3 &pos)
{
    return dpolar(pos);
}
dvec3 dpolar::to_cartesian()
{
    return polar_to_cartesian(*this);
}

void dpolar::from_cartesian(const vec3 &pos)
{
    *this = cartesian_to_polar(pos);
}
