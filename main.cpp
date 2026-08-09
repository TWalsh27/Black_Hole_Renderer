#include <SDL.h>
#include <iostream>
#include "Vec3.h"
#include "Ray.h"

#include "Window.h"

const int WIDTH = 800, HEIGHT = 600;

int main(int argc, char* argv[]) {


    // -----------------------------------------
    // Constructors
    // -----------------------------------------

    Vec3 a(1.0, 2.0, 3.0);
    Vec3 b(4.0, 5.0, 6.0);

    std::cout << "a = ("
              << a.getX() << ", "
              << a.getY() << ", "
              << a.getZ() << ")\n";

    std::cout << "b = ("
              << b.getX() << ", "
              << b.getY() << ", "
              << b.getZ() << ")\n\n";


    // -----------------------------------------
    // Addition
    // -----------------------------------------

    Vec3 add = a + b;

    std::cout << "a + b = ("
              << add.getX() << ", "
              << add.getY() << ", "
              << add.getZ() << ")\n";


    // -----------------------------------------
    // Subtraction
    // -----------------------------------------

    Vec3 subtract = a - b;

    std::cout << "a - b = ("
              << subtract.getX() << ", "
              << subtract.getY() << ", "
              << subtract.getZ() << ")\n";


    // -----------------------------------------
    // Scalar multiplication
    // -----------------------------------------

    Vec3 multiply = a * 2.0;

    std::cout << "a * 2 = ("
              << multiply.getX() << ", "
              << multiply.getY() << ", "
              << multiply.getZ() << ")\n";


    // -----------------------------------------
    // Scalar division
    // -----------------------------------------

    Vec3 divide = a / 2.0;

    std::cout << "a / 2 = ("
              << divide.getX() << ", "
              << divide.getY() << ", "
              << divide.getZ() << ")\n";


    // -----------------------------------------
    // Length
    // -----------------------------------------

    Vec3 lengthTest(3.0, 4.0, 0.0);

    std::cout << "\nLength of (3,4,0): "
              << lengthTest.getLength() << '\n';

    std::cout << "Length squared: "
              << lengthTest.getLengthSquared() << '\n';


    // -----------------------------------------
    // Normalization
    // -----------------------------------------

    Vec3 normalized = lengthTest.normalize();

    std::cout << "\nNormalized (3,4,0) = ("
              << normalized.getX() << ", "
              << normalized.getY() << ", "
              << normalized.getZ() << ")\n";

    std::cout << "Normalized length: "
              << normalized.getLength() << '\n';


    // -----------------------------------------
    // Dot product
    // -----------------------------------------

    Vec3 x(1.0, 0.0, 0.0);
    Vec3 y(0.0, 1.0, 0.0);

    std::cout << "\nX dot Y = "
              << x.dot(y) << '\n';


    // -----------------------------------------
    // Cross product
    // -----------------------------------------

    Vec3 cross = x.cross(y);

    std::cout << "X cross Y = ("
              << cross.getX() << ", "
              << cross.getY() << ", "
              << cross.getZ() << ")\n";


    // -----------------------------------------
    // Ray-style calculation
    // -----------------------------------------

    Vec3 origin(1.0, 2.0, 3.0);
    Vec3 direction(4.0, 5.0, 6.0);

    double t = 2.0;

    Vec3 point = origin + direction * t;

    std::cout << "\nRay point at t = 2: ("
              << point.getX() << ", "
              << point.getY() << ", "
              << point.getZ() << ")\n";

    /*

    Window Test_Window("Test Window", WIDTH, HEIGHT);

    Test_Window.initialize();

    bool running = true;

    SDL_Event event;

    while (running) {
        running = Test_Window.processEvents();
        Test_Window.clear();
        Test_Window.present();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
        }
    }

    */

    return 0;
}
