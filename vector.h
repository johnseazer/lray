#ifndef __VECTOR__
#define __VECTOR__

#include <cmath>

inline double sqr(double n) { return n * n; };

struct Vector {
	
	double x, y, z;
	
	Vector(): x(0), y(0), z(0) {}
	Vector(const Vector& v) : x(v.x), y(v.y), z(v.z) {}
	Vector(double x, double y, double z) : x(x), y(y), z(z) {}
	
	Vector operator - () const { return Vector(-x, -y, -z); }
	Vector operator = (const Vector& v) { x = v.x; y = v.y; z = v.z; return *this; }
	Vector& operator += (const Vector& v) { x += v.x; y += v.y; z += v.z; return *this; }
	Vector& operator -= (const Vector& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
	Vector& operator *= (double f) { x *= f; y *= f; z *= f; return *this; }
	Vector& operator /= (double f) { x /= f; y /= f; z /= f; return *this; }

	double length2() const { return x*x + y*y + z*z; }
	double length() const { return sqrt(length2()); }
	double normalize() { double l = length(); *this /= l; return l; }
	Vector normalized() { Vector v(*this); v.normalize(); return v; }
};

double dot(Vector u, Vector v) { return u.x * v.x + u.y * v.y + u.z * v.z; }

Vector cross(Vector u, Vector v) {
	return Vector(	u.y * v.z - u.z * v.y,
					u.z * v.x - u.x * v.z,
					u.x * v.y - u.y * v.x);
}

inline Vector operator + (const Vector& u, const Vector& v) {
	return Vector(	u.x + v.x,
					u.y + v.y,
					u.z + v.z);
}

inline Vector operator - (const Vector& u, const Vector& v) {
	return Vector(	u.x - v.x,
					u.y - v.y,
					u.z - v.z);
}

inline Vector operator * (const Vector& u, const Vector& v) {
	return Vector(	u.x * v.x,
					u.y * v.y,
					u.z * v.z);
}

inline Vector operator * (const Vector& v, double f) {
	return Vector(	v.x * f,
					v.y * f,
					v.z * f);
}

inline Vector operator * (double f, const Vector& v) {
	return Vector(	f * v.x,
					f * v.y,
					f * v.z);
}

inline Vector operator /(const Vector& u, const Vector& v) {
	return Vector(	u.x / v.x,
					u.y / v.y,
					u.z / v.z);
}

inline Vector operator /(const Vector& u, double f) {
	return Vector(	u.x / f,
					u.y / f,
					u.z / f);
}

inline Vector operator /(double f, const Vector& u) {
	return Vector(	f / u.x,
					f / u.y,
					f / u.z);
}

typedef Vector Point;

struct Vector2 {
	double x, y;

	Vector2() : x(0.0), y(0.0) {}
	Vector2(const Vector2& v) : x(v.x), y(v.y) {}
	Vector2(double x, double y) : x(x), y(y) {}
	Vector2(double f) : x(f), y(f) {}

	Vector2& operator = (const Vector2& v) { x = v.x; y = v.y; return *this; }
};

#endif