#include "HitRecord.h"

// Constructors -------------------------

HitRecord::HitRecord() {}

HitRecord::HitRecord(bool hit, double t, Vec3 point, Vec3 normal, const Sphere * hit_object) :
    hit(hit), t(t), point(point), normal(normal), hit_object(hit_object) {}

// Getters ------------------------------

bool HitRecord::get_hit_status() const {
    return hit;
}

double HitRecord::get_t() const {
    return t;
}

Vec3 HitRecord::get_hit_point() const {
    return point;
}

Vec3 HitRecord::get_normal() const
{
    return normal;
}

const Sphere * HitRecord::get_hit_object() const {
    return hit_object;
}

// Methods --------------------------------


