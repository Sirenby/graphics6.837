#include <stdlib.h>
#include <iostream>
#include "vectors.h"
#include "matrix.h"
#include "image.h"
#include "IFS.h"

// ========================================================
// ========================================================
// Some sample code you might like to use for parsing 
// command line arguments and the input IFS files

// sample command line:
// ifs -input fern.txt -points 10000 -iters 10 -size 100 -output fern.tga

int main(int argc, char* argv[])
{
	char *input_file = NULL;
	int num_points = 10000;
	int num_iters = 10;
	int size = 100;
	char *output_file = NULL;

	for (int i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "-input")) {
			i++; assert(i < argc);
			input_file = argv[i];
		}
		else if (!strcmp(argv[i], "-points")) {
			i++; assert(i < argc);
			num_points = atoi(argv[i]);
		}
		else if (!strcmp(argv[i], "-iters")) {
			i++; assert(i < argc);
			num_iters = atoi(argv[i]);
		}
		else if (!strcmp(argv[i], "-size")) {
			i++; assert(i < argc);
			size = atoi(argv[i]);
		}
		else if (!strcmp(argv[i], "-output")) {
			i++; assert(i < argc);
			output_file = argv[i];
		}
		else {
			printf("whoops error with command line argument %d: '%s'\n", i, argv[i]);
			assert(0);
		}
	}

	Image *image = new Image(size, size);
	image->SetAllPixels(Vec3f(0, 0, 0));

	FILE *input = fopen(input_file, "r");
	assert(input != NULL);

	int num_transforms;
	fscanf(input, "%d", &num_transforms);

	IFS *ifs = new IFS(num_transforms);
	ifs->inputIFS(input);
	fclose(input);
	ifs->renderIFS(image, num_points, num_iters);
	image->SaveTGA(output_file);

	system("pause");
}
