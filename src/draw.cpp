#include <SDL2/SDL.h>
#include "window.h"
void line(int startX, int startY, int endX, int endY) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 225, 225);
    SDL_RenderDrawLine(renderer, startX, startY, endX, endY);
}