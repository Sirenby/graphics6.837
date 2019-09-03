#pragma once
#include "camera.h"

class OrthographicCamera :
	public Camera
{
public:
	OrthographicCamera(Vec3f o_center,Vec3f o_dir,Vec3f o_up,float o_size);
	virtual Ray generateRay(Vec2f point);
	virtual float getTMin() const;
private:
	Vec3f center;
	Vec3f direction;
	Vec3f up;
	Vec3f horizontal;
	float size;
};

