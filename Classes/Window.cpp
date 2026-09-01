#include "Window.h"
#include <iostream>

Window::Window(const std::string& title, int width, int height)
    : title(title), width(width), height(height),
      window(nullptr), renderer(nullptr)
{
}

Window::~Window()
{
    if (renderer)
        SDL_DestroyRenderer(renderer);

    if (window)
        SDL_DestroyWindow(window);

    SDL_Quit();
}

bool Window::initialize()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cout << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(
        title.c_str(),
        width,
        height,
        0
    );

    if (!window)
    {
        std::cout << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, nullptr);

    if (!renderer)
    {
        std::cout << "SDL_CreateRenderer failed: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void Window::clear()
{
    SDL_RenderClear(renderer);
}

void Window::present()
{
    SDL_RenderPresent(renderer);
}

bool Window::processEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
            return false;
    }

    return true;
}

SDL_Renderer* Window::getRenderer()
{
    return renderer;
}