#pragma once
#include "Object3D.h"
#include <math.h>
class Sphere : Object3D
{
public:
	Sphere(Vec3f &s_center, float s_radius, Material *s_material);
	virtual bool intersect(const Ray &r, Hit &h, float tmin);
	~Sphere();
private:
	Vec3f center;
	float radius;
};

