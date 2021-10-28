#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <glad/glad.h>
#include <iostream>

bool cursorInArea(const SDL_Rect& rect, int x, int y)
{
    return ((x >= rect.x && x <= rect.x + rect.w) && (y >= rect.y && y <= rect.y + rect.h));
}

SDL_Rect sdlRect;

SDL_HitTestResult hitCallback(SDL_Window* win, const SDL_Point* area, void* data) {
    if (cursorInArea(sdlRect, area->x, area->y)) {
        return (SDL_HITTEST_DRAGGABLE);
    }
}

void srcpool_drag(SDL_Rect bar, SDL_Window* window) {
    sdlRect = bar;
    SDL_SetWindowHitTest(window, hitCallback, 0);
}

int setGLAttributes() {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

    return 0;
}

int setIcon(SDL_Window* window) {
    SDL_Surface* icon = IMG_Load("images\\icon.png");
    if (icon == NULL) {
        std::cout << SDL_GetError() << std::endl;
    }
    else {
        std::cout << "image loaded" << std::endl;
    }
    SDL_SetWindowIcon(window, icon);
}