#include "Triangle.h"
#include "Plane.h"

Triangle::Triangle(Vec3f& t_a, Vec3f& t_b, Vec3f& t_c, Material* t_m) 
{
	A = t_a;
	B = t_b;
	C = t_c;
	A.Cross3(normal, A - B, B - C);
	normal.Normalize();
	material = t_m;
}

bool Triangle::intersect(const Ray& r, Hit& h, float tmin)
{
	Plane p(A, B, C, material);
	Hit t_h(h);
	
	if (p.intersect(r, t_h, tmin)) {
		Vec3f P = r.getOrigin() + t_h.getT() * r.getDirection();
		Vec3f t1, t2;
		t1.Cross3(t1, A - C, P - A);
		t2.Cross3(t2, A - C, B - A);
		if (t1.Dot3(t2) < 0)	return false;
		t1.Cross3(t1, B - A, P - B);
		t2.Cross3(t2, B - A, C - B);
		if (t1.Dot3(t2) < 0)	return false;
		t1.Cross3(t1, C - B, P - C);
		t2.Cross3(t2, C - B, A - C);
		if (t1.Dot3(t2) < 0)	return false;
		h.set(t_h.getT(), material, t_h.getNormal(), r);
		return true;
	}
	return false;
}
