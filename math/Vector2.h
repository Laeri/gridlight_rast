//
// Created by hexaquat on 08/11/17.
//

#ifndef GRIDLIGHT_RAST_VECTOR2_H
#define GRIDLIGHT_RAST_VECTOR2_H


class Vector2 {
public:
    float x;
    float y;

    Vector2();

    Vector2(float x, float y);

    Vector2(const Vector2 &vec2);

    Vector2 &operator+=(Vector2 &vec2);

    Vector2 operator+(Vector2 &vec2);

    Vector2 &operator-=(Vector2 &vec2);

    Vector2 operator-(Vector2 &vec2);

    Vector2 operator*(float t);

    Vector2 &operator*=(float t);

    Vector2 operator/(float t);

    Vector2 &operator/=(float t);

    void operator=(Vector2 &vec2);

    void operator=(Vector2 vec2);

    bool operator==(Vector2 &vec2);

    void scale(float t);

    void add_scaled(Vector2 &vec2, float scale);
};


#endif //GRIDLIGHT_RAST_VECTOR2_H
