//
// Created by hexaquat on 08/11/17.
//

#ifndef GRIDLIGHT_RAST_RENDERER_H
#define GRIDLIGHT_RAST_RENDERER_H


#include <SDL_video.h>
#include <sol.hpp>

class Renderer {
private:
    SDL_Window *window = NULL;
    SDL_Surface *screenSurface = NULL;
    sol::state* lua;
public:
    Renderer(sol::state* lua);
    void run();

    void init();
};


#endif //GRIDLIGHT_RAST_RENDERER_H
