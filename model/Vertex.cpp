//
// Created by hexaquat on 11/11/17.
//

#include "Vertex.h"

Vertex::Vertex(Vector3 position) {
    this->position.x = position.x;
    this->position.y = position.y;
    this->position.z = position.z;
}

Vertex::Vertex(float x, float y, float z) {
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;
}

Vertex::Vertex() {
    this->position.x = 0;
    this->position.y = 0;
    this->position.z = 0;
}
