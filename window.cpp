#include <loader.h>

int close(SDL_Window* window, SDL_GLContext glContext) {
    SDL_DestroyWindow(window);
    SDL_GL_DeleteContext(glContext);
    IMG_Quit();
    SDL_Quit();
}

int renderWindowBase(int winW, int winH) {

    // Window
    glBegin(GL_QUADS);
    glColor3f(0.085f, 0.085f, 0.085f);
    glVertex3i(winW, winH, 0);
    glVertex3i(0, winH, 0);
    glVertex3i(0, 0, 0);
    glVertex3i(winW, 0, 0);
    glEnd();

    // Titlebar
    glBegin(GL_QUADS);
    glColor3f(0.08f, 0.08f, 0.08f);
    glVertex3i(winW, winH, 1);
    glVertex3i(0, winH, 1);
    glVertex3i(0, winH - 20, 1);
    glVertex3i(winW, winH - 20, 1);
    glEnd();

}

int main(int argc, char* argv[]) {
    bool quit = false;

    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    setGLAttributes();

    Uint32 flags = SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL;
    SDL_Window* window = SDL_CreateWindow("srcpool", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winW, winH, flags);
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    gladLoadGLLoader(SDL_GL_GetProcAddress);
    glOrtho(0, winW, 0, winH, -1, 1);
    glEnable(GL_BLEND);

    SDL_Surface* icon = IMG_Load("images\\icon.png");
    srcpool_setIcon(window, icon);

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
                            srcpool_toggleFocusMode();
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
                            commandMode = false;
                            break;
                    }
                }
            }
        }

        srcpool_updateCursor(mouseX, mouseY);
        SDL_SetWindowHitTest(window, hitCallback, 0);

        glClearColor(0.f, 0.f, 0.f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderWindowBase(winW, winH);

        SDL_GL_SwapWindow(window);
    }

    // Closes all processes
    close(window, glContext);

    return 0;
}