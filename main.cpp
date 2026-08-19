// Last updated 8/10/26

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

    Camera Camera(Vec3(0,0,0), 800, 600, 90);

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
