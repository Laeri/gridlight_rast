//
// Created by hexaquat on 08/11/17.
//

#ifndef GRIDLIGHT_RAST_RENDERER_H
#define GRIDLIGHT_RAST_RENDERER_H


#include <SDL_video.h>
#include <sol.hpp>
#include <queue>
#include "../model/Model.h"

class Renderer {
private:
    SDL_Window *window = NULL;
    SDL_Surface *screenSurface = NULL;
    sol::state* lua;
    std::queue<Model*> render_queue = std::queue<Model*>();
public:
    Renderer(sol::state* lua);
    void run();

    void init();


    void draw(Model *model);
    void begin_shader(sol::object *shader);
    void end_shader();
};


#endif //GRIDLIGHT_RAST_RENDERER_H
