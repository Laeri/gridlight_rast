//
// Created by hexaquat on 08/11/17.
//

#include "Vector3.h"
#include "math.h"
#include <stdexcept>


Vector3::Vector3() : x(0), y(0), z(0) {}

Vector3::Vector3(double x, double y, double z) : x(x), y(y), z(z) {}

Vector3::Vector3(const Vector3 &vector3) : x(vector3.x), y(vector3.y), z(vector3.z) {
}

double Vector3::length() const {
    return sqrt(x * x + y * y + z * z);
}

void Vector3::scale(const double factor) {
    x *= factor;
    y *= factor;
    z *= factor;
}

void Vector3::normalize() {
    float len = length();
    if (len == 0) throw std::runtime_error("Tried to normalize zero vector!");
    scale(1.0 / len);
}

double Vector3::dot(const Vector3 &vector3) const {
    return x * vector3.x + y * vector3.y + z * vector3.z;
}

Vector3 Vector3::cross(const Vector3 &vector3) {
    double tmp_x = y * vector3.z - z * vector3.y;
    double tmp_y = z * vector3.x - x * vector3.z;
    double tmp_z = x * vector3.y - y * vector3.x;
    return Vector3(tmp_x, tmp_y, tmp_z);
}

Vector3 Vector3::operator+(const Vector3 &vector3) {
    return Vector3(x + vector3.x, y + vector3.y, z + vector3.z);
}

Vector3 &Vector3::operator+=(const Vector3 &vector3) {
    x += vector3.x;
    y += vector3.y;
    z += vector3.z;
    return *this;
}

Vector3 Vector3::operator-(const Vector3 &vector3) const {
    return Vector3(x - vector3.x, y - vector3.y, z - vector3.z);
}

Vector3 &Vector3::operator-=(const Vector3 &vector3) {
    x -= vector3.x;
    y -= vector3.y;
    z -= vector3.z;
    return *this;
}

Vector3 Vector3::operator*(const Vector3 &vector3) {
    return Vector3(x * vector3.x, y * vector3.y, z * vector3.z);
}

Vector3 Vector3::operator*(const double &d) {
    return Vector3(x * d, y * d, z * d);
}

Vector3 &Vector3::operator*=(const double &d) {
    x *= d;
    y *= d;
    z *= d;
    return *this;
}

Vector3 Vector3::operator/(double d) {
    return Vector3(x / d, y / d, z / d);
}

Vector3 &Vector3::operator/=(double d) {
    x /= d;
    y /= d;
    z /= d;
    return *this;
}

Vector3 &Vector3::operator*=(const Vector3 &vector3) {
    x *= vector3.x;
    y *= vector3.y;
    z *= vector3.z;
    return *this;
}

Vector3 Vector3::operator/(const Vector3 &vector3) {
    return Vector3(x / vector3.x, y / vector3.y, z / vector3.z);
}

Vector3 &Vector3::operator/=(const Vector3 &vector3) {
    x /= vector3.x;
    y /= vector3.y;
    z /= vector3.z;
    return *this;
}

bool Vector3::operator==(const Vector3 &vector3) {
    return (x == vector3.x) && (y == vector3.y) && (z == vector3.z);
}

double &Vector3::operator[](int index) {
    if (index == 0) return x;
    if (index == 1) return y;
    return z;
}

std::ostream &operator<<(std::ostream &strm, const Vector3 &vector3) {
    return strm << "Vector3(" << vector3.x << "," << vector3.y << "," << vector3.z << ")";
}

double dot(const Vector3 &vec1, const Vector3 &vec2) {
    return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

Vector3 operator*(const double &d, const Vector3 &vector3) {
    return Vector3(vector3.x * d, vector3.y * d, vector3.z * d);
}


Vector3 Vector3::max(const Vector3 &vector3) const {
    double m_x = (x > vector3.x) ? x : vector3.x;
    double m_y = (y > vector3.y) ? y : vector3.y;
    double m_z = (z > vector3.z) ? z : vector3.z;
    return Vector3(m_x, m_y, m_z);
}

float Vector3::max() const {
    return std::max(x, std::max(y, z));
}