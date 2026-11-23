#ifndef BLACK_HOLE_RENDERER_MATERIAL_H
#define BLACK_HOLE_RENDERER_MATERIAL_H

#include "Vec3.h"

class Material {
private:

    double reflectivity;
    Vec3 base_color;

public:

    Material();
    Material(double reflectivity, Vec3 base_color);

    double get_reflectivity() const;
    Vec3 get_base_color() const;


};


#endif //BLACK_HOLE_RENDERER_MATERIAL_H