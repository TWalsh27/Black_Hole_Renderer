#ifndef HITRECORD_H
#define HITRECORD_H

#include "Classes/Vec3.h"
#include "Classes/Sphere.h"

class HitRecord {
private:
    bool hit = false;
    double t{};
    Vec3 point{};
    Vec3 normal{};
    const Sphere * hit_object = nullptr;

public:
    HitRecord();
    HitRecord(bool hit, double t, Vec3 point, Vec3 normal, const Sphere * hit_object);

    bool get_hit_status() const;
    double get_t() const;
    Vec3 get_hit_point() const;
    Vec3 get_normal() const;
    const Sphere * get_hit_object() const;
};

#endif //HITRECORD_H
