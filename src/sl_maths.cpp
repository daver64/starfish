#include "sl.h"

polar::polar(const float &lon,
             const float &lat,
             const float &alt) : lon(lon), lat(lat), alt(alt) {}
polar::polar(const float p[3]) : lon(p[0]), lat(p[1]), alt(p[0]) {}
polar::polar(const vec3 &pos)
{
    rad = std::sqrt(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z);
    lon = std::atan(pos.y / pos.x);
    lat = std::atan(std::sqrt(pos.x * pos.x + pos.y * pos.y) / pos.z);
}
float &polar::operator[](size_t index)
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

dpolar::dpolar(const double &lon,
               const double &lat,
               const double &alt) : lon(lon), lat(lat), alt(alt) {}
dpolar::dpolar(const double p[3]) : lon(p[0]), lat(p[1]), alt(p[0]) {}
dpolar::dpolar(const dvec3 &pos)
{
    rad = std::sqrt(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z);
    lon = std::atan(pos.y / pos.x);
    lat = std::atan(std::sqrt(pos.x * pos.x + pos.y * pos.y) / pos.z);
}
double &dpolar::operator[](size_t index)
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
