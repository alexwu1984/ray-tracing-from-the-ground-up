#pragma once

#include "Window.hpp"
#include <chrono>

class Window_NOTHREAD : public Window{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Event event;
    std::chrono::steady_clock::time_point tp_start = std::chrono::high_resolution_clock::now();
    
public:
    Window_NOTHREAD(int width, int height);
    ~Window_NOTHREAD();

    void init();
    void update();
};