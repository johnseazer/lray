#ifndef __IMAGE__
#define __IMAGE__

#include <fstream>

#include "color.h"

class Image {

protected:
	int width;
	int height;
	Color* color;

public:
	Image(int width, int height) : width(width), height(height) {
		color = new Color[width * height];
	}
	virtual ~Image() { delete[] color; }

	int get_width() const { return width; }
	int get_height() const { return height; }
	Color* get_color(int x, int y) { return color + (x + y * width); }

	void save_image(std::string filename) const {

		// Open file
		std::ofstream out(filename);
		
		// Write ppm header
		out << "P3\n" << width << ' ' << height << ' ' << "255\n";

		// Process pixels
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {

				Color px_color = color[x + y * width];
				px_color.clamp();

				// Convert colors to 0~255
				int r = (int) px_color.r * 255.0;
				int g = (int) px_color.g * 255.0;
				int b = (int) px_color.b * 255.0;

				// Write ppm pixel
				out << r << ' ' << g << ' ' << b << '\n';
			}
		}
	}
};

#endif