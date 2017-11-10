//
// Created by hexaquat on 08/11/17.
//

#include "Model.h"


std::vector<Vector3> &Model::get_positions() {
    return this->positions;
}

std::vector<int> &Model::get_indices() {
    return this->indices;
}

void Model::set_indices(std::vector<int> indices) {
    this->indices = indices;
}

void Model::set_positions(std::vector<Vector3> positions) {
    this->positions = positions;
}

Model::Model() {
    model_matrix = new Matrix4();
    model_matrix->set_identity();
}
