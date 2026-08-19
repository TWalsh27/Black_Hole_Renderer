// Last updated 8/10/26

#include "Ray.h"

// Constructors ----------------------------

Ray::Ray() {}

Ray::Ray(const Vec3& origin, const Vec3& direction) :
    origin(origin), direction(direction) {}

// Getters ----------------------------------

Vec3 Ray::get_origin() const {
    return origin;
}

Vec3 Ray::get_direction() const {
    return direction;
}

// Methods -----------------------------------

Vec3 Ray::at(double t) const {
    return origin + direction * t;
}
