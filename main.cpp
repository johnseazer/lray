/* main.cpp */

#define _USE_MATH_DEFINES

#include <fstream>
#include <iostream>
#include <unistd.h>
#include <math.h>

#include "json/json.h"

#include "vector.h"
#include "ray.h"
#include "shape.h"
#include "camera.h"
#include "color.h"
#include "image.h"

using namespace std;

struct Opts {
	int level;
	const char * in;
	const char * out;
};

void usage() {
	cout <<
		"\n"
		"Usage\t\tlray -n <level> -i <source> -o <destination>\n\n"
		"<level>\t\ttracing level (1)\n"
		"<source>\tpath to json file with scene data\n"
		"<destination>\tpath to ppm file to which the image will be saved\n" << endl;
}

void trace(Image& image, Camera* camera, Shape* objects) {
	for (int x = 0; x < image.get_width(); x++) {
		for (int y = 0; y < image.get_height(); y++) {

			Vector2 screen_coords(
				( 2.0 * x) / image.get_width()  - 1.0,
				(-2.0 * y) / image.get_height() + 1.0);
			
			Ray ray = camera->make_ray(screen_coords);
			Color *px = image.get_color(x, y);
			Intersection intersection(ray);

			if (objects->intersect(intersection)) {
				*px = intersection.color;
			}
			else *px = Color(0.0);
		}
	}
}


int main(int argc, char * argv[]) {

	// Parse Command Line Arguments

	Opts opts;

	int opt;
	static const char* optstring = "n:i:o:";
	while ((opt = getopt(argc, argv, optstring)) != -1) {
		switch(opt) {
			case 'n':
				opts.level = stoi(optarg);
				break;
			case 'i':
				opts.in = optarg;
				break;
			case 'o':
				opts.out = optarg;
				break;
			case '?':
				usage();
				return EXIT_FAILURE;
			default:
				abort();
		}
	}

	// Open Json
	
	clog << "Opening scene data" << endl;

	ifstream ifs(opts.in);

	Json::Value root;
	JSONCPP_STRING errs;
	Json::CharReaderBuilder builder;

	if (!parseFromStream(builder, ifs, &root, &errs)) {
		cerr << "Error reading " << opts.in << ", please verify integrity of the file" << endl;
		cout << errs << endl;
		return EXIT_FAILURE;
	}

	// Init Image

	int width = 800;
	int height = 800;
	Image image(width, height);

	// Extract Camera from Json
	
	clog << "Extracting camera data" << endl;

	const Json::Value& cam = root["cameras"][0];

	PerspectiveCamera camera(
		Point(cam["ox"].asDouble(), cam["oy"].asDouble(), cam["oz"].asDouble()),
		Point(cam["tx"].asDouble(), cam["ty"].asDouble(), cam["tz"].asDouble()),
		Vector(0.0, 1.0, 0.0),
		25.0 * M_PI / 180.0,
		(double) width / (double) height
	);

	// Extract Objects from Json
	
	clog << "Extracting objects data" <<endl;

	ShapeSet objects;
	const Json::Value& objs = root["objects"];

	for (int i = 0; i < objs.size(); i++) {
		const Json::Value& obj = objs[i];

		// Sphere
		if(obj["type"].asString() == "sphere") {
			Sphere* sphere = new Sphere (
				Point(obj["cx"].asDouble(), obj["cy"].asDouble(), obj["cz"].asDouble()),
				obj["radius"].asDouble(),
				Color(obj["r"].asDouble(), obj["g"].asDouble(), obj["b"].asDouble())
			);
			objects.addShape(sphere);
		}
	}

	// Ray Trace
	clog << "Ray tracing" << endl;
	trace(image, &camera, &objects);

	// Save Image
	clog << "Saving image" << endl;
	image.save_image(opts.out);

	clog << "Done" << endl;
	return EXIT_SUCCESS;
}