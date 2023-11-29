/**
 * (c) 2023 David Rowbotham thedaver64@gmail.com and Toni Ylisirniö 
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

quat::quat() : w(1), x(0), y(0), z(0) {}
quat::quat(float32 h, float32 p, float32 b)
{
    set(h, p, b);
}
quat::quat(const mat4x4 &m)
{
    float32 tr, s, q[4];
    int32 i, j, k;
    int32 nxt[3] = {1, 2, 0};
    tr = m[0][0] + m[1][1] + m[2][2];
    // check the diagonal

    if (tr > 0.0)
    {
        s = std::sqrt(tr + 1.0);
        this->w = s / 2.0;
        s = 0.5 / s;
        this->x = (m[1][2] - m[2][1]) * s;
        this->y = (m[2][0] - m[0][2]) * s;
        this->z = (m[0][1] - m[1][0]) * s;
    }
    else
    {
        // diagonal is negative
        i = 0;
        if (m[1][1] > m[0][0])
            i = 1;
        if (m[2][2] > m[i][i])
            i = 2;
        j = nxt[i];
        k = nxt[j];
        s = std::sqrt((m[i][i] - (m[j][j] + m[k][k])) + 1.0);
        q[i] = s * 0.5;
        if (s != 0.0)
            s = 0.5 / s;
        q[3] = (m[j][k] - m[k][j]) * s;
        q[j] = (m[i][j] + m[j][i]) * s;
        q[k] = (m[i][k] + m[k][i]) * s;
        this->x = q[0];
        this->y = q[1];
        this->z = q[2];
        this->w = q[3];
    }
}
float32 &quat::operator[](size_t index)
{
    return d[index];
}
void quat::set(float32 h, float32 p, float32 b)
{
    const float32 cr = std::cos(p / 2);
    const float32 cp = std::cos(h / 2);
    const float32 cy = std::cos(b / 2);
    const float32 sr = std::sin(p / 2);
    const float32 sp = std::sin(h / 2);
    const float32 sy = std::sin(b / 2);
    const float32 cpcy = cp * cy;
    const float32 spsy = sp * sy;
    w = cr * cpcy + sr * spsy;
    x = sr * cpcy - cr * spsy;
    y = cr * sp * cy + sr * cp * sy;
    z = cr * cp * sy - sr * sp * cy;
}
void quat::set(const quat &q)
{
    w = q.w;
    x = q.x;
    y = q.y;
    z = q.z;
}
void quat::set(const polar &p)
{
    const float32 sina = std::sin(p.rad / 2);
    const float32 cosa = std::cos(p.rad / 2);
    const float32 sinlat = std::sin(p.lat);
    const float32 coslat = std::cos(p.lat);
    const float32 sinlon = std::sin(p.lon);
    const float32 coslon = std::cos(p.lon);
    x = sina * coslat * sinlon;
    y = sina * sinlat;
    z = sina * sinlat * coslon;
    w = cosa;
}
quat quat::mult(const quat &q1, const quat &q2)
{
    const float32 A = (q1.w + q1.x) * (q2.w + q2.x);
    const float32 B = (q1.z - q1.y) * (q2.y - q2.z);
    const float32 C = (q1.w - q1.x) * (q2.y + q2.z);
    const float32 D = (q1.y + q1.z) * (q2.w - q2.x);
    const float32 E = (q1.x + q1.z) * (q2.x + q2.y);
    const float32 F = (q1.x - q1.z) * (q2.x - q2.y);
    const float32 G = (q1.w + q1.y) * (q2.w - q2.z);
    const float32 H = (q1.w - q1.y) * (q2.w + q2.z);
    quat res;
    res.w = B + (-E - F + G + H) / 2;
    res.x = A - (E + F + G + H) / 2;
    res.y = C + (E - F + G - H) / 2;
    res.z = D + (E - F - G + H) / 2;
    return res;
}
quat &quat::mult(const quat &q2)
{
    const float32 A = (w + x) * (q2.w + q2.x);
    const float32 B = (z - y) * (q2.y - q2.z);
    const float32 C = (w - x) * (q2.y + q2.z);
    const float32 D = (y + z) * (q2.w - q2.x);
    const float32 E = (x + z) * (q2.x + q2.y);
    const float32 F = (x - z) * (q2.x - q2.y);
    const float32 G = (w + y) * (q2.w - q2.z);
    const float32 H = (w - y) * (q2.w + q2.z);
    w = B + (-E - F + G + H) / 2;
    x = A - (E + F + G + H) / 2;
    y = C + (E - F + G - H) / 2;
    z = D + (E - F - G + H) / 2;
    return *this;
}
mat4x4 quat::to_matrix()
{
    mat4x4 m;
    const float32 x2 = x + x;
    const float32 y2 = y + y;
    const float32 z2 = z + z;
    const float32 xx = x * x2;
    const float32 xy = x * y2;
    const float32 xz = x * z2;
    const float32 yy = y * y2;
    const float32 yz = y * z2;
    const float32 zz = z * z2;
    const float32 wx = w * x2;
    const float32 wy = w * y2;
    const float32 wz = w * z2;
    m[0][0] = 1.0 - (yy + zz);
    m[1][0] = xy - wz;
    m[2][0] = xz + wy;
    m[3][0] = 0.0;
    m[0][1] = xy + wz;
    m[1][1] = 1.0 - (xx + zz);
    m[2][1] = yz - wx;
    m[3][1] = 0.0;
    m[0][2] = xz - wy;
    m[1][2] = yz + wx;
    m[2][2] = 1.0 - (xx + yy);
    m[3][2] = 0.0;
    m[0][3] = 0;
    m[1][3] = 0;
    m[2][3] = 0;
    m[3][3] = 1;
    return m;
}

void quat::apply()
{
    mat4x4 m = to_matrix();
    matrix_apply(m);
}
void quat::pitch(float32 a)
{
    quat q;
    q.w = std::cos(a / 2);
    q.x = std::sin(a / 2);
    q.y = 0;
    q.z = 0;
    set(mult(*this, q));
}
void quat::yaw(float32 a)
{
    quat q;
    q.w = std::cos(a / 2);
    q.x = 0;
    q.y = std::sin(a / 2);
    q.z = 0;
    set(mult(*this, q));
}
void quat::roll(float32 a)
{
    quat q;
    q.w = std::cos(a / 2);
    q.x = 0;
    q.y = 0;
    q.z = std::sin(a / 2);
    set(mult(*this, q));
}
void quat::set(vec3 v, float32 a)
{
    glm::normalize(v);
    v *= sin(a / 2.0);
    x = v.x;
    y = v.y;
    z = v.z;
    w = cos(a / 2.0);
}
void quat::get_headings(float32 *heading, float32 *attitude, float32 *bank)
{
    *heading = std::atan2(2 * y * w - 2 * x * z, 1 - 2 * y * y - 2 * z * z);
    *attitude = std::asin(2 * x * y + 2 * z * w);
    *bank = std::atan2(2 * x * w - 2 * y * z, 1 - 2 * x * x - 2 * z * z);
}
const float32 quat::length()
{
    return std::sqrt(w * w + x * x + y * y + z * z);
}
void quat::normalise()
{
    const float32 qlength = length();
    if (qlength == 0)
    {
        w = 1.;
        x = 0.;
        y = 0.;
        z = 0.;
    }
    else
    {
        float32 inv = 1.0f / qlength;
        x = x * inv;
        y = y * inv;
        z = z * inv;
        w = w * inv;
    }
}
void quat::conjugate(const quat &q)
{
    w = q.w;
    x = -q.x;
    y = -q.y;
    z = -q.z;
}
const quat &quat::operator*(const quat &oq)
{
    quat result = mult(oq);
    x = result.x;
    y = result.y;
    z = result.z;
    w = result.w;
    return *this;
}
quat quat::slerp(quat a, quat b, float32 t)
{
    float32 flip = 1.0;
    float32 cosine = a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z;
    if (cosine < 0)
    {
        cosine = -cosine;
        flip = -1;
    }
    if ((1 - cosine) < 0.00001)
    {
        a.w *= (1 - t);
        a.x *= (1 - t);
        a.y *= (1 - t);
        a.z *= (1 - t);
        b.w *= (t * flip);
        b.x *= (t * flip);
        b.y *= (t * flip);
        b.z *= (t * flip);
        a.w = a.w + b.w;
        a.x = a.x + b.x;
        a.y = a.y + b.y;
        a.z = a.z + b.z;
        return a;
    }
    const float32 theta = std::acos(cosine);
    const float32 sine = std::sin(theta);
    const float32 beta = std::sin((1 - t) * theta) / sine;
    const float32 alpha = std::sin(t * theta) / sine * flip;
    a.w *= beta;
    a.x *= beta;
    a.y *= beta;
    a.z *= beta;
    b.w *= alpha;
    b.x *= alpha;
    b.y *= alpha;
    b.z *= alpha;
    a.w = a.w + b.w;
    a.x = a.x + b.x;
    a.y = a.y + b.y;
    a.z = a.z + b.z;
    return quat(a);
}

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


plane::plane()
{
    normal = vec3(0, 1, 0);    
}
plane::~plane()
{
    
}
//
//
// free form functions
//
//

void quadratic_plot(vec2 startpos, vec2 controlpos, vec2 endpos, std::vector<vec2> &plotresult, int32 numsegments)
{
    for (int32 i = 0; i <= numsegments; ++i)
    {
        const float32 t = (float64)i / (float64)numsegments;
        const float32 a = std::pow((1.0 - t), 2.0);
        const float32 b = 2.0 * t * (1.0 - t);
        const float32 c = std::pow((float32)t, 2.0);
        const float32 x = a * startpos.x + b * controlpos.x + c * endpos.x;
        const float32 y = a * startpos.y + b * controlpos.y + c * endpos.y;
        plotresult.emplace_back(vec2((float32)x, (float32)y));
    }
}

void cubic_plot(vec2 startpos, vec2 controlpos1, vec2 endpos, vec2 controlpos2, std::vector<vec2> &plotresult, int32 numsegments)
{
    for (int32 i = 0; i <= numsegments; ++i)
    {
        const float32 t = (float_t)i / (float_t)numsegments;
        const float32 a = powf((1.0f - t), 3.0f);
        const float32 b = 3.0f * t * powf((1.0f - t), 2.0f);
        const float32 c = 3.0f * powf(t, 2.0f) * (1.0f - t);
        const float32 d = powf(t, 3.0f);
        const float32 x = a * startpos.x + b * controlpos1.x + d * endpos.x + c * controlpos2.x;
        const float32 y = a * startpos.y + b * controlpos1.y + d * endpos.y + c * controlpos2.y;
        plotresult.emplace_back(vec2((float_t)x, (float_t)y));
    }
}

vec2 get_line_intersection(vec2 v0, vec2 v1, vec2 v2, vec2 v3, bool &success)
{
    vec2 vr;
    success = get_line_intersection(v0.x, v0.y, v1.x, v1.y, v2.x, v2.y, v3.x, v3.y, vr.x, vr.y);
    return vr;
}

bool get_line_intersection(float32 p0_x, float32 p0_y,
                           float32 p1_x, float32 p1_y,
                           float32 p2_x, float32 p2_y,
                           float32 p3_x, float32 p3_y,
                           float32 &i_x, float32 &i_y)
{
    float32 s1_x, s1_y, s2_x, s2_y;
    s1_x = p1_x - p0_x;
    s1_y = p1_y - p0_y;
    s2_x = p3_x - p2_x;
    s2_y = p3_y - p2_y;
    float32 s, t;
    s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
    t = (s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);
    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
    {
        i_x = p0_x + (t * s1_x);
        i_y = p0_y + (t * s1_y);
        return true;
    }
    i_x = NAN;
    i_y = NAN;
    return false;
}

float64 gcircle_distance(float64 lon1, float64 lat1, float64 lon2, float64 lat2, float64 R)
{
    const float64 theta1 = degtorad(lat1);
    const float64 theta2 = degtorad(lat2);
    const float64 delta_theta = degtorad(lat2 - lat1);
    const float64 delta_tau = degtorad(lon2 - lon1);
    const float64 a = sin(delta_theta / 2.0) * sin(delta_theta / 2.0) +
                      cos(theta1) * cos(theta2) * sin(delta_tau / 2) * sin(delta_tau / 2.0);
    const float64 c = 2 * atan2(sqrt(a), sqrt(1 - a));
    float64 d = R * c;
    return d;
}

float64 gcircle_bearing(float64 from_lon, float64 from_lat, float64 to_lon, float64 to_lat)
{
    const float64 y = sin(degtorad(to_lon - from_lon)) * cos(degtorad(to_lat));
    const float64 x = cos(degtorad(from_lat)) * sin(degtorad(to_lat)) - sin(degtorad(from_lat)) * cos(degtorad(to_lat)) * cos(degtorad(to_lon - from_lon));
    float64 b = radtodeg(atan2(y, x));
    if (b < 0)
        b = 360 + b;
    return b;
}

void gcircle_destination(float64 from_lon, float64 from_lat, float64 bearing, float64 distance, float64 &to_lon, float64 &to_lat, float64 R)
{
    const float64 to_lat1 = asin(sin(degtorad(from_lat)) * cos(distance / R) +
                                 cos(degtorad(from_lat)) * sin(distance / R) * cos(degtorad(bearing)));
    const float64 lon = degtorad(from_lon) + atan2(sin(degtorad(bearing)) *
                                                       sin(distance / R) * cos(degtorad(from_lat)),
                                                   cos(distance / R) - sin(degtorad(from_lat)) * sin(degtorad(to_lat1)));
    to_lat = radtodeg(to_lat1);
    to_lon = radtodeg(lon);
}
