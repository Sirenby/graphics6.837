#pragma once
#include "Object3D.h"
#include "matrix.h"

class Transform :
	public Object3D
{
public:
	Transform(Matrix& m, Object3D* o);
	virtual bool intersect(const Ray& r, Hit& h, float tmin);
private:
	Object3D* object;
	Matrix matrix;
};

