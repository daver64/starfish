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

Camera::Camera()
{
	farz = 1e2;
	nearz = 0.5;
	fov = 60.0;
	parent = nullptr;
	external = false;
	rmat = rquat.to_matrix();
	//	bboard_mat = rquat.to_matrix();
	//	for (int32_t n = 0; n < 3; n++)
	//	{
	//		bboard_mat.x[n] = -rmat.x[n];
	//		bboard_mat.z[n] = -rmat.z[n];
	//	}
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

void Camera::set_frustum_vars()
{
	vratio = (float32)viewport_w / (float32)viewport_h;
	hnear = std::tan(degtorad(fov / 2.0f)) * nearz;
	wnear = hnear * vratio;
	hfar = std::tan(degtorad(fov / 2.0f)) * farz;
	wfar = hfar * vratio;
}
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
	//return -Vec3<>(rmat.z[0], rmat.z[1], rmat.z[2]).normalise();
	vec3 result = -vec3(rmat[6][0], rmat[6][1], rmat[6][2]);
	glm::normalize(result);
	return result;
}
vec3 Camera::up_vector()
{
	//return Vec3<>(rquat.to_matrix().y).normalise();
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
