#include "sl.h"

class Camera : public Object3d
{
public:
	Camera();
	double get_screen_size(Object3d* obj, float32 distance);
	void billboard(vec3& pos, float32 size);
	void billboard_fixed(vec3& pos, float32 abs_size);
	void billboard_quad(vec3  pos, float32 size);
	virtual void set_3d_transform();
	virtual void set_doom_3d_transform();
	virtual void set_projection();
	void get_glu_lookat_params(vec3& eye, vec3& center, vec3& up);
	virtual void billboard_update();
	void set_viewport_params(int32_t vx, int32_t vy, int32_t vw, int32_t vh);

	void set_frustum();
	void get_frustum_points_near(vec3& near_center, vec3& near_top_left,
		vec3& near_top_right, vec3& near_bottom_left, vec3& near_back_right);
	void get_frustum_points_far(vec3& far_center, vec3& far_top_left,
		vec3& far_top_right, vec3& far_bottom_left, vec3& far_bottom_right);
	bool point_within_frustum(vec3& p);
	bool point_within_frustum(dvec3 p);
	bool point_within_frustum(ivec3 p);
	void set_frustum_vars();

	vec3 up_vector();
	vec3 down_vector();
	vec3 left_vector();
	vec3 right_vector();
	vec3 forward_vector();
	vec3 back_vector();

	mat4x4 bboard_mat;
	float32 nearz, farz;
	float32 fov;
	bool external;
	//Plane<> view_frustum[6];// the 6 planes (0=nearz, 1=farz, 2=left, 3=right, 4=top , 5=bottom)
	float32 hfar, hnear, wfar, wnear;
	float32 vratio;
	bool viewchanged{ true };
	int32 viewchange_count{ 0 };
	int32 viewchange_threshold{ 5 };
protected:
	int viewport_x, viewport_y, viewport_w, viewport_h;
	virtual void apply_translation(vec3& offset);
};
