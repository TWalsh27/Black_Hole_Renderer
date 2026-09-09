#ifndef SPHERE_H
#define SPHERE_H

#include "Vec3.h"
#include "Ray.h"
#include <utility>
#include <cstdint>
#include <cmath>

class Sphere {
private:
    Vec3 center;
    double radius;
    uint32_t color;

public:
    Sphere(const Vec3& center, double radius, uint32_t color);

    Vec3 get_center() const;
    double get_radius() const;
    uint32_t get_color() const;

    std::pair<double, double> ray_sphere_intersection(const Ray& ray);
};

#endif //SPHERE_H