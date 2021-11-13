#include <loader.h>
using namespace srcpool;

int close(SDL_Window* window, SDL_GLContext glContext) {
    IMG_Quit();
    
    SDL_DestroyWindow(window);
    SDL_GL_DeleteContext(glContext);
    SDL_Quit();

    return 0;
}

int main(int argc, char* argv[]) {

    // Variables
    bool quit = false;

    // Initializations
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    setGLAttributes();

    // Creating the window
    Uint32 flags = SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL;
    SDL_Window* window = SDL_CreateWindow("srcpool", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winW, winH, flags);
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, glContext);

    SDL_Surface* icon = IMG_Load("images\\icon.png");
    setIcon(window, icon);

    // Setting up OpenGL
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        return -1;
    }
    glViewport(0, 0, winW, winH);

    // Initialize the VAOs
    assignVAO(windowVAO);
    assignVAO(tablistVAO);
    assignVAO(textboxVAO);
    startRenderer();

    while(!quit) {
        SDL_Event event;
        mouseX = event.motion.x;
        mouseY = event.motion.y;
        
        // Input Collection
        while (SDL_PollEvent(&event) != 0) {
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

        SDL_SetWindowHitTest(window, hitCallback, 0);

        glClearColor(0.085f, 0.085f, 0.085f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Draw();

        SDL_GL_SwapWindow(window);
    }

    // Closes all processes
    close(window, glContext);

    return 0;
}