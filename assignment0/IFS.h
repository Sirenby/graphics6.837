#pragma once
#include "matrix.h"
#include "image.h"

class IFS{
public:
	IFS(){}
	IFS(int &trans_num){
		transNum = trans_num;
		transMatrices = new Matrix[transNum];
		transProb = new float[transNum];
	}
	~IFS() {
		delete[] transMatrices;
		delete[] transProb;
		transMatrices = NULL;
		transProb = NULL;
	}
	void inputIFS(FILE *file);
	void renderIFS(Image *image, const int point_num, const int iter_num);

private:
	int transNum;//number of ations
	Matrix *transMatrices;//matrices representing the n transformations
	float *transProb;//corresponding probabilities for choosing a transformation
};

