//
// Created by hexaquat on 08/11/17.
//

#ifndef GRIDLIGHT_RAST_MODEL_H
#define GRIDLIGHT_RAST_MODEL_H

#include <vector>
#include "../math/Vector3.h"
#include "../math/Matrix4.h"
#include "Vertex.h"

class Model {
public:
    Model();
    Matrix4 *model_matrix;
    std::vector<Vertex> vertices;
    std::vector<int> indices;

    std::vector<Vertex> &get_vertices();

    std::vector<int> &get_indices();

    void set_vertices(std::vector<Vertex> vertices);

    void set_indices(std::vector<int> indices);
};


#endif //GRIDLIGHT_RAST_MODEL_H
