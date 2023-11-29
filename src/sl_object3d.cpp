/**
 * (c) 2023 David Rowbotham thedaver64@gmail.com and Toni Ylisirniö 
*/
#include "sl.h"

Object3d* find_common_parent(Object3d* o1, Object3d* o2,
	std::vector<Object3d*>* up, std::vector<Object3d*>* down) {
	std::vector<Object3d*> o1_chain;
	std::vector<Object3d*> o2_chain;
	std::vector<Object3d*>::iterator res_i;
	Object3d* o1t = o1;
	Object3d* o2t = o2;
	o1_chain.push_back(o1t);
	o2_chain.push_back(o2t);
	do {
		if (o1t->parent) {
			o1t = o1t->parent;
			o1_chain.push_back(o1t);
		}
		if (o2t->parent) {
			o2t = o2t->parent;
			o2_chain.push_back(o2t);
		}
		res_i = find(o1_chain.begin(), o1_chain.end(), o2t);
		if (res_i != o1_chain.end()) {
			if (up && down) {
				up->insert(up->begin(), o1_chain.begin(), res_i + 1);
				down->insert(down->begin(), o2_chain.rbegin(), o2_chain.rend());
			}
			return *res_i;
		}
		res_i = find(o2_chain.begin(), o2_chain.end(), o1t);
		if (res_i != o2_chain.end()) {
			if (up && down) {
				std::vector<Object3d*>::reverse_iterator rev_i = o2_chain.rbegin();
				while ((*rev_i) != (*res_i)) rev_i++;  // Needs work to make it more efficient.

				up->insert(up->begin(), o1_chain.begin(), o1_chain.end());
				down->insert(down->begin(), rev_i, o2_chain.rend());
			}
			return *res_i;
		}
	} while (o1t->parent || o2t->parent);
	return nullptr;
}

/*
  07:06 < X-Com> The up-chain checks for fixed orientation, the down-chain doesn't.
  07:06 < X-Com> Eg, it works only if all coordinate systems have axes that are
  aligned the same away. Up-chain works for any combination.
*/
mat4x4 local_to_local(Object3d* o1, Object3d* o2) { // Probably not-broken, caveat user.
	mat4x4 accu = o1->local_to_parent();
/*	std::vector<Object3d*> up;
	std::vector<Object3d*> down;
	Object3d* cp = find_common_parent(o1, o2, &up, &down);
	if (o1 != cp) accu = o1->local_to_parent();
	//std::vector<Object3d*>::iterator i;
	Object3d* prev = o1;
	for (auto i = up.begin() + 1; i < up.end() - 1; i++) {
		//str += (*i)->name + ",";
		if (prev->fixed)
			accu.mult((*i)->local_to_parent());
		else
			accu.mult((*i)->relative_to_parent());
		prev = (*i);
	}
	for (auto i = down.begin() + 1; i < down.end(); i++) {
		accu.mult(Matrix<>((*i)->rmat).translate((*i)->position));
		// WRONG! FIXME (should check for fixed'ness)
	}
	//Vec3 dest=accu.Transform(Vec3(0,0,0));*/
	return accu;
}

mat4x4 relative_to_relative(Object3d* o1,
	Object3d* o2, vec3* vel) { // Not broken, can be used
	mat4x4 accu;
/*	vec3 vel_accu;
	std::vector<Object3d*> up;
	std::vector<Object3d*> down;
	Object3d* cp = find_common_parent(o1, o2, &up, &down);
	if (o1 != cp) accu = o1->relative_to_parent();

	std::vector<Object3d*>::iterator i;
	Object3d* prev = o1;
	for (i = up.begin() + 1; i < up.end() - 1; i++) {
		vel_accu -= (*i)->velocity;
		if (prev->fixed) {
			accu.mult((*i)->local_to_parent());
			prev = (*i);
		}
		else {
			accu.mult((*i)->relative_to_parent());
			prev = (*i);
		}
	}
	for (i = down.begin() + 1; i < down.end(); i++) {
		vel_accu += (*i)->velocity;
		accu.translate((*i)->position);
	}
	if (vel != nullptr) *vel += vel_accu;
    */
	return accu;
}
mat4x4 Object3d::local_to_relative() {
mat4x4 m;
return m;
//	return Matrix<>(rmat).invert();  // No translation part in rmat.
}
mat4x4 Object3d::relative_to_parent() {
mat4x4 m;
return m;
//	return Matrix<>(-position);
}
mat4x4 Object3d::local_to_parent() {
mat4x4 m;
return m;
//	return Matrix<>(rmat).translate(position).invert();
}

Object3d::Object3d(Object3d* p) :parent(p) {
	if (parent != nullptr)
		position = parent->position;
}

void Object3d::pitch(float32 p) { rquat.pitch(p); }
void Object3d::roll(float32 r) { rquat.roll(r); }
void Object3d::yaw(float32 y) { rquat.yaw(y); }
void Object3d::set_rotation(const quat& q) { rquat = q; }

/* angular momentum code starts here */
void Moments::recalculate()
{
	angular_velocity.x = angular_momentum.x / inertia_tensor.x;
	angular_velocity.y = angular_momentum.y / inertia_tensor.y;
	angular_velocity.z = angular_momentum.z / inertia_tensor.z;
	orientation.normalise();
	quat tmp;
	tmp.x = angular_velocity.x;
	tmp.y = angular_velocity.y;
	tmp.z = angular_velocity.z;
	tmp.w = 0.;

	spin = tmp.mult(orientation);
	spin.w *= 0.5;
	spin.x *= 0.5;
	spin.y *= 0.5;
	spin.z *= 0.5;
}

Deriv Object3d::evaluate(Moments& state)
{
	Deriv output;
	output.spin = state.spin;
	output.torque = angular_acceleration;
	return output;
}

Deriv Object3d::evaluate(Moments& state, float32 dt, Deriv& derivative)
{
	state.orientation.w += derivative.spin.w * dt;
	state.orientation.x += derivative.spin.x * dt;
	state.orientation.y += derivative.spin.y * dt;
	state.orientation.z += derivative.spin.z * dt;
	state.angular_momentum += derivative.torque * dt;
	state.recalculate();
	Deriv output;
	output.spin = state.spin;
	output.torque = angular_acceleration;
	return output;
}

//Object3d::Object3d(Object3d *parent)
//: parent(parent)
//{

//}
//Object3d::~Object3d()
//{

//}
void Object3d::apply_forces(float32 dt)
{
	apply_linear_force(dt);
	apply_angular_force(dt);
	
	velocity += linear_acceleration * dt;
	position += velocity * dt;
	linear_acceleration= vec3(0,0,0);
	angular_acceleration= vec3(0,0,0);
}
void Object3d::apply_linear_force(float32 dt)
{
	apply_gravity_force(dt);
	apply_aerodynamic_force(dt);
	//apply_linear_thrust(dt);

}
void Object3d::apply_angular_force(float32 dt)
{
	previous_rotary = rotary;
	Moments* state = &rotary;

	Deriv a = evaluate(*state);
	Deriv b = evaluate(*state, dt * 0.5, a);
	Deriv c = evaluate(*state, dt * 0.5, b);
	Deriv d = evaluate(*state, dt, c);

	quat tmp1;
	tmp1.w = 2.0 * (b.spin.w + c.spin.w);
	tmp1.x = 2.0 * (b.spin.x + c.spin.x);
	tmp1.y = 2.0 * (b.spin.y + c.spin.y);
	tmp1.z = 2.0 * (b.spin.z + c.spin.z);

	tmp1.w = (a.spin.w + d.spin.w + tmp1.w);
	tmp1.x = (a.spin.x + d.spin.x + tmp1.x);
	tmp1.y = (a.spin.y + d.spin.y + tmp1.y);
	tmp1.z = (a.spin.z + d.spin.z + tmp1.z);

	tmp1.w *= (1.0 / 6.0) * dt;
	tmp1.x *= (1.0 / 6.0) * dt;
	tmp1.y *= (1.0 / 6.0) * dt;
	tmp1.z *= (1.0 / 6.0) * dt;

	state->orientation.w += tmp1.w;
	state->orientation.x += tmp1.x;
	state->orientation.y += tmp1.y;
	state->orientation.z += tmp1.z;

	vec3 tmp2 = (b.torque + c.torque);
	tmp2 = tmp2 * 2.f;
	vec3 tmp3 = (a.torque + d.torque);
	tmp2 = tmp2 + tmp3;
	tmp2 = tmp2 * ( dt * (1.0f / 6.0f));
	state->angular_momentum += tmp2;
	state->recalculate();
}

void Object3d::apply_aerodynamic_force(float32 dt)
{
	const double_t G = 6.67430e-11;
	double_t lim_atmosalt = soibody->atm_limalt;
	double_t p0 = soibody->atm_p0;
	double_t R = 8.31;
	double_t mu = soibody->atm_mu; // molar mass of air
	double_t g = G * soibody->mass / pow(soibody->radius, 2.0); // check
	double_t T = soibody->atm_T; // static and isothermal. For now.

	mat4x4 lrmat = rmat;
	//lrmat.invert();
	//vec3 vel_local = lrmat.transform(velocity);

}

void Object3d::apply_gravity_force(float32 dt)
{
	/*
	VECTOR spos,oldspos;

	if(kosmos.frameskip % 10)
		calculate_soi_body();

	VECTOR tmp;
	if(position.length() < soibody->radius+5.001 && velocity.length()>10.0)
	{
		position = position.normalize() * ( soibody->radius + 5.0 );

		VECTOR vel=velocity;
		VECTOR pos_c=position;
		double_t dot;
		VECTOR newvel, vel_vert;
		// vertical velocity. We want to reverse this and tone it down a bit.
		dot = vel.dot(pos_c.normalize());


		if( dot < 1e-3 )
		{ // going down
			// vertical component of velocity
			vel_vert = pos_c.normalize() * dot ;

			vel -= vel_vert; // cancel out vertical motion
			vel_vert *= 0.05; // arbitrarily lose 95% of the speed

			if( vel_vert.length() > 15.0 ) // don't bounce too much -- aribrarily 15m/s max.
				vel_vert = vel_vert.normalize() * 15.0;

			if( vel_vert.length() < 1.0 ) // too slow. let's just stop.
				vel_vert = VECTOR(0,0,0);

			vel -= vel_vert ;	// reverse vertical component, and scale;
		}

		vel *= friction;

		velocity = vel;
		landed(false);
	}
	else if(position.length() < soibody->radius+5.001 && velocity.length()<=10.0)
	{
		VECTOR A,B,C;
		C = touchdown_points[1] - touchdown_points[0];
		B = touchdown_points[2] - touchdown_points[0];
		A = touchdown_points[2] - touchdown_points[1];

		VECTOR z = VECTOR(0,0,1);


		double_t Cz, Bz, Az;

		Cz = C.dot(z);
		Bz = B.dot(z);
		Az = A.dot(z);

		VECTOR fore;
		if( Cz > Bz && Cz > Az )
			fore = VECTOR(0,0,Cz);
		else if( Bz > Az && Bz > Az )
			fore = VECTOR(0,0,Bz);
		else if( Az > Bz && Az > Cz )
			fore = VECTOR(0,0,Az);

		// The above code does nothing currently.
		// We're assuming that we want the nose plane to be oriented to ground.

		fore=VECTOR(rmat.z);

		VECTOR up=position;
		up.normalize();

		//up = B.cross(C);

		VECTOR left;

		left = fore.cross(up);
		left.normalize();
		fore = left.cross(up);
		fore.normalize();

		MATRIX m;

		m.x[0]=-left.x;
		m.x[1]=-left.y;
		m.x[2]=-left.z;

		m.y[0]=up.x;
		m.y[1]=up.y;
		m.y[2]=up.z;

		m.z[0]=-fore.x;
		m.z[1]=-fore.y;
		m.z[2]=-fore.z;
		//m.firstline = left;
		//m.secondline = up;
		//m.thirdline = fore;
		QUAT q(m);
		rotary.orientation.set(q);
		velocity=VECTOR(0,0,0);
		landed(true);
	}
	else //if(!landed() || velocity.length()>0.0)
	{
		BOOST_FOREACH(GRAVOBJECT *gravobject,starsystem->bodies)
		{
			VECTOR oldacc,newacc;
			VECTOR npos=relative_to_relative(gravobject,this).transform(VECTOR(0,0,0));
			if(gravobject==soibody)
				newacc=rk6_gravity_acceleration(dt,npos,VECTOR(0,0,0),gravobject->mass);
			else
				newacc=gravity_acceleration(npos,VECTOR(0,0,0),gravobject->mass)*dt;
			velocity+=newacc;
		}
		landed(false);
	}

	position+=velocity*dt;
	*/
	velocity += integrate_rk6(dt);
}
vec3 Object3d::gravity_acceleration(const vec3& affected_body_position, const vec3& gravitating_body_position,
	double_t gravitating_body_mass)
{
    vec3 accel;
    return accel;
	//const double_t G = 6.67430e-11;
	//vec3 dir = make_vector<>(position, soibody->position);
	//double_t distance = dir.length();
	//dir.normalise();
	//double_t accel_scalar = (soibody->mass * G) / (distance * distance);
	//vec3 acceleration = dir * accel_scalar;
	//return acceleration;
}
vec3 Object3d::integrate_rk6(float32 dt)
{
	const float32 b21 = 1.0 / 5.0;
	const float32 b31 = 3.0 / 40.0, b32 = 9.0 / 40.0;
	const float32 b41 = 3.0 / 10.0, b42 = -9.0 / 10.0, b43 = 6.0 / 5.0;
	const float32 b51 = -11.0 / 54.0, b52 = 5.0 / 2.0, b53 = -70.0 / 27.0, b54 = 35.0 / 27.0;
	const float32 b61 = 1631.0 / 55296.0, b62 = 175.0 / 512.0, b63 = 575.0 / 13824.0, b64 = 44275.0 / 110592.0, b65 = 253.0 / 4096.0;
	vec3 kx1, kx2, kx3, kx4, kx5, kv1;
	kx1 = gravity_acceleration(position, vec3(0, 0, 0), soibody->mass) * dt;
	kv1 = position + (kx1 * b21);
	kx2 = gravity_acceleration(kv1, vec3(0, 0, 0), soibody->mass) * dt;
	kv1 = position + (kx1 * b31) + (kx2 * b32);
	kx3 = gravity_acceleration(kv1, vec3(0, 0, 0), soibody->mass) * dt;
	kv1 = position + (kx1 * b41) + (kx2 * b42) + (kx3 * b43);
	kx4 = gravity_acceleration(kv1, vec3(0, 0, 0), soibody->mass) * dt;
	kv1 = position + (kx1 * b51) + (kx2 * b52) + (kx3 * b53) + (kx4 * b54);
	kx5 = gravity_acceleration(kv1, vec3(0, 0, 0), soibody->mass) * dt;
	kv1 = position + (kx1 * b61) + (kx2 * b62) + (kx3 * b63) + (kx4 * b64) + (kx5 * b65);
	return gravity_acceleration(kv1, vec3(0, 0, 0), soibody->mass) * dt;
}