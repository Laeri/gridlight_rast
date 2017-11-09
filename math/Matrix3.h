//
// Created by hexaquat on 08/11/17.
//

#ifndef GRIDLIGHT_RAST_MATRIX3_H
#define GRIDLIGHT_RAST_MATRIX3_H

#include <vector>
#include "Vector3.h"

class Matrix3 {
private:
    std::vector<Vector3> rows;
public:
    static const int DIM = 3;
    int M11 = 0;
    int M12 = 1;
    int M13 = 2;
    int M21 = 3;
    int M22 = 4;
    int M23 = 5;
    int M31 = 6;
    int M32 = 7;
    int M33 = 8;


    Matrix3();

    Matrix3(std::vector<double> values);

    Matrix3 operator+(Matrix3 &matrix);

    Matrix3 &operator+=(Matrix3 &matrix);

    Matrix3 operator-(Matrix3 &matrix);

    Matrix3 &operator-=(Matrix3 &matrix);

    Matrix3 operator*(Matrix3 &matrix);

    Matrix3 &operator*=(Matrix3 &matrix);

    Matrix3 operator*(double d);

    Matrix3 &operator*=(double d);

    Vector3 operator*(const Vector3 &vector);


    void transform(Vector3 &vector);

    void transpose();

    Vector3 &operator[](int row);

    void set_row(int row, Vector3 vector);

    void set_row(int row, double x, double y, double z);

    void set_column(int column, Vector3 vector);

    Vector3 get_row(int row);

    Vector3 get_column(int column);

    void set(Matrix3 &matrix);

    double get(int index);

    void set(int index, double value);

    void invert();

    Matrix3 get_inverted();

    void set_identity();

    double det();


};

Vector3 operator*(Vector3 &vector, Matrix3 &matrix);

std::ostream &operator<<(std::ostream &strm, Matrix3 &matrix);



#endif //GRIDLIGHT_RAST_MATRIX3_H
