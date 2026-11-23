#ifndef BLACK_HOLE_RENDERER_INTEGRATOR_H
#define BLACK_HOLE_RENDERER_INTEGRATOR_H

#include "../Renderer_Classes/Vec3.h"
#include <cmath>

struct State {
    double u;
    double v;

    State operator+(const State& other) const;
    State operator-(const State& other) const;
    State operator*(double scalar) const;
    State operator/(double scalar) const;
};

class Integrator {
private:
    Vec3 photon_position;
    State photon_trajectory;
    double black_hole_mass;
    double step_size;

public:

    Integrator(const Vec3& photon_position, State photon_trajectory, double black_hole_mass, double step_size);

    const Vec3& get_photon_position() const;
    State get_photon_trajectory() const;
    double get_black_hole_mass() const;
    double get_step_size() const;

    const State derive_state(const State& state);
    void RK4();
};

#endif //BLACK_HOLE_RENDERER_INTEGRATOR_H