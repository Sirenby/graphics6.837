#pragma once
#include "Camera.h"
class PerspectiveCamera :
	public Camera
{
public:
	PerspectiveCamera(Vec3f& p_center, Vec3f& p_direction, Vec3f& p_up, float p_angle);
	virtual Ray generateRay(Vec2f point);
	virtual float getTMin() const;
private:
	Vec3f center;
	Vec3f direction;
	Vec3f up;
	Vec3f horizontal;
	float angle;
	float distance;
};

