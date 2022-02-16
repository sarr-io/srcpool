// OpenGL
#include <glad/glad.h>

// SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// Renderer
#include <renderer.h>

namespace srcpool {

    /*
        VARIABLES
    ================================================
    */
    Uint32 flags = SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL;

    int winW = 1300;
    int winH = 700;

    int mouseX, mouseY;

    int focusMode = 0;
    bool commandMode = false;
    std::vector<std::string> tabList;

    int defaultFontSize = 24; // In the future, this value will come from settings.json.



    /*
        CORE CLASSES
    ================================================
    */

    class Tab;

    class Textbox;

    class Menu;

    class Extensions;



    /*
        FUNCTIONS
    ================================================
    */

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

    // 0 = textbox
    // 1 = menu
    int resetMode = 1;
    int toggleFocusMode() {
        focusMode++;
        if (focusMode > resetMode) {focusMode = 0;}
        return 0;
    }

    // TODO: make init for textbox, start back at last open path .txt (if none start blank textbox)

    /* 
    Setup temporary font rendering with libdrawtext (https://github.com/jtsiomb/libdrawtext/blob/master/examples/simple/simple.c) 
    Will most likely replace with  my own solution, just testing different libraries
    */

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

    void inputCollection(SDL_Event event, bool &quit) {
        if (event.type == SDL_QUIT) {
            std::cout << "Closing..." << std::endl;
            quit = true;
        }
        // TODO: Add event to check line number.
        // TODO: Check if clicking on tab button.
        if (event.type == SDL_KEYDOWN) {
            // All keybinds
            if (event.key.keysym.sym == SDLK_LSHIFT) {
                commandMode = !commandMode;
            }
            if (commandMode) {
                switch (event.key.keysym.sym) {
                    case SDLK_m:
                        toggleFocusMode();
                        std::cout << "Focus Toggled!" << std::endl;
                        commandMode = false;
                        break;
                    case SDLK_e:
                        std::cout << "Compiled!" << std::endl;
                        commandMode = false;
                        break;
                }
            }
            else {
                switch (event.key.keysym.sym) {
                    case SDLK_F5:
                        std::cout << "Compiled!" << std::endl;
                        break;
                }
            }
        }
    }

    void convertHexToGL(int color, float &r, float &g, float &b) {
        r = (color / 256 / 256) % 256;
        g = (color / 256) % 256;
        b = (color) % 256;
        r /= 255.0f;
        g /= 255.0f;
        b /= 255.0f;
    }

}