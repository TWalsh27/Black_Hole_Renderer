#ifndef SPHERE_H
#define SPHERE_H

#include "Vec3.h"
#include "Ray.h"
#include "Material.h"
#include <utility>
#include <cmath>

class Sphere {
private:
    Vec3 center{};
    double radius{};
    const Material& material{};

public:
    Sphere(const Vec3& center, double radius, const Material& material);

    Vec3 get_center() const;
    double get_radius() const;
    const Material& get_material() const;

    std::pair<double, double> ray_sphere_intersection(const Ray& ray) const;
};

#endif //SPHERE_H