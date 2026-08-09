#pragma once

#include <SDL2/SDL.h>
#include <string>

class Window
{
public:
    Window(const std::string& title, int width, int height);
    ~Window();

    bool initialize();

    void clear();
    void present();

    bool processEvents();

    SDL_Renderer* getRenderer();

private:
    std::string title;

    int width;
    int height;

    SDL_Window* window;
    SDL_Renderer* renderer;
};