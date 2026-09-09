#include <SDL3/SDL.h>
#include <iostream>
#include "Classes/Vec3.h"
#include <vector>
#include <cstdint>
#include "Classes/Ray.h"
#include "Classes/Camera.h"
#include "Classes/Sphere.h"
#include "Classes/Window.h"

// this function is a temporary measure to clean up repeated code in main
uint32_t get_pixel(const double r, const double g, const double b) {
    // cast them to uint8_t
    uint8_t a = 255;
    uint8_t casted_r = static_cast<uint8_t> (r * 255);
    uint8_t casted_g = static_cast<uint8_t> (g * 255);
    uint8_t casted_b = static_cast<uint8_t> (b * 255);

    // bit shift them into uint32 value
    uint32_t pixel = (a << 24) | (casted_r << 16) | (casted_g << 8) | casted_b;

    return pixel;
}

const int WIDTH = 800, HEIGHT = 600;

int main(int argc, char* argv[]) {

    Camera Camera(Vec3(0,0,0), 800, 600, 90);

    Sphere Sphere(Vec3(0,0,-5), 1, 0xFFFF0000);

    Vec3 light_position(-6, -2, 0);

    // Allocate memory for pixel buffer

    std::vector<uint32_t> buffer_Mem(WIDTH * HEIGHT);

    // Creates a color gradient using Vec3 RGB

    for (double y = 0; y < HEIGHT; y++) {
        for (double x = 0; x < WIDTH; x++) {
            int index = y * WIDTH + x;

            Ray current_ray {};
            current_ray = Camera.get_ray_for_pixel(x,y);
            std::pair<double, double> intersects = Sphere.ray_sphere_intersection(current_ray);
            Vec3 current_direction = current_ray.get_direction();
            double chosen_intersect = -1;

            // The below code retrieves the minimum positive value of the pair. I'll clean it up later
            if (intersects.first > 0)
                chosen_intersect = intersects.first;
            if (intersects.second > 0 && intersects.second < intersects.first)
                chosen_intersect = intersects.second;

            if (chosen_intersect != -1) { // hit
                // get 3D face
                Vec3 hit_point = current_ray.at(chosen_intersect);
                Vec3 normal = (hit_point - Sphere.get_center()).normalize();

                // get brightness from light position and hit
                Vec3 light_direction = (light_position - hit_point).normalize();
                double brightness = std::max(double(0), normal.dot(light_direction));

                uint32_t sphere_color = Sphere.get_color();

                // Use sphere color and bit shifting to isolate RGB values.
                // Then multiply by 255 to get the RBG values into standard form
                // Finally, multiply by the dirived brightness value and send into the get_pixel function
                auto r = ((sphere_color >> 16) & 0xFF) / 255.0 * brightness;
                auto g = ((sphere_color >> 8) & 0xFF) / 255.0 * brightness;
                auto b = (sphere_color & 0xFF) / 255.0 * brightness;

                uint32_t pixel = get_pixel(r,g,b);

                // Write pixel data to memory and map onto frame
                buffer_Mem[index] = pixel;
            }
            else { // miss
                auto r = (current_direction.get_x() + 1) / 2;
                auto g = (current_direction.get_y() + 1) / 2;
                auto b = (current_direction.get_z() + 1) / 2;

                uint32_t pixel = get_pixel(r,g,b);

                buffer_Mem[index] = pixel; // map onto frame
            }
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
