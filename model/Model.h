//
// Created by hexaquat on 08/11/17.
//

#ifndef GRIDLIGHT_RAST_MODEL_H
#define GRIDLIGHT_RAST_MODEL_H

#include <vector>
#include "../math/Vector3.h"

class Model {
public:

    std::vector<Vector3> positions;
    std::vector<int> indices;

    std::vector<Vector3> &get_positions();

    std::vector<int> &get_indices();

    void set_positions(std::vector<Vector3> positions);

    void set_indices(std::vector<int> indices);
};


#endif //GRIDLIGHT_RAST_MODEL_H
