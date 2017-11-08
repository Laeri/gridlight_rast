//
// Created by hexaquat on 08/11/17.
//

#include "Matrix3.h"


Matrix3::Matrix3() {
    rows = std::vector<Vector3>(3, Vector3(0, 0, 0));
}

Matrix3::Matrix3(std::vector<double> values) {
    rows = {Vector3(values[M11], values[M12], values[M13]), Vector3(values[M21], values[M22], values[M23]),
            Vector3(values[M31], values[M32], values[M33])};

}

void Matrix3::invert() {
    Matrix3 result = get_inverted();
    set(result);
}

Matrix3 Matrix3::get_inverted() {
    Matrix3 result = Matrix3();
    result[0][0] = rows[1][1] * rows[2][2] - rows[1][2] * rows[2][1];
    result[0][1] = -(rows[0][1] * rows[2][2] - rows[0][2] * rows[2][1]);
    result[0][2] = rows[0][1] * rows[1][2] - rows[0][2] * rows[1][1];
    result[1][0] = -(rows[1][0] * rows[2][2] - rows[1][2] * rows[2][0]);
    result[1][1] = rows[0][0] * rows[2][2] - rows[0][2] * rows[2][0];
    result[1][2] = -(rows[0][0] * rows[1][2] - rows[0][2] * rows[1][0]);
    result[2][0] = rows[1][0] * rows[2][1] - rows[1][1] * rows[2][0];
    result[2][1] = -(rows[0][0] * rows[2][1] - rows[0][1] * rows[2][0]);
    result[2][2] = rows[0][0] * rows[1][1] - rows[0][1] * rows[1][0];
    result *= (1.0 / det());
    return result;
}

void Matrix3::set_identity() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == j) rows[i][j] = 1;
            else rows[i][j] = 0;
        }
    }
}

double Matrix3::det() {
    return rows[0][0] * rows[1][1] * rows[2][2] + rows[0][1] * rows[1][2] * rows[2][0] +
           rows[1][0] * rows[2][1] * rows[0][2] - rows[0][2] * rows[1][1] * rows[2][0] -
           rows[0][1] * rows[1][0] * rows[2][2] - rows[1][2] * rows[2][1] * rows[0][0];
}

double Matrix3::get(int index) {
    int row = index / 3;
    int column = index % 3;
    return rows[row][column];
}

void Matrix3::set(int index, double value) {
    int row = index / 3;
    int column = index % 3;
    rows[row][column] = value;
}

Vector3 Matrix3::get_row(int row) {
    return rows[row];
}

void Matrix3::set_row(int row, Vector3 vector) {
    rows[row] = vector;
}

void Matrix3::set_row(int row, double x, double y, double z) {
    rows[row][0] = x;
    rows[row][1] = y;
    rows[row][2] = z;
}

Vector3 Matrix3::get_column(int column) {
    return Vector3(get(column), get(column + 3), get(column + 6));
}

void Matrix3::set_column(int column, Vector3 vector) {
    rows[0][column] = vector.x;
    rows[1][column] = vector.y;
    rows[2][column] = vector.z;
}

void Matrix3::set(Matrix3 &matrix) {
    rows[0] = matrix.get_row(0);
    rows[1] = matrix.get_row(1);
    rows[2] = matrix.get_row(2);
}

Matrix3 Matrix3::operator+(Matrix3 &matrix) {
    Matrix3 result = Matrix3();
    result.set_row(0, rows[0] + matrix.get_row(0));
    result.set_row(1, rows[1] + matrix.get_row(1));
    result.set_row(2, rows[2] + matrix.get_row(2));
}

Matrix3 &Matrix3::operator+=(Matrix3 &matrix) {
    get_row(0) += matrix.get_row(0);
    get_row(1) += matrix.get_row(1);
    get_row(2) += matrix.get_row(2);
}

Matrix3 Matrix3::operator-(Matrix3 &matrix) {
    Matrix3 result = Matrix3();
    result.set_row(0, rows[0] - matrix.get_row(0));
    result.set_row(1, rows[1] - matrix.get_row(1));
    result.set_row(2, rows[2] - matrix.get_row(2));
}

Matrix3 &Matrix3::operator-=(Matrix3 &matrix) {
    rows[0] -= matrix.get_row(0);
    rows[1] -= matrix.get_row(1);
    rows[2] -= matrix.get_row(2);
}

Matrix3 Matrix3::operator*(Matrix3 &matrix) {
    Matrix3 result = Matrix3();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result[i][j] = get_row(i).dot(matrix.get_column(j));
        }
    }
    return result;
}

Matrix3 &Matrix3::operator*=(Matrix3 &matrix) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            rows[i][j] = get_row(i).dot(matrix.get_column(j));
        }
    }
    return (*this);
}

Vector3 Matrix3::operator*(const Vector3 &vector) {
    float x = rows[0].dot(vector);
    float y = rows[1].dot(vector);
    float z = rows[2].dot(vector);
    return Vector3(x, y, z);
}

Vector3 operator*(Vector3 &vector, Matrix3 &matrix) {
    float x = vector.dot(matrix.get_column(0));
    float y = vector.dot(matrix.get_column(1));
    float z = vector.dot(matrix.get_column(2));
    return Vector3(x, y, z);
}

void Matrix3::transform(Vector3 &vector) {
    float x = rows[0].dot(vector);
    float y = rows[1].dot(vector);
    float z = rows[2].dot(vector);
    vector.x = x;
    vector.y = y;
    vector.z = z;
}

Matrix3 Matrix3::operator*(double d) {
    Matrix3 result = Matrix3(*this);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result[i][j] *= d;
        }
    }
    return result;
}

Matrix3 &Matrix3::operator*=(double d) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            (*this)[i][j] *= d;
        }
    }
    return *this;
}

Vector3 &Matrix3::operator[](int row) {
    return rows[row];
}

std::ostream &operator<<(std::ostream &strm, Matrix3 &matrix3) {
    strm << "Matrix4(" << std::endl;
    for (int y = 0; y < Matrix3::DIM; y++) {
        strm << "(";
        for (int x = 0; x < Matrix3::DIM; x++) {
            strm << matrix3[y][x];
            if (x < Matrix3::DIM - 1) strm << ",";
        }
        strm << ")" << std::endl;
    }
    strm << ")" << std::endl;
}
