#ifndef __RAY__
#define __RAY__

#include "vector.h"
#include "color.h"

#define RAY_T_MIN 0.0001
#define RAY_T_MAX 1.0e30

struct Ray {
  Point origin;
  Vector direction;
  double tMax;

  Ray()
  	: origin(0.0, 0.0, 0.0), direction(), tMax(RAY_T_MAX) {}
  Ray(const Ray& r)
  	: origin(r.origin), direction(r.direction), tMax(r.tMax) {}
  Ray(const Point& origin, const Vector& direction, double tMax = RAY_T_MAX)
  	: origin(origin), direction(direction), tMax(tMax) {}

  Ray& operator = (const Ray& r) {
  	origin = r.origin; direction = r.direction; tMax = r.tMax;
  	return *this;
  }
  
  Point calculate(double t) const { return origin + direction * t; }
};

class Shape;

struct Intersection {
	Ray ray;
	double t;
	Shape *shape;
	Color color;

	Intersection() : ray(), t(RAY_T_MAX), shape(NULL) {}
	Intersection(const Intersection& i) : ray(i.ray), t(i.t), shape(i.shape) {}
	Intersection(const Ray& ray) : ray(ray), t(ray.tMax), shape(NULL) {}

	Intersection& operator = (const Intersection &i) {
		ray = i.ray; t = i.t; shape = i.shape;
		return * this;
	}

	bool intersected() const { return (shape != NULL); }
	Point position() const { return ray.calculate(t); }
};


#endif