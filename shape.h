#ifndef __SHAPE__
#define __SHAPE__

#include <vector>
#include "math.h"
#include "color.h"
#include "ray.h"

class Shape {
	public:
		virtual bool intersect(Intersection& i) = 0;
		virtual bool intersects(const Ray& r) = 0;
};

class ShapeSet : public Shape {
	protected:
		std::vector<Shape*> shapes;

	public:
		ShapeSet() {}

		void addShape(Shape* shape) { shapes.push_back(shape); }

		virtual bool intersect(Intersection& intersection) {
			bool intersects = false;

			for (std::vector<Shape*>::iterator iter = shapes.begin();
				iter != shapes.end();
				++iter) {
				Shape *shape = *iter;
				if (shape->intersect(intersection))
					intersects = true;
			}
			return intersects;
		}
		
		virtual bool intersects(const Ray& ray) {
			for (	std::vector<Shape*>::iterator iter = shapes.begin();
					iter != shapes.end();
					++iter) {
				Shape *shape = *iter;
				if (shape->intersects(ray))
					return true;
			}
			return false;
		}
};

class Sphere : public Shape {

	protected:
	  Point center;
	  double radius;
	  Color color;

	public:
		Sphere(const Point& center, double radius, const Color& color = Color(1.0, 1.0, 1.0))
			: center(center), radius(radius), color(color) {}

		virtual bool intersect(Intersection& intersection) {

			// See sphere centered on origin
			Ray rayc = intersection.ray;
			rayc.origin -= center;

			// Equation
			double a = rayc.direction.length2();
			double b = 2 * dot(rayc.direction, rayc.origin);
			double c = rayc.origin.length2() - sqr(radius);

			// Solutions
			double delta = sqr(b) - 4 * a * c;
			if (delta < 0.0) return false;
			double t1 = (-b - std::sqrt(delta)) / (2 * a);
			double t2 = (-b + std::sqrt(delta)) / (2 * a);

			// Check validity
			if (t1 > RAY_T_MIN && t1 < intersection.t) intersection.t = t1;
			else if (t2 > RAY_T_MIN && t2 < intersection.t) intersection.t = t2;
			else return false;

			// Complete intersection
			intersection.shape = this;
			intersection.color = color;
			return true;
		}

		virtual bool intersects(const Ray& ray) {
	    	
	    	// See sphere centered on origin
			Ray rayc = ray;
			rayc.origin -= center;

			// Equation
			double a = rayc.direction.length2();
			double b = 2 * dot(rayc.direction, rayc.origin);
			double c = rayc.origin.length2() - sqr(radius);

			// Solutions
			double delta = sqr(b) - 4 * a * c;
			if (delta < 0.0) return false;
			double t1 = (-b - std::sqrt(delta)) / (2 * a);
			if (t1 > RAY_T_MIN && t1 < ray.tMax) return true;
			double t2 = (-b + std::sqrt(delta)) / (2 * a);
			if (t2 > RAY_T_MIN && t2 < ray.tMax) return true;
			return false;
		}
};

#endif