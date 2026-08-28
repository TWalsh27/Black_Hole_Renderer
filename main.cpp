// Main is currently being used to test the newly implemented ray_sphere_intersection function
// As of 8/27/26, all tests pass successfully

#include <iostream>
#include <iomanip>
#include "Vec3.h"
#include "Ray.h"
#include "Sphere.h"

void print_test_result(const std::string& name,
                       const std::pair<double, double>& result)
{
    std::cout << name << "\n";
    std::cout << "t1 = " << result.first << "\n";
    std::cout << "t2 = " << result.second << "\n";
    std::cout << "--------------------------------\n";
}

int main() {

    // ---------------------------------------------------------
    // Test 1: Direct hit
    // Sphere: center (0, 0, -5), radius 1
    // Ray:    origin (0, 0, 0), direction (0, 0, -1)
    //
    // Expected: t = 4 and t = 6
    // ---------------------------------------------------------

    Sphere sphere1(Vec3(0, 0, -5), 1);
    Ray ray1(Vec3(0, 0, 0), Vec3(0, 0, -1));

    auto result1 = sphere1.ray_sphere_intersection(ray1);

    print_test_result("TEST 1: Direct Hit", result1);


    // ---------------------------------------------------------
    // Test 2: Tangent
    // Sphere: center (1, 0, -5), radius 1
    // Ray:    origin (0, 0, 0), direction (0, 0, -1)
    //
    // Expected: t = 5 and t = 5
    // ---------------------------------------------------------

    Sphere sphere2(Vec3(1, 0, -5), 1);
    Ray ray2(Vec3(0, 0, 0), Vec3(0, 0, -1));

    auto result2 = sphere2.ray_sphere_intersection(ray2);

    print_test_result("TEST 2: Tangent", result2);


    // ---------------------------------------------------------
    // Test 3: Miss
    // Sphere: center (2, 0, -5), radius 1
    // Ray:    origin (0, 0, 0), direction (0, 0, -1)
    //
    // Expected: discriminant < 0
    // ---------------------------------------------------------

    Sphere sphere3(Vec3(2, 0, -5), 1);
    Ray ray3(Vec3(0, 0, 0), Vec3(0, 0, -1));

    auto result3 = sphere3.ray_sphere_intersection(ray3);

    print_test_result("TEST 3: Miss", result3);


    // ---------------------------------------------------------
    // Test 4: Sphere behind ray
    // Sphere: center (0, 0, 5), radius 1
    // Ray:    origin (0, 0, 0), direction (0, 0, -1)
    //
    // Expected: two negative t values
    // ---------------------------------------------------------

    Sphere sphere4(Vec3(0, 0, 5), 1);
    Ray ray4(Vec3(0, 0, 0), Vec3(0, 0, -1));

    auto result4 = sphere4.ray_sphere_intersection(ray4);

    print_test_result("TEST 4: Sphere Behind Ray", result4);


    return 0;
}








/*

#include <SDL3/SDL.h>
#include <iostream>
#include "Vec3.h"
#include <vector>
#include <cstdint>
#include "Ray.h"
#include "Camera.h"

#include "Window.h"

const int WIDTH = 800, HEIGHT = 600;

int main(int argc, char* argv[]) {

    /* Camera Camera(Vec3(0,0,0), 800, 600, 90);

    // Allocate memory for pixel buffer

    std::vector<uint32_t> buffer_Mem(WIDTH * HEIGHT);

    // Creates a color gradient using Vec3 RGB

    for (double y = 0; y < HEIGHT; y++) {
        for (double x = 0; x < WIDTH; x++) {
            int index = y * WIDTH + x;

            Ray current_ray {};
            current_ray = Camera.get_ray_for_pixel(x,y);

            Vec3 current_direction = current_ray.get_direction();

            auto r = (current_ray.get_direction().get_x() + 1) / 2;
            auto g = (current_ray.get_direction().get_y() + 1) / 2;
            auto b = (current_ray.get_direction().get_z() + 1) / 2;

            uint8_t a = 255;
            uint8_t casted_r = static_cast<uint8_t> (r * 255);
            uint8_t casted_g = static_cast<uint8_t> (g * 255); // cast them to uint8_t
            uint8_t casted_b = static_cast<uint8_t> (b * 255);

            uint32_t pixel = (a << 24) | (casted_r << 16) | (casted_g << 8) | casted_b; // bit shift them into uint32 value

            buffer_Mem[index] = pixel; // map onto frame
        }
    }

    Window Test_Window("Test Window", WIDTH, HEIGHT);

    Test_Window.initialize();

    SDL_Texture * texture = SDL_CreateTexture(Test_Window.getRenderer(),
                                    SDL_PIXELFORMAT_ARGB8888,
                                    SDL_TEXTUREACCESS_STREAMING,
                                    WIDTH, HEIGHT);

    SDL_UpdateTexture(texture, nullptr, buffer_Mem.data(), WIDTH * sizeof(uint32_t));

    bool running = true;

    SDL_Event event;

    while (running) {
        Test_Window.clear();
        SDL_RenderTexture(Test_Window.getRenderer(), texture, nullptr, nullptr);
        Test_Window.present();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT)
                running = false;
        }
    }

    return 0;
}

*/