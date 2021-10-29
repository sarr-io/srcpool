#include <loader.h>

int main(int argc, char* argv[]) {
    bool quit = false;

    int winW = 1300;
    int winH = 700;

    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    setGLAttributes();

    Uint32 flags = SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL;
    SDL_Window* window = SDL_CreateWindow("srcpool", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winW, winH, flags);
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    gladLoadGLLoader(SDL_GL_GetProcAddress);

    setIcon(window);

    while(!quit) {
        SDL_Event event;
        int mouseX = event.motion.x;
        int mouseY = event.motion.y;
        
        // Input Collection
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                std::cout << "Closing..." << std::endl;
                quit = true;
            }
            // TODO: Add event for clicking on resize frame, then set the window size to new size when dragging.
        }
        
        srcpool_drag(window, winW);

        glClearColor(0.f, 0.f, 0.f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT);

        // do stuff
        
        SDL_GL_SwapWindow(window);
    }

    SDL_DestroyWindow(window);
    SDL_GL_DeleteContext(glContext);
    IMG_Quit();
    SDL_Quit();

    return 0;
}