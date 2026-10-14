#ifndef BLACK_HOLE_RENDERER_SCENE_H
#define BLACK_HOLE_RENDERER_SCENE_H

#include "Sphere.h"
#include <vector>

class Scene {
private:

    const std::vector<Sphere> sphere_container;
    const Vec3 light_position;

public:

    Scene(const std::vector<Sphere>& sphere_container, const Vec3& light_position);

    const std::vector<Sphere>& get_sphere_container() const;
    const Vec3& get_light_position() const;
};

#endif //BLACK_HOLE_RENDERER_SCENE_H