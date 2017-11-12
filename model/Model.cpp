//
// Created by hexaquat on 08/11/17.
//

#include "Model.h"


std::vector<Vertex*> &Model::get_vertices() {
    return this->vertices;
}

std::vector<int> &Model::get_indices() {
    return this->indices;
}

void Model::set_indices(std::vector<int> indices) {
    this->indices = indices;
}

void Model::set_vertices(std::vector<Vertex*> vertices) {
    this->vertices = vertices;
}

Model::Model() {
    model_matrix = new Matrix4();
    model_matrix->set_identity();
}
