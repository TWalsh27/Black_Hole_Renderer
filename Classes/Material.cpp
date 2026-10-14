#include "Material.h"

// constructors --------------

Material::Material() :
    reflectivity(0.00), base_color(1.0,1.0,1.0) {}

Material::Material(double reflectivity, Vec3 base_color) :
    reflectivity(reflectivity), base_color(base_color) {}

// Getters -------------------

double Material::get_reflectivity() const {
    return reflectivity;
}

Vec3 Material::get_base_color() const {
    return base_color;
}
