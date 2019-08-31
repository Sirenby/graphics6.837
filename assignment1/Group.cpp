#include "group.h"

Group::Group(int g_index)
{
	total_num = g_index;
	instances = new Object3D*[total_num];
}

bool Group::intersect(const Ray &r, Hit &h, float tmin) {
	for (int i = 0; i < total_num; i++)
		if (instances[i]->intersect(r, h, tmin))
			return true;
	return false;
}

void Group::addObject(int index, Object3D *obj) {
	instances[index] = obj;
}

Group::~Group()
{
	for (int i = 0; i < total_num; i++) 
		delete[] instances[i];
}
