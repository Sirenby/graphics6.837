#include "IFS.h"

void IFS::inputIFS(FILE *file){
	for (int i = 0; i < transNum; i++) {
		fscanf(file, "%f", &transProb[i]);
		transMatrices[i].Read3x3(file);		
	}
}

void IFS::renderIFS(Image *image, const int point_num, const int iter_num){
	for (int i = 0; i < point_num; i++) {
		Vec2f v(rand() / (RAND_MAX + 0.0), rand() / (RAND_MAX + 0.0));
		for (int j = 0; j < iter_num; j++) {
			float probility = rand() / (RAND_MAX + 0.0);
			float sum = 0;
			int k = 0;
			for (k = 0;  k < transNum; k++) {
				sum += transProb[k];
				if (sum >= probility)
					break;
			}
			transMatrices[k].Transform(v);
		}
		if (v.x() >= 0 && v.x() <= 1 && v.y() >= 0 && v.y() <= 1)
		{
			float x = v.x()*image->Width();
			float y = v.y()*image->Height();
			image->SetPixel(x, y, Vec3f(v.x(), v.y(), 0.2f));
		}
	}
}
