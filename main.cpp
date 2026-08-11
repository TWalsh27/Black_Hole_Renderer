// Last updated 8/10/26

#include <SDL3/SDL.h>
#include <iostream>
#include "Vec3.h"
#include <vector>
#include <cstdint>
#include "Ray.h"

#include "Window.h"

const int WIDTH = 800, HEIGHT = 600;

int main(int argc, char* argv[]) {

    std::vector<uint32_t> buffer_Mem(WIDTH * HEIGHT);

    for (auto y = 0; y < HEIGHT; y++) {
        for (auto x = 0; x < WIDTH; x++) {
            int index = y * WIDTH + x;
            auto u = static_cast<double> (x) / (WIDTH - 1);
            auto v = static_cast<double> (y) / (HEIGHT - 1);

            Vec3 color(u, v, 0.0);
            auto r = color.getX();
            auto g = color.getY(); // get RGB values from vector
            auto b = color.getZ();

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
