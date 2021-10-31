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
int winW = 1300;
int winH = 700;
int mouseX;
int mouseY;
// add array of lines of text (from open file) index acts as line #, value acts as the line's string

// Functions
bool srcpool_cursorInArea(int coordPlane[4], int posX, int posY, int windowH)
{
    return ((posY >= (windowH - coordPlane[1]) && posY <= (windowH - coordPlane[3])) && (posX <= coordPlane[0] && posX >= coordPlane[2]));
}

SDL_HitTestResult hitCallback(SDL_Window* win, const SDL_Point* area, void* data) {
    int testArea[4] = {winW, winH, 0, (winH - 20)};
    if (srcpool_cursorInArea(testArea, mouseX, mouseY, 700)) {
        return (SDL_HITTEST_DRAGGABLE);
    }
}

int srcpool_updateCursor(int mouseX, int mouseY) {
    mouseX = mouseX;
    mouseY = mouseY;
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

int srcpool_setIcon(SDL_Window* window) {
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