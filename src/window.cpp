#include <SDL2/SDL.h>
#include <iostream>
#include "window.h"
#include "draw.h"
#include "logic.h"

bool windowOpen = true;

SDL_Window* g_window = NULL;
SDL_Renderer* renderer = NULL;

int window() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        std::cout << "SDL library failed to initialize" << std::endl;
        std::cout << "Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    g_window = SDL_CreateWindow("cube", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);

    if (!g_window) {
        std::cout << "window failed" << std::endl;
        std::cout << "Error: " << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

	if (!renderer) {
		std::cout << "failed to make a renderer for the window\n";
		std::cout << "Error: " << SDL_GetError() << "\n";
		return -1;
	}

    //line(0, 0, 100, 100);

    SDL_Event e;
    while (windowOpen) {
        const Uint8* state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_RIGHT]) {
            angleY += 0.01;
            if (angleY >= 360.0) {
                angleY -= 360.0;
            }
        } else if (state[SDL_SCANCODE_LEFT]) {
            angleY -= 0.01;
            if (angleY >= 0.0) {
                angleY += 360.0;
            }
        }
        if (state[SDL_SCANCODE_UP]) {
            angleX += 0.01;
            if (angleX >= 360.0) {
                angleX -= 360;
            }
        } else if (state[SDL_SCANCODE_DOWN]) {
            angleX -= 0.01;
            if (angleX >= 0.0) {
                angleX += 360.0;
            }
        }
        renderCube();
        SDL_RenderPresent(renderer);
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                windowOpen = false;
            }
            SDL_UpdateWindowSurface(g_window);
        }
        SDL_Delay(20);
    }
    return 0;
}