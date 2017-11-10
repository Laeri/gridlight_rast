//
// Created by hexaquat on 10/11/17.
//

#include "Camera.h"


Camera::Camera() {
    position = Vector4(0, 0, 10, 1);
    u = Vector3(1, 0, 0);
    v = Vector3(0, 1, 0);
    w = Vector3(0, 0, 1);
    update();
}

Camera::Camera(Vector4 position, Vector3 up, Vector3 look_at) {
    this->position = position;

    w = look_at;
    w.scale(-1);
    w.normalize();
    u = up.cross(w);
    u.normalize();
    v = w.cross(u);
    update();
}

void Camera::update() {
    Vector4 tmp = Vector4(u, 0);
    camera_matrix.set_column(0, tmp);
    tmp = Vector4(v, 0);
    camera_matrix.set_column(1, tmp);
    tmp = Vector4(w, 0);
    camera_matrix.set_column(2, tmp);
    camera_matrix.set_column(3, position);
    camera_matrix.invert();
}

Matrix4 &Camera::get_world_to_camera() {
    return camera_matrix;
}

Camera::Camera(Vector3 position, Vector3 up, Vector3 look_at) {
    this->position.x = position.x;
    this->position.y = position.y;
    this->position.z = position.z;
    this->position.w = 1;

    w = look_at;
    w.scale(-1);
    w.normalize();
    u = up.cross(w);
    u.normalize();
    v = w.cross(u);
    update();
}
