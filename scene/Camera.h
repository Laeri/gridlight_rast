//
// Created by hexaquat on 10/11/17.
//

#ifndef GRIDLIGHT_RAST_CAMERA_H
#define GRIDLIGHT_RAST_CAMERA_H


#include "../math/Matrix4.h"

class Camera {
private:
    Vector4 position;
    Vector3 u, v, w;
    Matrix4 camera_matrix;
public:
    Camera();
    Camera(Vector4 position, Vector3 up, Vector3 look_at);
    void update();
    Matrix4 &get_world_to_camera();
};


#endif //GRIDLIGHT_RAST_CAMERA_H
