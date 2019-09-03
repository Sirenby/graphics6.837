#include <stdlib.h>
#include <iostream>
#include "vectors.h"
#include "matrix.h"
#include "image.h"
#include "IFS.h"
#include "scene_parser.h"
#include "ray.h"
#include "Camera.h"
#include "hit.h"
#include "Group.h"
#include "light.h"

/*assignment0*/
/*int main(int argc, char* argv[])
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
}*/


/*assignment1*/
int main(int argc, char* argv[]){
	char *input_file = NULL;
	int width = 100;
	int height = 100;
	char *output_file = NULL;
	float depth_min = 0;
	float depth_max = 1;
	char *depth_file = NULL;
	char *normal_file = NULL;
	bool shade_back = false;
	// sample command line:
	// raytracer -input scene1_01.txt -size 200 200 -output output1_01.tga -depth 9 10 depth1_01.tga

	for (int i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "-input")) {
			i++; assert(i < argc);
			input_file = argv[i];
		}
		else if (!strcmp(argv[i], "-size")) {
			i++; assert(i < argc);
			width = atoi(argv[i]);
			i++; assert(i < argc);
			height = atoi(argv[i]);
		}
		else if (!strcmp(argv[i], "-output")) {
			i++; assert(i < argc);
			output_file = argv[i];
		}
		else if (!strcmp(argv[i], "-depth")) {
			i++; assert(i < argc);
			depth_min = atof(argv[i]);
			i++; assert(i < argc);
			depth_max = atof(argv[i]);
			i++; assert(i < argc);
			depth_file = argv[i];
		}
		else if (!strcmp(argv[i], "-normals")) {
			i++; assert(i < argc);
			normal_file = argv[i];
		}
		else if (!strcmp(argv[i], "-shade_back"))
		{
			shade_back = true;
		}
		else {
			printf("whoops error with command line argument %d: '%s'\n", i, argv[i]);
			assert(0);
		}
	}

	SceneParser *scene_parse = new SceneParser(input_file);

	Camera *camera = scene_parse->getCamera();
	Vec3f background_color = scene_parse->getBackgroundColor();
	Vec3f ambient_light = scene_parse->getAmbientLight();
	int light_num = scene_parse->getNumLights();
	int material_num = scene_parse->getNumMaterials();
	Group *group = scene_parse->getGroup();
	
	int size = width > height ? width : height;
	Image* image = new Image(size, size);
	Image* depth_image = new Image(size, size);
	Image* normal_image = new Image(size, size);
	image->SetAllPixels(background_color);
	depth_image->SetAllPixels(Vec3f(0,0,0));
	normal_image->SetAllPixels(Vec3f(0, 0, 0));
	
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
		{
			float x = i * 2.0f / size - 1.0f;
			float y = j * 2.0f / size - 1.0f;
			Ray ray = camera->generateRay(Vec2f(x, y));
			Hit* hit = new Hit(INT_MAX, scene_parse->getMaterial(0), Vec3f(0, 0, 0));
			float tmin = 0;
			if (group->intersect(ray, *hit, tmin)) {
				Vec3f hit_color = hit->getMaterial()->getDiffuseColor();
				Vec3f hit_point = ray.pointAtParameter(hit->getT());
				Vec3f normal = hit->getNormal();
				Vec3f pixel_color = Vec3f(hit_color.x() * ambient_light.x(),
					hit_color.y() * ambient_light.y(),
					hit_color.z() * ambient_light.z());

				if (shade_back)
					if (normal.Dot3(ray.getDirection()) > 0)
						normal *= -1.0f;
				/*output*/
				if (normal.Dot3(ray.getDirection()) <= 0) {
					for (int k = 0; k < light_num; k++) {
						Light* light = scene_parse->getLight(k);
						Vec3f light_dir;
						Vec3f light_color;
						light->getIllumination(hit_point, light_dir, light_color);
						float d = light_dir.Dot3(normal);
						if (d < 0)	d = 0;
						pixel_color += d * Vec3f(light_color.x() * hit_color.x(),
							light_color.y() * hit_color.y(),
							light_color.z() * hit_color.z());
					}
					image->SetPixel(i, j, pixel_color);
					/*output*/

					/*normal*/
					Vec3f normal_color = Vec3f(fabs(normal.x()), fabs(normal.y()), fabs(normal.z()));
					normal_image->SetPixel(i, j, normal_color);
					/*normal*/

					/*depth*/
					float t = hit->getT();
					if (t < depth_min)
						t = depth_min;
					else if (t > depth_max)
						t = depth_max;
					float dif = (depth_max - depth_min == 0) ? 1.0f : depth_max - depth_min;
					float grey = (depth_max - t) / dif;
					depth_image->SetPixel(i, j, Vec3f(grey, grey, grey));
					/*depth*/
				}
			}
		}
	}
	if(output_file)
		image->SaveTGA(output_file);
	if(depth_file)
		depth_image->SaveTGA(depth_file);
	if (normal_file)
		normal_image->SaveTGA(normal_file);
}


