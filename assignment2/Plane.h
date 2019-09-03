#pragma once
#include "Object3D.h"
class Plane :
	public Object3D
{
public:
	Plane(Vec3f& p_normal, float p_d, Material* p_m);
	Plane(Vec3f& A, Vec3f& B, Vec3f& C, Material* p_m);
	virtual bool intersect(const Ray& r, Hit& h, float tmin);
private:
	Vec3f normal;
	float d;
};

