#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char* args[]) {
    int winW = 1200;
    int winH = 600;
    Uint32 flags = SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL;
    SDL_Window* window = SDL_CreateWindow("srcpool", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, winW, winH, flags);

    SDL_Init(SDL_INIT_EVERYTHING);

    while(true) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if( event.type == SDL_QUIT )
                SDL_DestroyWindow(window);
                SDL_Quit();
        }

        SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
        SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

        SDL_UpdateWindowSurface(window);
    }