#pragma once

#include "hit.h"
#include "ray.h"
#include "material.h"

class Object3D
{
public:
	Object3D(){}
	~Object3D(){
		delete[] material;
	}
	virtual bool intersect(const Ray &r, Hit &h, float tmin) = 0;
protected:
	Material *material;
};

