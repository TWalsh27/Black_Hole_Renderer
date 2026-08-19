//
// Created by Tjwal on 8/19/2026.
//

#include "Camera.h"
#include <cmath>
#include <numbers>

// Constructors ---------------------

Camera::Camera(const Vec3& position, const double image_width, const double image_height, const double focal_length) :
    position(position), image_width(image_width), image_height(image_height), focal_length(focal_length) {}

// Methods ---------------------------

Vec3 Camera::get_position() const {
    return position;
}

double Camera::get_width() const {
    return image_width;
}

double Camera::get_height() const {
    return image_height;
}

double Camera::get_ratio() const {
    return aspect_ratio;
}

double Camera::get_vp_height() const {
    return viewport_height;
}

double Camera::get_vp_width() const {
    return viewport_width;
}

double Camera::get_focal_length() const {
    return focal_length;
}

double Camera::get_fov() const {
    return fov;
}

// Methods -------------------------------

Ray Camera::get_ray_for_pixel(const double x, const double y) const {

    const double width = get_width();
    const double height = get_height();
    const double fov = get_fov();

    // get pixels to Normalized Device Coordinates using NDC formulas
    const double ndc_x = (2 * x + 1) / width - 1;
    const double ndc_y = 1 - (2 * y + 1) / height;

    // get viewport x and y values from NDC values
    // viewport z set at -1 to account for being 1 unit away from the camera and looking down the z axis
    const double vp_x = ndc_x * tan((fov * std::numbers::pi/180)/2) * get_ratio();
    const double vp_y = ndc_y * tan((fov * std::numbers::pi/180)/2);
    const double vp_z = -1;

    // now that we have VP values, this function creates a viewport point vector
    // this VP vector allows us to get the unit direction element after a normalization
    Vec3 viewport_point(vp_x, vp_y, vp_z);
    Vec3 direction = viewport_point - get_position();
    Vec3 unit_direction = direction.normalize();

    Ray result_ray(get_position(), unit_direction);

    return result_ray;
}