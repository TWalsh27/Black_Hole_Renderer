#ifndef SPHERE_H
#define SPHERE_H

#include "Vec3.h"
#include "Ray.h"

class Sphere {
private:
    Vec3 center;
    double radius;

public:
    Sphere( const Vec3& center, double radius);

    Vec3 get_center() const;
    double get_radius() const;

    bool check_ray_sphere_intersection( const Ray& Ray);
};

#endif //SPHERE_H