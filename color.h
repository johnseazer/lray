#ifndef __COLOR__
#define __COLOR__

#include <cmath>

struct Color {

	double r, g, b;

	Color() : r(0.0), g(0.0), b(0.0) {}
	Color(double gray) : r(gray), g(gray), b(gray) {}
	Color(double r, double g, double b) : r(r), g(g), b(b) {}

	void clamp(double min = 0.0, double max = 1.0) {
		r = std::max(min, std::min(max, r));
		g = std::max(min, std::min(max, g));
		b = std::max(min, std::min(max, b));
	}

	Color& operator = (const Color& c) { r = c.r; g = c.g; b = c.b; return *this; }
	Color& operator += (const Color& c) { r += c.r; g += c.g; b += c.b; return *this; }
	Color& operator *= (const Color& c) { r *= c.r; g *= c.g; b *= c.b; return *this; }
	Color& operator *= (double f) { r *= f; g *= f; b *= f; return *this; }
};

inline Color operator + (const Color& c1, const Color& c2) {
	return Color(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b); }

inline Color operator * (const Color& c1, const Color& c2) {
	return Color(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b); }

inline Color operator * (const Color& c, double f) {
	return Color(c.r * f, c.g * f, c.b * f); }

inline Color operator *(double f, const Color& c) {
	return Color(f * c.r, f * c.g, f * c.b); }

#endif