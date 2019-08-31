#include "sphere.h"

Sphere::Sphere(Vec3f &s_center, float s_radius, Material *s_material) {
	center = s_center;
	radius = s_radius;
	material = s_material;
}

bool Sphere::intersect(const Ray &r, Hit &h, float tmin) {
	float a = r.getDirection().Dot3(r.getDirection());
	float b = 2*r.getDirection().Dot3((r.getOrigin() - center));
	float c = (r.getOrigin() - center).Dot3(r.getOrigin() - center) - radius * radius;
	float delta = b * b - 4 * a*c;
	float t;
	if (delta < 0)	return false;
	if (delta == 0) 
		t = -b / 2 * a;
	else if (delta > 0) {
		float t1 = (-b + sqrt(delta)) / 2 / a;
		float t2 = (-b - sqrt(delta)) / 2 / a;
		t = t1 < t2 ? t1 : t2;
	}
	if (t > tmin&&t < h.getT())
		h.set(t, material, r);
	return true;
}

Sphere::~Sphere(){
	delete[] material;
	material = NULL;
}
