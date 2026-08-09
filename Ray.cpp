//
// Created by Tjwal on 8/8/2026.
//

#include "Ray.h"

// Constructors ----------------------------

Ray::Ray(const Vec3& origin, const Vec3& direction) :
    origin(origin), direction(direction) {}

// Getters ----------------------------------

Vec3 Ray::getOrigin() const {
    return origin;
}

Vec3 Ray::getDirection() const {
    return direction;
}

// Methods -----------------------------------

Vec3 Ray::at(double t) const {
    return origin + direction * t;
}

