//
// Created by hexaquat on 08/11/17.
//

#include <SDL_quit.h>
#include <SDL_timer.h>
#include <SDL_surface.h>
#include <SDL.h>
#include <iostream>
#include "Renderer.h"
#include "../math/Matrix4.h"
#include "../math/Matrix3.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;
Matrix4 viewport_matrix;

std::vector<double> zbuffer = std::vector<double>((SCREEN_WIDTH - 1) * (SCREEN_HEIGHT - 1),
                                                  -1 * std::numeric_limits<double>::max());

void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel) {
    Uint32 *target_pixel = (Uint32 *) ((Uint8 *) surface->pixels + y * surface->pitch +
                                       x * sizeof *target_pixel);
    *target_pixel = pixel;
}

int clamp(int min, int max, int value) {
    if (value < min) return min;
    else if (value > max) return max;
    return value;
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

    viewport_matrix = Matrix4();
    viewport_matrix.set_identity();
    int x0 = 0;
    int x1 = SCREEN_WIDTH - 1;
    int y0 = 0;
    int y1 = SCREEN_HEIGHT - 1;
    std::vector<double> values = {
            (x1 - x0) / 2.0, 0, 0, (x0 + x1) / 2.0,
            0, (y1 - y0) / 2.0, 0, (y0 + y1) / 2.0,
            0, 0, 0.5, 0.5,
            0, 0, 0, 1
    };
    viewport_matrix.set(values);

    camera = new Camera();
    frustum = new Frustum();


}

void Renderer::run() {
    screenSurface = SDL_GetWindowSurface(window);
    bool quit = false;

    Uint32 current = SDL_GetTicks();
    Uint32 last = 0;
    float delta = 0;
    float timer = 0;


    Matrix3 edge_matrix = Matrix3();
    bool draw_backface = true;

    while (!quit) {
        zbuffer.assign(zbuffer.size(), -1 * std::numeric_limits<double>::max());
        SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));
        last = current;
        current = SDL_GetTicks();
        delta = ((float) (current - last) / 1000);
        timer += delta;
        // clear old uniforms/render state
        (*lua)["renderer"]["clear"](*this);
        // update current state
        (*lua)["state"]["render"]((*lua)["state"], *this, delta);
        // draw collected items
        while (!render_queue.empty()) {
            Model &model = *render_queue.front();
            render_queue.pop();
            auto &positions = model.get_positions();
            auto &indices = model.get_indices();
            for (int i = 0; i < indices.size(); i += 3) {
                auto &vec1 = positions[indices[i]];
                auto &vec2 = positions[indices[i + 1]];
                auto &vec3 = positions[indices[i + 3]];
                (*lua)["vertex_shader"]["projection"] = 3;
                (*lua)["vertex_shader"]["model_view"] = 3;
                (*lua)["vertex_shader"]["position"] = Vector4(vec1.x, vec1.y, vec1.z, 1);
                (*lua)["vertex_shader"]["main"]((*lua)["vertex_shader"]);

                Vector4 pos1 = (*lua)["vertex_shader"]["gl_position"];

                (*lua)["vertex_shader"]["position"] = Vector4(vec2.x, vec2.y, vec2.z, 1);
                (*lua)["vertex_shader"]["main"]((*lua)["vertex_shader"]);
                Vector4 pos2 = (*lua)["vertex_shader"]["gl_position"];

                (*lua)["vertex_shader"]["position"] = Vector4(vec3.x, vec3.y, vec3.z, 1);
                (*lua)["vertex_shader"]["main"]((*lua)["vertex_shader"]);
                Vector4 pos3 = (*lua)["vertex_shader"]["gl_position"];

                edge_matrix.set_row(0, pos1.x, pos1.y, pos1.w);
                edge_matrix.set_row(1, pos2.x, pos2.y, pos2.w);
                edge_matrix.set_row(2, pos3.x, pos3.y, pos3.w);

                std::cout << pos1 << pos2 << pos3 << std::endl;

                std::cout << "det" << edge_matrix.det() << std::endl;
                float det = edge_matrix.det();
                if (det == 0) { // triangle has no area either before or after the projection
                    continue;
                } else if (det < 0 && !draw_backface) {
                    continue;
                }
                edge_matrix.invert();

                edge_matrix.transpose();
                std::cout << edge_matrix << std::endl;

                // do homogenous division
                pos1.x /= pos1.w;
                pos1.y /= pos1.w;
                pos2.x /= pos2.w;
                pos2.y /= pos2.w;
                pos3.x /= pos3.w;
                pos3.y /= pos3.w;

                int min_x, min_y, max_x, max_y;

                min_x = (int) std::min(std::min(pos1.x, pos2.x), pos3.x);
                min_y = (int) std::min(std::min(pos1.y, pos2.y), pos3.y);
                max_x = (int) std::ceil(std::max(std::max(pos1.x, pos2.x), pos3.x));
                max_y = (int) std::ceil(std::max(std::max(pos1.y, pos2.y), pos3.y));

                min_x = clamp(0, SCREEN_WIDTH - 1, min_x);
                min_y = clamp(0, SCREEN_HEIGHT - 1, min_y);
                max_x = clamp(0, SCREEN_WIDTH - 1, max_x);
                max_y = clamp(0, SCREEN_HEIGHT - 1, max_y);

                Vector3 pixel_pos = Vector3();
                for (int y = min_y; y <= max_y; y++) {
                    for (int x = min_x; x <= max_x; x++) {
                        pixel_pos.x = x;
                        pixel_pos.y = y;
                        pixel_pos.z = 1; // on screen homogenous coordinate w = 1
                        edge_matrix.transform(pixel_pos); // after transformation alpha, beta, gamma weights in vector
                        if (pixel_pos.x > 0 && pixel_pos.y > 0 &&
                            pixel_pos.z > 0) { // pixel position is inside triangle
                        }
                    }
                }
            }
        }

        SDL_UpdateWindowSurface(window);
    }
    SDL_DestroyWindow(window);

    SDL_Quit();
}

void Renderer::draw(Model *model) {
    render_queue.push(model);
}

void Renderer::set_camera(Camera *camera) {
    this->camera = camera;
}

Camera &Renderer::get_camera() {
    return *camera;
}

void Renderer::set_frustum(Frustum *frustum) {
    this->frustum = frustum;
}

Frustum &Renderer::get_frustum() {
    return *frustum;
}
