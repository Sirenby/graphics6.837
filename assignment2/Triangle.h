#pragma once
#include "Object3D.h"
class Triangle :
	public Object3D
{
public:
	Triangle(Vec3f& t_a, Vec3f& t_b, Vec3f& t_c, Material* t_m);
	virtual bool intersect(const Ray& r, Hit& h, float tmin);
private:
	Vec3f A;
	Vec3f B;
	Vec3f C;
	Vec3f normal;
};

