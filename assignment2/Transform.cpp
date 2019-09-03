#include "Transform.h"

Transform::Transform(Matrix& m, Object3D* o) 
{
	matrix = m;
	object = o;
}

bool Transform::intersect(const Ray& r, Hit& h, float tmin) 
{
	bool res = false;
	Vec3f ori = r.getOrigin();
	Vec3f dir = r.getDirection();
	Matrix m(matrix);
	if (m.Inverse()) {
		m.Transform(ori);
		m.TransformDirection(dir);
		Ray new_r(ori, dir);
		res= object->intersect(new_r, h, tmin);
		if (res) {
			Vec3f n = h.getNormal();
			m.Transpose();
			m.TransformDirection(n);
			n.Normalize();
			h.set(h.getT(), h.getMaterial(), n, new_r);
		}
	}
	return res;
}