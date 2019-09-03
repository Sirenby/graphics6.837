#include "Plane.h"

Plane::Plane(Vec3f& p_normal, float p_d, Material* p_m) {
	normal = p_normal;
	normal.Normalize();
	d = p_d;
	material = p_m;
}

Plane::Plane(Vec3f& A, Vec3f& B, Vec3f& C, Material* p_m) {
	Vec3f a = A - B;
	Vec3f b = B - C;
	a.Normalize();
	b.Normalize();
	if (a == b) {
		Vec3f v=Vec3f(0, 0, 1);
		Plane pl(v, 0, p_m);
	}
	A.Cross3(normal, A-B, B-C);
	normal.Normalize();
	d = A.Dot3(normal);
	material = p_m;
}

bool Plane::intersect(const Ray& r, Hit& h, float tmin)
{
	bool res = false;
	float t;
	if (r.getDirection().Dot3(normal) != 0) {
		t = (d - r.getOrigin().Dot3(normal)) / (r.getDirection().Dot3(normal));
		res = true;
	}
	else if (r.getOrigin().Dot3(normal) == d) {
		t = 0;
		res = true;
	}
	if (res && t > tmin && t < h.getT()) {
		if (r.getDirection().Dot3(normal) > 0)
			normal *= -1.0f;
		h.set(t, material, normal, r);
		return true;
	}
	return false;
}