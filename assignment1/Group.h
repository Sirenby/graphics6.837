#pragma once
#include "Object3D.h"

class Group :
	public Object3D
{
public:
	Group(int g_index);
	virtual bool intersect(const Ray &r, Hit &h, float tmin);
	void addObject(int index, Object3D *obj);
	~Group();
private:
	Object3D** instances;
	int total_num;
};

