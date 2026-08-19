// Last updated 8/10/26

#ifndef UNTITLED1_VEC3_H
#define UNTITLED1_VEC3_H

class Vec3 {

private:

    double x{};
    double y{};
    double z{};

public:

    Vec3();
    Vec3(double x, double y, double z);

    double get_x() const;
    double get_y() const;
    double get_z() const;

    double get_length() const;
    double get_length_squared() const;

    Vec3 add_vectors (const Vec3& other) const;
    Vec3 subtract_vectors (const Vec3& other) const;
    Vec3 multiply_vector (double scalar) const;
    Vec3 divide_vector (double scalar) const;
    Vec3 normalize () const;
    double dot(const Vec3& other) const;
    Vec3 cross(const Vec3& other) const;

    Vec3 operator+(const Vec3& other) const;
    Vec3 operator-(const Vec3& other) const;
    Vec3 operator*(double scalar) const;
    Vec3 operator/(double scalar) const;

};

#endif //UNTITLED1_VEC3_H