#include "orthographicCamera.h"

OrthographicCamera::OrthographicCamera(Vec3f o_center, Vec3f o_dir, Vec3f o_up, float o_size)
{
	center = o_center;
	direction = o_dir;
	up = o_up;
	size = o_size;

	direction.Normalize();
	up.Normalize();
	up -= direction * (up.Dot3(direction) / up.Length() / direction.Length());
	up.Normalize();
	horizontal.Cross3(horizontal, direction, up);
	horizontal.Normalize();
}

Ray OrthographicCamera::generateRay(Vec2f point)
{
	Vec3f origin = center + horizontal * point.x() * size *0.5 + up * point.y() * size * 0.5;
	return Ray(origin, direction);
}

float OrthographicCamera::getTMin() const
{
	return -1.0f*INT_MAX;
}