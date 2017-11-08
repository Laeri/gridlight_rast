//
// Created by hexaquat on 08/11/17.
//

#include <SDL_quit.h>
#include <SDL_timer.h>
#include <SDL_surface.h>
#include <SDL.h>
#include <iostream>
#include "Renderer.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;

void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel) {
    Uint32 *target_pixel = (Uint32 *) ((Uint8 *) surface->pixels + y * surface->pitch +
                                       x * sizeof *target_pixel);
    *target_pixel = pixel;
}


Renderer::Renderer(sol::state *lua) {
    this->lua = lua;
}

void Renderer::init() {
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    } else {
        //Create window
        window = SDL_CreateWindow("Gridlight", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
    }

}

void Renderer::run() {
    screenSurface = SDL_GetWindowSurface(window);
    bool quit = false;

    Uint32 current = SDL_GetTicks();
    Uint32 last = 0;
    float delta = 0;
    float timer = 0;
    while (!quit) {
        SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));
        last = current;
        current = SDL_GetTicks();
        delta = ((float) (current - last) / 1000);
        timer += delta;
        std::cout << std::to_string(timer) << std::endl;
        SDL_UpdateWindowSurface(window);
    }
    SDL_DestroyWindow(window);

    SDL_Quit();
}