/**
 * (c) 2023 David Rowbotham thedaver64@gmail.com and Toni Ylisirniö
 */
#include "sl.h"
#include "sl_camera.h"
#include "sl_draw.h"
#include "sl_framebuffer.h"
#include "sl_primitivebuffer.h"
#include "sl_texture.h"
#include "sl_context.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#ifndef _WIN32
#include <GL/glu.h>
#endif
/*

	TODO: convert from simlib matrix handling to glm.
	note: simlib internal layout

	{
		T m[16];
		T d[4][4];
		struct
		{
			T x[3]; T dpx;
			T y[3]; T dpy;
			T z[3]; T dpz;
			union {
				struct {
					T tx, ty, tz, tw;
				};
				T t[3];
			};
		};

*/
Camera::Camera()
{
	farz = 1e2;
	nearz = 0.5;
	fov = 60.0;
	parent = nullptr;
	external = false;
	rmat = rquat.to_matrix();
	bboard_mat = rquat.to_matrix();
	for (int32_t n = 0; n < 3; n++)
	{
		bboard_mat[0][n] = -rmat[0][n];
		bboard_mat[6][n] = -rmat[6][n];
	}
}
// Camera::~Camera()
//{

//}
void Camera::set_viewport_params(int32_t vx, int32_t vy, int32_t vw, int32_t vh)
{
	viewport_x = vx;
	viewport_y = vy;
	viewport_w = vw;
	viewport_h = vh;
}
void Camera::set_projection()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(viewport_x, viewport_y, viewport_w, viewport_h);
	gluPerspective(fov, (float64)viewport_w / (float64)viewport_h, nearz, farz);
	glMatrixMode(GL_MODELVIEW);
}
void Camera::set_3d_transform()
{
	set_projection();
	glLoadIdentity();

	rmat = rquat.to_matrix();
	set_frustum_vars();
	set_frustum();
	gluLookAt(position.x, position.y, position.z + 0.001,
			  position.x + rmat[6][0], position.y + rmat[6][1], position.z + rmat[6][2],
			  rmat[3][0], rmat[3][1], rmat[3][2]);
}

bool Camera::point_within_frustum(vec3 &p)
{
	EIntersectionRelation3D point_relation = view_frustum[0].classify_point_relation(p);
	if (point_relation == ISREL3D_BACK)
		return false;
	point_relation = view_frustum[1].classify_point_relation(p);
	if (point_relation == ISREL3D_BACK)
		return false;
	point_relation = view_frustum[2].classify_point_relation(p);
	if (point_relation == ISREL3D_BACK)
		return false;
	point_relation = view_frustum[3].classify_point_relation(p);
	if (point_relation == ISREL3D_BACK)
		return false;
	point_relation = view_frustum[4].classify_point_relation(p);
	if (point_relation == ISREL3D_BACK)
		return false;
	point_relation = view_frustum[5].classify_point_relation(p);
	if (point_relation == ISREL3D_BACK)
		return false;

	return true;
}
void Camera::set_frustum() 
{
	vec3 up = rquat.to_matrix()[3];
	vec3 right = -vec3(rquat.to_matrix()[0]);
	// slightly wide
	up = up * 1.1f;
	right = right * 1.1f;
	vec3 fc = position + (forward_vector() * farz);
	vec3 ftl = fc + (up * hfar) - (right * wfar);
	vec3 ftr = fc + (up * hfar) + (right * wfar);
	vec3 fbl = fc - (up * hfar) - (right * wfar);
	vec3 fbr = fc - (up * hfar) + (right * wfar);
	// pull back to behind camera
	vec3 nc = position + (forward_vector() * -1.0f);
	vec3 ntl = nc + (up * hnear) - (right * wnear);
	vec3 ntr = nc + (up * hnear) + (right * wnear);
	vec3 nbl = nc - (up * hnear) - (right * wnear);
	vec3 nbr = nc - (up * hnear) + (right * wnear);
	// 0=nearz, 1=farz, 2=left, 3=right, 4=top , 5=bottom
	view_frustum[0].set_plane(ntl, ntr, nbr);
	view_frustum[1].set_plane(ftr, ftl, fbl);
	view_frustum[2].set_plane(ntl, nbl, fbl);
	view_frustum[3].set_plane(nbr, ntr, fbr);
	view_frustum[4].set_plane(ntr, ntl, ftl);
	view_frustum[5].set_plane(nbl, nbr, fbr);
}
void Camera::set_frustum_vars()
{
	vratio = (float32)viewport_w / (float32)viewport_h;
	hnear = std::tan(degtorad(fov / 2.0f)) * nearz;
	wnear = hnear * vratio;
	hfar = std::tan(degtorad(fov / 2.0f)) * farz;
	wfar = hfar * vratio;
}

void Camera::get_frustum_points_near(vec3 &near_center, vec3 &near_top_left,
									 vec3 &near_top_right, vec3 &near_bottom_left, vec3 &near_bottom_right)
{
	// fix me!
	// vec3 up = rquat.to_matrix().y;
	vec3 up = rquat.to_matrix()[3];
	// Vec3<> right = -Vec3<>(rquat.to_matrix().x);
	vec3 right = -vec3(rquat.to_matrix()[0]);
	near_center = position + forward_vector();

	near_top_left = near_center + (up * hnear) - (right * wnear);
	near_top_right = near_center + (up * hnear) + (right * wnear);
	near_bottom_left = near_center - (up * hnear) - (right * wnear);
	near_bottom_right = near_center - (up * hnear) + (right * wnear);
}
vec3 Camera::forward_vector()
{
	// fix me!!
	// return Vec3<>(rmat.z[0], rmat.z[1], rmat.z[2]).normalise();
	vec3 result = vec3(rmat[6][0], rmat[6][1], rmat[6][2]);
	glm::normalize(result);
	return result;
}
vec3 Camera::back_vector()
{
	// return -Vec3<>(rmat.z[0], rmat.z[1], rmat.z[2]).normalise();
	vec3 result = -vec3(rmat[6][0], rmat[6][1], rmat[6][2]);
	glm::normalize(result);
	return result;
}
vec3 Camera::up_vector()
{
	// return Vec3<>(rquat.to_matrix().y).normalise();
	vec3 result = glm::normalize(vec3(rquat.to_matrix()[3]));
	glm::normalize(result);
	return result;
}
vec3 Camera::down_vector()
{
	vec3 result = glm::normalize(-vec3(rquat.to_matrix()[3]));
	glm::normalize(result);
	return result;
}
vec3 Camera::left_vector()
{
	vec3 result;
	glm::normalize(result);
	return result;
}
vec3 Camera::right_vector()
{
	vec3 result;
	glm::normalize(result);
	return result;
}
