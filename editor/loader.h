// OpenGL
#include <glad/glad.h>

// SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// Standard
#include <stdio.h>
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <fstream>
#include <cstring>
#include <sstream>

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

    int setGLAttributes() {
        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1);

        // Request a debug context.
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

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
    // float convertColor(std::string hexValue, float r, float g, float b) {
    //     // Do some weird math stuff (divide by 255.0f)
    //     return;
    // }

    // TODO: make init for textbox, start back at last open path .txt (if none start blank textbox)

    // TODO: Add function for font rendering. (http://oglft.sourceforge.net/)

    // Window Checks
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

    class Renderer {

        public:

            void attachObject(); // Adds an object type to the list of updated objects on screen at a given moment.
            void detachObject(); // Removes an object type from the list of updated objects on screen at a given moment.

            typedef struct Objects {
                std::vector<GLfloat> vertices;
                std::vector<int> indices;
                
                std::vector<GLfloat> colors;
                std::vector<int> shaderProgramID;
                std::vector<std::string> name;
            } Objects;

            class Queue {
            
                void listObjects(); // List all objects in the queue.
                void findObject(); // Returns true or false if the object is found.
            
            };

    };

}