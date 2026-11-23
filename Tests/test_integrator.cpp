#include "../Classes/Physics_Classes/Integrator.h"
#include "../Classes/Renderer_Classes/Vec3.h"
#include <iostream>
#include <iomanip>

int main() {
    // Test configuration
    const double M = 0.0;
    const double h = 0.01;
    const int steps = 100;
    const double tolerance = 1e-9;

    // Initial photon conditions
    Vec3 position(10.0, 0.0, 0.0);
    State initial_state{0.1, 0.0};

    // Initialize integrator
    Integrator integrator(position, initial_state, M, h);

    // Perform RK4 integration
    for (int i = 0; i < steps; i++) {
        integrator.RK4();
    }

    // Retrieve numerical solution
    State result = integrator.get_photon_trajectory();

    // Calculate total angular displacement
    double phi = steps * h;

    // Calculate exact analytical solution
    double expected_u = 0.1 * std::cos(phi);
    double expected_v = -0.1 * std::sin(phi);

    // Calculate absolute numerical errors
    double error_u = std::abs(result.u - expected_u);
    double error_v = std::abs(result.v - expected_v);

    // Display test results
    std::cout << std::setprecision(15);

    std::cout << "===== RK4 FLAT SPACE TEST =====\n\n";

    std::cout << "Mass: " << M << '\n';
    std::cout << "Step size: " << h << '\n';
    std::cout << "Steps: " << steps << '\n';
    std::cout << "Final angle: " << phi << "\n\n";

    std::cout << "Computed u: " << result.u << '\n';
    std::cout << "Expected u: " << expected_u << '\n';
    std::cout << "Error u:    " << error_u << "\n\n";

    std::cout << "Computed v: " << result.v << '\n';
    std::cout << "Expected v: " << expected_v << '\n';
    std::cout << "Error v:    " << error_v << "\n\n";

    std::cout << "Tolerance: " << tolerance << "\n\n";

    // Determine whether the test passed
    if (error_u < tolerance && error_v < tolerance) {
        std::cout << "TEST PASSED\n";
        return 0;
    }

    std::cout << "TEST FAILED\n";
    return 1;
}
