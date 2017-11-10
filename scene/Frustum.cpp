//
// Created by hexaquat on 10/11/17.
//

#include <cmath>
#include "Frustum.h"


Frustum::Frustum() : near(1), far(100), fov(90), aspect_ratio(1) {
    update();
}

Frustum::Frustum(double near, double far, double fov, double aspect_ratio) : near(near), far(far), fov(fov),
                                                                             aspect_ratio(aspect_ratio) {
    update();
}

void Frustum::update() {
    double fov_rad = (fov / 180.0) * M_PI;

    std::vector<double> values = {1.0 / (aspect_ratio * tan(fov_rad / 2.0)), 0, 0, 0,
                                  0, (1.0 / (tan(fov_rad / 2.0))), 0, 0,
                                  0, 0, (near + far) / (near - far),
                                  (2.0 * near * far) / (near - far),
                                  0, 0, -1, 0};
    projection_matrix.set(values);
}

Matrix4 &Frustum::get_projection() {
    return projection_matrix;
}