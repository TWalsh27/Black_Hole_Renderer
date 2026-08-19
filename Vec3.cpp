// Last updated 8/10/26

#include "Vec3.h"
#include <cmath>

// Constructors ------------------------------

Vec3::Vec3() {}

Vec3::Vec3(double x, double y, double z) :
    x(x), y(y), z(z) {}

// Getters ------------------------------------

double Vec3::get_x() const {
    return x;
}

double Vec3::get_y() const {
    return y;
}

double Vec3::get_z() const {
    return z;
}

double Vec3::get_length() const {
    return sqrt(get_length_squared());
}

double Vec3::get_length_squared() const {
    return x*x + y*y + z*z;
}

// Methods ------------------------------------------------

Vec3 Vec3::add_vectors(const Vec3& other) const {
    return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::subtract_vectors(const Vec3& other) const {
    return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::multiply_vector(double scalar) const {
    return Vec3(x * scalar, y * scalar, z * scalar);
}

Vec3 Vec3::divide_vector(double scalar) const {
    return Vec3(x / scalar, y / scalar, z / scalar);
}

Vec3 Vec3::normalize() const {
    double length = get_length();

    if (length == 0.0) { // catch div by 0
        return Vec3();
    }

    return Vec3(x / length, y / length, z / length);
}

double Vec3::dot(const Vec3& other) const {
    return x * other.x + y * other.y + z * other.z;
}

Vec3 Vec3::cross(const Vec3& other) const {
    return Vec3(y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x);
}

Vec3 Vec3::operator+(const Vec3& other) const {
    return Vec3(x + other.x,
                y + other.y,
                z + other.z);
}

Vec3 Vec3::operator-(const Vec3& other) const {
    return Vec3(x - other.x,
                y - other.y,
                z - other.z);
}

Vec3 Vec3::operator*(const double scalar) const {
    return Vec3(x * scalar,
                y * scalar,
                z * scalar);
}

Vec3 Vec3::operator/(const double scalar) const {
    return Vec3(x / scalar,
                y / scalar,
                z / scalar);
}
