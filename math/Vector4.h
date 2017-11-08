//
// Created by hexaquat on 08/11/17.
//

#ifndef GRIDLIGHT_RAST_VECTOR4_H
#define GRIDLIGHT_RAST_VECTOR4_H

#include "Vector3.h"

class Vector4 {
public:
    double x, y, z, w;

    Vector4();

    Vector4(double x, double y, double z, double w);

    Vector4(const Vector4 &vector4);

    Vector4(const Vector3 &vector3);

    Vector4(const Vector3 &vector3, double w);

    Vector4 operator+(const Vector4 &vector4);

    Vector4 &operator+=(const Vector4 &vector4);

    Vector4 operator-(const Vector4 &vector4);

    Vector4 &operator-=(const Vector4 &vector4);

    Vector4 operator*(const Vector4 &vector4);

    Vector4 &operator*=(const Vector4 &vector4);

    Vector4 operator/(const Vector4 &vector4);

    Vector4 &operator/=(const Vector4 &vector4);

    Vector4 operator*(const double d);

    Vector4 &operator*=(const double d);

    double &operator[](int index) {
        if (index == 0) return x;
        if (index == 1) return y;
        if (index == 2) return z;
        if (index == 3) return w;
    }

    void set(const Vector4 &vector4);

    double dot(const Vector4 &vector4);

    double length();

    void scale(double d);

    void normalize();

    Vector3 xyz();

    bool isPoint();

    bool isVector();

};

Vector4 operator*(const double &d, const Vector4 &vector4);

std::ostream &operator<<(std::ostream &strm, const Vector4 &vector4);



#endif //GRIDLIGHT_RAST_VECTOR4_H
