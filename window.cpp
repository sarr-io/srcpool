#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

bool XYInRect(const SDL_Rect& rect, int x, int y)
{
    return ((x >= rect.x && x <= rect.x + rect.w) && (y >= rect.y && y <= rect.y + rect.h));
}

SDL_Rect titleBar;

SDL_HitTestResult hitCallback(SDL_Window* win, const SDL_Point* area, void* data) {
    if (XYInRect(titleBar, area->x, area->y)) {
        return (SDL_HITTEST_DRAGGABLE);
    }
}

std::vector<SDL_Event> eventVector;

int main(int argc, char* args[]) {
    bool quit = false;

    int winW = 1300;
    int winH = 700;

    Uint32 flags = SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL;
    SDL_Window* window = SDL_CreateWindow("srcpool", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winW, winH, flags);

    while(!quit) {
        SDL_Event event;

        int mouseX = event.motion.x;
        int mouseY = event.motion.y;

        SDL_Renderer* renderer = NULL;
        renderer =  SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        SDL_SetRenderDrawColor(renderer, 28, 28, 29, 255);
        SDL_RenderClear(renderer);

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

        SDL_SetWindowHitTest(window, hitCallback, 0);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}