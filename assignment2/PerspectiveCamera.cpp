#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(Vec3f& p_center, Vec3f& p_direction, Vec3f& p_up, float p_angle)
{
	center = p_center;
	direction = p_direction;
	up = p_up;
	angle = p_angle;

	direction.Normalize();
	up.Normalize();
	up -= direction * (up.Dot3(direction) / up.Length() / direction.Length());
	up.Normalize();
	horizontal.Cross3(horizontal, direction, up);
	horizontal.Normalize();
	distance = 1.0f / tan(angle / 2.0f);
}

Ray PerspectiveCamera::generateRay(Vec2f point)
{
	Vec3f dir = horizontal * point.x() + up * point.y() + direction * distance;
	dir.Normalize();
	return Ray(center, dir);
}

float PerspectiveCamera::getTMin() const
{
	return -1.0f * INT_MAX;
}