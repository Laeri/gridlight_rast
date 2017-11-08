//
// Created by hexaquat on 08/11/17.
//

#ifndef GRIDLIGHT_RAST_VECTOR3_H
#define GRIDLIGHT_RAST_VECTOR3_H

#include <iostream>

class Vector3 {
public:
    double x, y, z;

    Vector3();

    Vector3(double x, double y, double z);

    Vector3(const Vector3 &vector3);

    double length() const;

    void scale(const double factor);

    void normalize();

    double dot(const Vector3 &vector3) const;

    Vector3 cross(const Vector3 &vector3);

    Vector3 operator+(const Vector3 &vector3);

    Vector3 operator-(const Vector3 &vector3) const;

    Vector3 &operator+=(const Vector3 &vector3);

    Vector3 &operator-=(const Vector3 &vector3);

    Vector3 operator*(const Vector3 &vector3);

    Vector3 operator/(const Vector3 &vector3);

    Vector3 operator*(const double &d);

    Vector3 &operator*=(const double &d);

    Vector3 &operator*=(const Vector3 &vector3);

    Vector3 operator/(double d);

    Vector3 &operator/=(double d);

    Vector3 &operator/=(const Vector3 &vector3);

    bool operator==(const Vector3 &vector3);

    double &operator[](int index);

    double dot(const Vector3 &vec1, const Vector3 &vec2);

    Vector3 max(const Vector3 &vector3) const;

    float max() const;
};

Vector3 operator*(const double &d, const Vector3 &vector3);

std::ostream &operator<<(std::ostream &strm, const Vector3 &vector3);
#endif //GRIDLIGHT_RAST_VECTOR3_H
