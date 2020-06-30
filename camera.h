#ifndef __CAMERA__
#define __CAMERA__

#include "vector.h"
#include "ray.h"

class Camera {

public:
	virtual Ray make_ray(Vector2 point) const = 0;
};

class PerspectiveCamera : public Camera {

	protected:
		Point origin;
		Point forward;
		Vector up;
		Vector right;
		double h, w;

	public:

		PerspectiveCamera(	Point origin,
							Point target,
							Vector upguide,
							double fov,
							double aspect_ratio)
			: origin(origin) {
			forward = (target - origin).normalized();
			right = cross(forward, upguide).normalized();
			up = cross(right, forward);
			h = tan(fov);
			w = h * aspect_ratio;
		}

		virtual Ray make_ray(Vector2 point) const {
			Vector direction = forward + point.x * w * right + point.y * h * up;
			return Ray(origin, direction.normalized());
		}
};

#endif