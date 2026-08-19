//
// Created by Tjwal on 8/19/2026.
//

#ifndef UNTITLED1_CAMERA_H
#define UNTITLED1_CAMERA_H

#include "Vec3.h"
#include "Ray.h"

class Camera {
private:
    Vec3 position;
    const double image_width;
    const double image_height;
    const double aspect_ratio = image_width / image_height;
    const double viewport_height = 100;
    const double viewport_width = aspect_ratio * viewport_height;
    const double focal_length;
    const double fov = 90;

public:
    Camera(const Vec3& position, double image_width, double image_height, double focal_length);

    // Getters -----------------------

    Vec3 get_position() const;

    double get_width() const;

    double get_height() const;

    double get_ratio() const;

    double get_vp_height() const;

    double get_vp_width() const;

    double get_focal_length() const;

    double get_fov() const;

    // Methods --------------------------

    Ray get_ray_for_pixel(double x, double y) const;

};

#endif //UNTITLED1_CAMERA_H