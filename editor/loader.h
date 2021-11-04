// OpenGL
#include "glad/glad.h"

// SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// Standard
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

// Shaders
#include <shaders/default.h>

namespace srcpool {

    // Variables
    int winW = 1300;
    int winH = 700;

    int mouseX, mouseY;

    std::vector<std::string> tabList;
    std::string loadedFile;
    int selectedLine;

    int focusMode = 0;
    bool commandMode = false;

    GLuint VBO, VAO, EBO;

    // Functions
    bool cursorInArea(int hitBox[4], int posX, int posY)
    {
        return ((posY >= (winH - hitBox[1]) && posY <= (winH - hitBox[3])) && (posX <= hitBox[0] && posX >= hitBox[2]));
    }

    SDL_HitTestResult hitCallback(SDL_Window* win, const SDL_Point* area, void* data) {
        int testArea[4] = {winW, winH, 0, (winH - 20)};
        if (cursorInArea(testArea, mouseX, mouseY)) {
            return (SDL_HITTEST_DRAGGABLE);
        }

        return (SDL_HITTEST_NORMAL);
    }

    int setGLAttributes() {
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1);
        SDL_SetHint(SDL_HINT_RENDER_OPENGL_SHADERS, "1");

        return 0;
    }

    int setIcon(SDL_Window* window, SDL_Surface* icon) {
        if (icon == NULL) {
            std::cout << SDL_GetError() << std::endl;
        }
        else {
            std::cout << "Icon Loaded!" << std::endl;
        }
        SDL_SetWindowIcon(window, icon);

        return 0;
    }

    // int tabFocus(int i) {
    //     // search through tabList vector for the file path, then load the file.
    // }

    // int loadFile(std::string filePath) {
    //     // do some io stuff and iterate through lines (clear, then add to textbox vector)
    // }

    // std::string getLoadedFile() {
    //     return (loadedFile);
    // }

    // 0 = textbox
    // 1 = menu
    int resetMode = 1;
    int toggleFocusMode() {
        focusMode++;
        if (focusMode > resetMode) {focusMode = 0;}
        return 0;
    }

    // TODO: Add function to convert #hex color codes into proper color format for opengl shader.
    // float convertColor(std::string hexValue, float* r, float* g, float* b) {
    //     // Do some weird math stuff (divide by 255.0f)
    //     return;
    // }

    // TODO: make init for textbox, start back at last open path .txt (if none start blank textbox)

    // TODO: Add function for font rendering. (http://oglft.sourceforge.net/)

    // Component values (all rendered objects that need to save a value)
    namespace components {
        
        // Add component for titlebar

    }

}