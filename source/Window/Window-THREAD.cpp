#include "Window-THREAD.hpp"
#include <chrono>

Window_THREAD::Window_THREAD(int width, int height) :
    Window(width, height){
}

Window_THREAD::~Window_THREAD(){
	pixels.clear();
}

void Window_THREAD::init(){
	running = true;
	std::thread video(_windowThread, w, h, &pixels, &running);
	video.detach();
}

void _windowThread(int width, int height, std::vector<unsigned char> *pixels, bool *running){
	
	int SCREEN_WIDTH = width;
    int SCREEN_HEIGHT = height;
    
	SDL_Window* window = SDL_CreateWindow("RTX", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    	SCREEN_WIDTH, SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
    
	SDL_Event event; 

	auto now = std::chrono::high_resolution_clock::now();
	auto startMs = static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count());

	double elapsed = 0;
	while(*running){

		now = std::chrono::high_resolution_clock::now();
		auto nowMs = static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count());
		
		if(nowMs - startMs > 1.0/60.0){
			startMs = nowMs;
			while( SDL_PollEvent( &event ) )
			{
				if( ( SDL_QUIT == event.type ) ||
					( SDL_KEYDOWN == event.type && SDL_SCANCODE_ESCAPE == event.key.keysym.scancode ) )
				{
					SDL_DestroyRenderer(renderer);
					SDL_DestroyWindow(window);
					SDL_Quit();	
					printf("Window thread terminated.\n");
					*running = false;
					return;
				}
			}
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
			SDL_RenderClear(renderer);
			SDL_UpdateTexture(texture, NULL, &(*pixels)[0], SCREEN_WIDTH*4);
			SDL_RenderCopy(renderer, texture, NULL, NULL);
			SDL_RenderPresent(renderer);
		}
	}
}