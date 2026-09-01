#ifndef SPHERE_H
#define SPHERE_H

#include "Vec3.h"
#include "Ray.h"
#include <utility>

class Sphere {
private:
    Vec3 center;
    double radius;

public:
    Sphere(const Vec3& center, double radius);

    Vec3 get_center() const;
    double get_radius() const;

    std::pair<double, double> ray_sphere_intersection(const Ray& ray);
};

#endif //SPHERE_H