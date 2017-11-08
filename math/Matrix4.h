//
// Created by hexaquat on 08/11/17.
//

#ifndef GRIDLIGHT_RAST_MATRIX4_H
#define GRIDLIGHT_RAST_MATRIX4_H

#include <vector>
#include "Vector4.h"

class Matrix4 {

private:
    std::vector<Vector4> rows;

public:
    static const int DIM = 4;
    int M11 = 0;
    int M12 = 1;
    int M13 = 2;
    int M14 = 3;
    int M21 = 4;
    int M22 = 5;
    int M23 = 6;
    int M24 = 7;
    int M31 = 8;
    int M32 = 9;
    int M33 = 10;
    int M34 = 11;
    int M41 = 12;
    int M42 = 13;
    int M43 = 14;
    int M44 = 15;

    Matrix4();

    Matrix4(std::vector<double> values);

    Matrix4 operator+(Matrix4 &matrix4);

    Matrix4 &operator+=(Matrix4 &matrix4);

    Matrix4 operator-(Matrix4 &matrix4);

    Matrix4 &operator-=(Matrix4 &matrix4);

    Matrix4 operator*(Matrix4 &matrix4);

    Matrix4 &operator*=(Matrix4 &matrix4);

    Matrix4 operator*(double d);

    Vector4 &operator[](int index);

    Vector4 operator*(const Vector4 &vector4);

    bool operator==(Matrix4 &matrix4);

    void set_translation(Vector3 &translation);

    void get_translation(Vector3 &vector3);

    Vector3 get_translation();

    void rot_x(double theta);

    void rot_y(double theta);

    void rot_z(double theta);

    void rot(Vector3 &axis, double theta);

    void set_scale(double scale_x, double scale_y, double scale_z);

    void translate(Vector3 &vector3);

    void invert();

    Matrix4 get_inverted();

    void swap_row(int r1, int r2);

    void set_identity();

    double det();

    void transform(Vector4 &vector4);

    void transform(Vector3 &vector3);

    void set_row(int row, Vector4 &vector4);

    void set_row(int row, double x, double y, double z, double w);

    std::vector<double> get_values();

    Vector4 get_row(int row) const;

    void set_column(int column, Vector4 &vector4);

    Vector4 get_column(int column);

    void set(int index, double value);

    void set(std::vector<double> values);

    double get(int index);

    void set(Matrix4 &matrix4);


    void transpose();
};

std::ostream &operator<<(std::ostream &strm, Matrix4 &matrix4);


#endif //GRIDLIGHT_RAST_MATRIX4_H
