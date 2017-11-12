//
// Created by hexaquat on 11/11/17.
//

#ifndef GRIDLIGHT_RAST_VERTEX_H
#define GRIDLIGHT_RAST_VERTEX_H


#include <sol.hpp>
#include <map>
#include "../math/Vector3.h"

class Vertex {
public:
    Vertex(Vector3 position);
    std::map<std::string, sol::object> members = std::map<std::string, sol::object>();
    Vertex(float x, float y, float z);
    Vertex();
    Vector3 position;
};


#endif //GRIDLIGHT_RAST_VERTEX_H
