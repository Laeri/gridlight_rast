//
// Created by hexaquat on 10/11/17.
//

#ifndef GRIDLIGHT_RAST_FRUSTUM_H
#define GRIDLIGHT_RAST_FRUSTUM_H


#include "../math/Matrix4.h"

class Frustum {
private:
    Matrix4 projection_matrix;
public:
    double near, far, fov, aspect_ratio;

    Frustum();

    Frustum(double near, double far, double fov, double aspect_ratio);

    void update();

    Matrix4 &get_projection();
};

#endif //GRIDLIGHT_RAST_FRUSTUM_H
