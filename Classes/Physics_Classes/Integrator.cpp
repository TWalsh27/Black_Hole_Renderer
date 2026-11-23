#include "Integrator.h"

// Constructors -------------------

Integrator::Integrator(const Vec3& photon_position, State photon_trajectory, double black_hole_mass, double step_size) :
    photon_position(photon_position), photon_trajectory(photon_trajectory), black_hole_mass(black_hole_mass), step_size(step_size) {}

// Getters ------------------------

const Vec3& Integrator::get_photon_position() const {
    return photon_position;
}

State Integrator::get_photon_trajectory() const {
    return photon_trajectory;
}

double Integrator::get_black_hole_mass() const {
    return black_hole_mass;
}

double Integrator::get_step_size() const {
    return step_size;
}

// Methods -------------------------

const State Integrator::derive_state(const State& state) {
    double M = black_hole_mass;
    double u = state.u;
    double v = state.v;

    // The following is derived from the formula f(u,v) = {v, 3Mu^2 - u}

    State derived_state{};

    derived_state.u = v;
    derived_state.v = 3 * M * u * u - u;

    return derived_state;
}

// The function below returns the next RK4 step using the formulas described in the notes that I will one day attach to this repo
void Integrator::RK4() {
    State k1 = derive_state(photon_trajectory);
    State k2 = derive_state(photon_trajectory + k1 * (step_size / 2));
    State k3 = derive_state(photon_trajectory + k2 * (step_size / 2));
    State k4 = derive_state(photon_trajectory + k3 * step_size);

    photon_trajectory = (photon_trajectory + (k1 + k2 * 2 + k3 * 2 + k4) * step_size/6);
}

State State::operator+(const State& other) const {
    return {u + other.u, v + other.v};
}

State State::operator-(const State& other) const {
    return {u - other.u, v - other.v};
}

State State::operator*(double scalar) const {
    return {u * scalar, v * scalar};
}

State State::operator/(double scalar) const {
    return {u / scalar, v / scalar};
}