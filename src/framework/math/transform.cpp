#include "transform.h"
#include <math.h>

// Transforms can be combined in the same way as matrices and quaternions and the effects of two transforms can be combined into one transform
// To keep things consistent, combining transforms should maintain a right-to-left combination order
Transform combine(const Transform& t1, const Transform& t2)
{
	Transform out;
	out.scale = t1.scale * t2.scale;
	out.rotation = t2.rotation * t1.rotation; // right-to-left multiplication (right is the first rotation applyed)
	// The combined position needs to be affected by the rotation and scale
	out.position = t1.rotation * (t1.scale * t2.position); // M = R*S*T
	out.position = t1.position + out.position;
	return out;
}

mat4 initialize(mat4& m) {
	m.c0r0 = 1;
	m.c1r1 = 1;
	m.c2r2 = 1;
	m.c3r3 = 1;
	m.c0r1 = 0; m.c0r2 = 0; m.c0r3 = 0; // Column 0
	m.c1r0 = 0; m.c1r2 = 0; m.c1r3 = 0; // Column 1
	m.c2r0 = 0; m.c2r1 = 0; m.c2r3 = 0; // Column 2
	m.c3r0 = 0; m.c3r1 = 0; m.c3r2 = 0; // Column 3
	return m;
}

Transform inverse(const Transform& t)
{
	Transform inv;
	inv.rotation = inverse(t.rotation);
	inv.scale.x = fabs(t.scale.x) < VEC3_EPSILON ? 0.0f : 1.0f / t.scale.x;
	inv.scale.y = fabs(t.scale.y) < VEC3_EPSILON ? 0.0f : 1.0f / t.scale.y;
	inv.scale.z = fabs(t.scale.z) < VEC3_EPSILON ? 0.0f : 1.0f / t.scale.z;
	vec3 invTrans = t.position * -1.0f;
	inv.position = inv.rotation * (inv.scale * invTrans);
	return inv;
}

Transform mix(const Transform& a, const Transform& b, float t)
{
	quat bRot = b.rotation;
	if (dot(a.rotation, bRot) < 0.0f) {
		bRot = -bRot;
	}
	return Transform(
		lerp(a.position, b.position, t),
		nlerp(a.rotation, bRot, t),
		lerp(a.scale, b.scale, t));
}

// Extract the rotation and the translition from a matrix is easy. But not for the scale
// M = SRT, ignore the translation: M = SR -> invert R to isolate S
Transform mat4_to_transform(const mat4& m)
{
	Transform transform;
	//Second TODO
	mat4 rotm;
	rotm.c0r0 = m.c0r0;
	rotm.c1r0 = m.c1r0;
	rotm.c0r1 = m.c0r1;
	rotm.c1r1 = m.c1r1;
	rotm.c2r1 = m.c2r1;
	rotm.c2r2 = m.c2r2;
	rotm.c0r2 = m.c0r2;
	rotm.c1r2 = m.c1r2;
	rotm.c2r0 = m.c2r0;
	rotm.c3r0 = 0;
	rotm.c3r1 = 0;
	rotm.c3r2 = 0;
	rotm.c3r3 = 1;
	rotm.c0r3 = 0;
	rotm.c1r3 = 0;
	rotm.c2r3 = 0;

	invert(rotm);
	mat4 escale = m * rotm;

	// TODO
	transform.position = vec3(m.c3r0,m.c3r1,m.c3r2);
	quat rot;
	rot.w = sqrt(1 + m.c0r0 + m.c1r1 + m.c2r2) / 2;
	rot.x = (m.c1r2 - m.c2r1) / (4 * rot.w);
	rot.y = (m.c0r2 - m.c0r2) / (4 * rot.w);
	rot.z = (m.c0r1 - m.c1r0) / (4 * rot.w);
	rot.scalar = rot.w;
	rot.vector = vec3(rot.x, rot.y, rot.z);
	transform.rotation = rot;
	transform.scale = vec3(escale.c0r0, escale.c1r1, escale.c2r2);
	

	return transform;
}

// Converts a transform into a mat4
mat4 transform_to_mat4(const Transform& t)
{
	// TODO
	//following M = SRT

	mat4 tra;
	mat4 rot;
	mat4 scale;
	initialize(tra);
	initialize(rot);
	initialize(scale);
	tra.c3r0 = t.position.x;
	tra.c3r1 = t.position.y;
	tra.c3r2 = t.position.z;

	return mat4();
}

vec3 transform_point(const Transform& a, const vec3& b)
{
	vec3 out;
	out = a.rotation * (a.scale * b);
	out = a.position + out;
	return out;
}

// First, apply the scale, then rotation
vec3 transform_vector(const Transform& t, const vec3& v)
{
	vec3 out;
	out = t.rotation * (t.scale * v);
	return out;
}