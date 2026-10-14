#include "Scene.h"

// Constructors ----------------

Scene::Scene(const std::vector<Sphere>& sphere_container, const Vec3& light_position) :
    sphere_container(sphere_container), light_position(light_position) {}

// Getters ---------------------

const std::vector<Sphere>& Scene::get_sphere_container() const {
    return sphere_container;
}

const Vec3& Scene::get_light_position() const {
    return light_position;
}