//
// Created by hexaquat on 08/11/17.
//

#include "Vector2.h"



Vector2::Vector2() : x(0), y(0) {}

Vector2::Vector2(float x, float y) : x(x), y(y) {}

Vector2::Vector2(const Vector2 &vec2) {
    x = vec2.x;
    y = vec2.y;
}

Vector2 Vector2::operator*(float t) {
    return Vector2(x * t, y * t);
}

Vector2 &Vector2::operator*=(float t) {
    x *= t;
    y *= t;
    return *this;
}

Vector2 Vector2::operator/(float t) {
    return Vector2(x / t, y / t);
}

Vector2 &Vector2::operator/=(float t) {
    x /= t;
    y /= t;
}

Vector2 Vector2::operator+(Vector2 &vec2) {
    return Vector2(x + vec2.x, y + vec2.y);
}

Vector2 Vector2::operator-(Vector2 &vec2) {
    return Vector2(x - vec2.x, y - vec2.y);
}

Vector2 &Vector2::operator+=(Vector2 &vec2) {
    x += vec2.x;
    y += vec2.y;
    return *this;
}

Vector2 &Vector2::operator-=(Vector2 &vec2) {
    x -= vec2.x;
    y -= vec2.y;
    return *this;
}

void Vector2::operator=(Vector2 &vec2) {
    x = vec2.x;
    y = vec2.y;
}

void Vector2::operator=(Vector2 vec2) {
    x = vec2.x;
    y = vec2.y;
}

bool Vector2::operator==(Vector2 &vec2) {
    return (x == vec2.x) && (y == vec2.y);
}

void Vector2::add_scaled(Vector2 &vec2, float scale) {
    x += vec2.x * scale;
    y += vec2.y * scale;
}

void Vector2::scale(float t) {
    x *= t;
    y *= t;
}
