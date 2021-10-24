#include <loader.h>

int renderScreen() {
    // Add GL rendering stuff here.
}

int initGL() {
    // Add GL stuff here.
}

int main(int argc, char* args[]) {
    bool quit = false;

    int winW = 1300;
    int winH = 700;

    setGLAttributes();
    IMG_Init(IMG_INIT_PNG);

    Uint32 flags = SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL;
    SDL_Window* window = SDL_CreateWindow("srcpool", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winW, winH, flags);

    //initGL();

    setIcon(window);

    while(!quit) {
        SDL_Event event;
        int mouseX = event.motion.x;
        int mouseY = event.motion.y;

        SDL_Renderer* renderer = NULL;
        renderer =  SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        SDL_SetRenderDrawColor(renderer, 28, 28, 29, 255);
        SDL_RenderClear(renderer);

        SDL_Rect titleBar;
        titleBar.x = 0;
        titleBar.y = 0;
        titleBar.w = winW;
        titleBar.h = 20;

        SDL_SetRenderDrawColor(renderer, 26, 26, 27, 255);
        SDL_RenderFillRect(renderer, &titleBar);
        SDL_RenderPresent(renderer);
        
        // Input Collection
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            // TODO: Add event for clicking on resize frame, then set the window size to new size when dragging.
        }

        srcpool_drag(titleBar, window);

        //renderScreen();
    }

    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}