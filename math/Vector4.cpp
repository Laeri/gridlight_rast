//
// Created by hexaquat on 08/11/17.
//


#include "Vector4.h"
#include "math.h"

Vector4::Vector4() : x(0), y(0), z(0), w(0) {}

Vector4::Vector4(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) {}

Vector4::Vector4(const Vector4 &vector4) : x(vector4.x), y(vector4.y), z(vector4.z), w(vector4.w) {}

Vector4::Vector4(const Vector3 &vector3) : x(vector3.x), y(vector3.y), z(vector3.z), w(0) {}

Vector4::Vector4(const Vector3 &vector3, double w) : x(vector3.x), y(vector3.y), z(vector3.z), w(w) {}

Vector4 Vector4::operator+(const Vector4 &vector4) {
    return Vector4(x + vector4.x, y + vector4.y, z + vector4.z, w + vector4.w);
}

Vector4 &Vector4::operator+=(const Vector4 &vector4) {
    x += vector4.x;
    y += vector4.y;
    z += vector4.z;
    w += vector4.w;
    return *this;
}

Vector4 Vector4::operator-(const Vector4 &vector4) {
    return Vector4(x - vector4.x, y - vector4.y, z - vector4.z, w - vector4.w);
}

Vector4 &Vector4::operator-=(const Vector4 &vector4) {
    x -= vector4.x;
    y -= vector4.y;
    z -= vector4.z;
    w -= vector4.w;
    return *this;
}

Vector4 Vector4::operator*(const double d) {
    return Vector4(x * d, y * d, z * d, w * d);
}

Vector4 Vector4::operator*(const Vector4 &vector4) {
    return Vector4(x * vector4.x, y * vector4.y, z * vector4.z, w * vector4.w);
}

Vector4 &Vector4::operator*=(const double d) {
    x *= d;
    y *= d;
    z *= d;
    w *= d;
    return *this;
}

double Vector4::dot(const Vector4 &vector4) {
    return x * vector4.x + y * vector4.y + z * vector4.z + w * vector4.w;
}


double Vector4::length() {
    return sqrt(dot((*this)));
}

void Vector4::normalize() {
    double length = this->length();
    scale(1.0 / length);
}

void Vector4::scale(double d) {
    x *= d;
    y *= d;
    z *= d;
    w *= d;
}

void Vector4::set(const Vector4 &vector4) {
    x = vector4.x;
    y = vector4.y;
    z = vector4.z;
    w = vector4.w;
}

Vector3 Vector4::xyz() {
    return Vector3(x, y, z);
}

bool Vector4::isPoint() {
    return w == 1;
}

bool Vector4::isVector() {
    return w == 0;
}

std::ostream &operator<<(std::ostream &strm, const Vector4 &vector4) {
    return strm << "Vector4(" << vector4.x << "," << vector4.y << "," << vector4.z << "," << vector4.w << ")";
}

Vector4 operator*(const double &d, const Vector4 &vector4) {
    return Vector4(d * vector4.x, d * vector4.y, d * vector4.z, d * vector4.w);
}