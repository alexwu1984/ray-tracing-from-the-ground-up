#include "Window-NOTHREAD.hpp"

Window_NOTHREAD::Window_NOTHREAD(int width, int height):
    Window(width, height) {
}

Window_NOTHREAD::~Window_NOTHREAD(){
	pixels.clear();
}

void Window_NOTHREAD::init(){
    window = SDL_CreateWindow("RTX", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    	w, h,SDL_WINDOW_SHOWN);
    
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, w, h);

    running = true;
    tp_start = std::chrono::high_resolution_clock::now();
}

void Window_NOTHREAD::update(){

	auto now = std::chrono::high_resolution_clock::now();
	auto nowMs = static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count());
    auto startMs = static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(tp_start.time_since_epoch()).count());
    if(running && (nowMs - startMs) > 1.0f / 60.0f) {

        tp_start = now;
        
        while( SDL_PollEvent( &event ) )
        {
            if( ( SDL_QUIT == event.type ) ||
                ( SDL_KEYDOWN == event.type && SDL_SCANCODE_ESCAPE == event.key.keysym.scancode ) )
            {
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();	
                running = false;
                return;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        SDL_UpdateTexture(texture, NULL, &pixels[0], w*4);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
}