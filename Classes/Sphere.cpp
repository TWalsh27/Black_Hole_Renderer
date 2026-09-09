#include "Sphere.h"

// Constructors ----------------------------

Sphere::Sphere(const Vec3& center, double radius, uint32_t color) :
    center(center), radius(radius), color(color) {}

// Getters ---------------------------------

Vec3 Sphere::get_center() const {
    return center;
}

double Sphere::get_radius() const {
    return radius;
}

uint32_t Sphere::get_color() const {
    return color;
}

// Methods ----------------------------------

std::pair<double, double> Sphere::ray_sphere_intersection(const Ray& ray) const
{
    // This function is used to find all real values t that satisfy the quadratic created
    // when checking for ray sphere intersection points along a given incident ray and sphere

    Vec3 O = ray.get_origin(); // O = Ray Origin
    Vec3 D = ray.get_direction(); // D = Ray Direction
    Vec3 C = get_center(); // C = Sphere Center
    double R = get_radius(); // R = Sphere Radius

    Vec3 Q = O - C; // Q = Ray Origin - Sphere Center

    // Abs(Q + tD)^2 = R^2
    // -> (Q · Q - R^2) + 2t(Q · D) + t^2(D · D) = 0 (zero)

    // The above equation can be written as a quadratic:
    // t^2(D · D) + 2t(Q · D) + (Q · Q - R^2) = 0

    // Using the above equation, we can use this simplified quadratic formula to get our t values:
    // -(Q · D) +- sqrt((Q · D)^2 - (D · D)(Q · Q - R^2)) / (D · D)

    // thus,
    double quad_A = D.dot(D); // A = D · D
    double quad_B = Q.dot(D); // B = Q · D
    double quad_C = Q.dot(Q) - R * R;// C = Q · Q - R^2

    // get the discriminant before passing into sqrt()
    double discriminant = quad_B * quad_B - (quad_A) * (quad_C);

    if (discriminant < 0)
        return {-1, -1}; // magic numbers for now, will improve when I find
    // a better way to implement this case

    // Positive quadratic
    double t_val_1 = (-quad_B + sqrt(discriminant)) / quad_A;

    // Negative quadratic
    double t_val_2 = (-quad_B - sqrt(discriminant)) / quad_A;

    // Return t values (lazily, will improve later)
    return {t_val_1, t_val_2};
}