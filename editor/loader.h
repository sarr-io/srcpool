// Standard
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

// SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// OpenGL
#include <glad/glad.h>
#include <GL/gl.h>


// Variables
SDL_Rect sdlRect;
// add array of lines of text index acts as line #, value acts as the line's string

// Functions
bool cursorInArea(const SDL_Rect& rect, int x, int y)
{
    return ((x >= rect.x && x <= rect.x + rect.w) && (y >= rect.y && y <= rect.y + rect.h));
}

SDL_HitTestResult hitCallback(SDL_Window* win, const SDL_Point* area, void* data) {
    if (cursorInArea(sdlRect, area->x, area->y)) {
        return (SDL_HITTEST_DRAGGABLE);
    }
}

void srcpool_drag(SDL_Window* window, int winW) {
    sdlRect.x = 0;
    sdlRect.y = 0;
    sdlRect.w = winW;
    sdlRect.h = 20;

    SDL_SetWindowHitTest(window, hitCallback, 0);
}

int setGLAttributes() {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    return 0;
}

int setIcon(SDL_Window* window) {
    SDL_Surface* icon = IMG_Load("images\\icon.png");
    if (icon == NULL) {
        std::cout << SDL_GetError() << std::endl;
    }
    else {
        std::cout << "Icon Loaded!" << std::endl;
    }
    SDL_SetWindowIcon(window, icon);
}

// TODO: Add function for font rendering. (http://oglft.sourceforge.net/)