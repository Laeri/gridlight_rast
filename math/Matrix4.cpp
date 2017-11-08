//
// Created by hexaquat on 08/11/17.
//

#include "Matrix4.h"
#include <cmath>
#include <assert.h>


Matrix4::Matrix4() {
    rows = std::vector<Vector4>(DIM, Vector4(0, 0, 0, 0));
}


Matrix4::Matrix4(std::vector<double> values) {
    assert(4 * 4 == values.size());
    rows = std::vector<Vector4>(DIM, Vector4(0, 0, 0, 0));
    for (int row = 0; row < 4; row++) {
        rows[row] = Vector4(values[row * DIM], values[DIM * row + 1], values[DIM * row + 2], values[DIM * row + 3]);
    }
}

Matrix4 Matrix4::operator*(double d) {
    Matrix4 result = Matrix4();
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            result[i][j] = rows[i][j] * d;
        }
    }
    return result;
}

Matrix4 Matrix4::operator+(Matrix4 &matrix4) {
    Matrix4 result = Matrix4();
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            result[i][j] = rows[i][j] + matrix4[i][j];
        }
    }
    return result;
}

Matrix4 &Matrix4::operator+=(Matrix4 &matrix4) {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            rows[i][j] += matrix4[i][j];
        }
    }
    return *this;
}

Matrix4 Matrix4::operator-(Matrix4 &matrix4) {
    Matrix4 result = Matrix4();
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            result[i][j] = rows[i][j] - matrix4[i][j];
        }
    }
    return result;
}

Matrix4 &Matrix4::operator-=(Matrix4 &matrix4) {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            rows[i][j] -= matrix4[i][j];
        }
    }
    return *this;
}

Matrix4 Matrix4::operator*(Matrix4 &matrix4) {
    Matrix4 result = Matrix4();
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            result[i][j] = rows[i].dot(matrix4.get_column(j));
        }
    }
    return result;
}

Matrix4 &Matrix4::operator*=(Matrix4 &matrix4) {
    Matrix4 result = Matrix4();
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            result[i][j] = (*this).get_row(i).dot(matrix4.get_column(j));
        }
    }
    set(result);
    return *this;
}

Vector4 &Matrix4::operator[](int index) {
    return rows[index];
}

Vector4 Matrix4::operator*(const Vector4 &vector4) {
    Vector4 vec = Vector4(vector4);
    transform(vec);
    return vec;
}

bool Matrix4::operator==(Matrix4 &matrix4) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if ((*this)[i][j] != matrix4[i][j]) return false;
        }
    }
    return true;
}

std::vector<double> Matrix4::get_values() {
    std::vector<double> values;
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            values.push_back(rows[i][j]);
        }
    }
    return values;
}

Vector4 Matrix4::get_column(int column) {
    Vector4 col = Vector4(get(column), get(column + DIM), get(column + 2 * DIM), get(column + 3 * DIM));
    return col;
}

void Matrix4::set_column(int column, Vector4 &vector4) {
    rows[0][column] = vector4.x;
    rows[1][column] = vector4.y;
    rows[2][column] = vector4.z;
    rows[3][column] = vector4.w;
}

Vector4 Matrix4::get_row(int row) const {
    return rows[row];
}

void Matrix4::set_row(int row, Vector4 &vector4) {
    rows[row] = vector4;
}

void Matrix4::set_row(int row, double x, double y, double z, double w) {
    rows[row][0] = x;
    rows[row][1] = y;
    rows[row][2] = z;
    rows[row][3] = w;
};


double Matrix4::get(int index) {
    int row = index / DIM;
    int column = index % DIM;
    return (*this)[row][column];
}

void Matrix4::set(int index, double value) {
    int row = index / DIM;
    int column = index % DIM;
    (*this)[row][column] = value;
}

void Matrix4::set(Matrix4 &matrix4) {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            rows[i][j] = matrix4[i][j];
        }
    }
}

void Matrix4::swap_row(int r1, int r2) {
    Vector4 row1 = rows[r1];
    Vector4 row2 = rows[r2];
    rows[r1] = row2;
    rows[r2] = row1;
}

double Matrix4::det() {
    int row = 0;
    int sign = 1;
    for (int column = 0; column < DIM; column++) {
        if (rows[row][column] == 0) {
            for (int i = row + 1; i < DIM; i++) {
                if (rows[i][column] != 0) {
                    swap_row(row, i);
                    sign *= -1;
                    break;
                }
            }
        }

        for (int i = row + 1; i < DIM; i++) {
            // skip elemination if already 0
            if (rows[i][column] == 0) continue;
            double scale = (1.0 / rows[row][column]) * rows[i][column];
            Vector4 tmp_row = Vector4(rows[row]);
            tmp_row *= scale;
            rows[i] -= tmp_row;
        }
        row++;
    }
    return sign * rows[0][0] * rows[1][1] * rows[2][2] * rows[3][3];

}

void Matrix4::invert() {
    Matrix4 inverted = get_inverted();
    set(inverted.get_values());
}

Matrix4 Matrix4::get_inverted() {

    Matrix4 inverted = Matrix4();
    Matrix4 tmp_mat = Matrix4((*this).get_values());
    inverted.set_identity();

    int row = 0;
    for (int column = 0; column < DIM; column++) {

        // check if rows need to be swapped
        if (tmp_mat[row][column] == 0) {
            for (int i = row + 1; i < DIM; i++) {
                if (tmp_mat[i][column] != 0) {
                    tmp_mat.swap_row(row, i);
                    inverted.swap_row(row, i);
                    break;
                }
            }
        }

        for (int i = row + 1; i < DIM; i++) {
            // skip elemination if already 0
            if (tmp_mat[i][column] == 0) continue;

            double scale = (1.0 / tmp_mat[row][column]) * tmp_mat[i][column];
            Vector4 tmp_row = Vector4(tmp_mat[row]);
            tmp_row *= scale;
            tmp_mat[i] -= tmp_row;

            Vector4 tmp_row_inverted = Vector4(inverted[row]);
            tmp_row_inverted *= scale;
            inverted[i] -= tmp_row_inverted;
        }
        row++;
    }

    // set_scale elements on diagonal to 1
    inverted[0] *= (1.0 / tmp_mat[0][0]);
    inverted[1] *= (1.0 / tmp_mat[1][1]);
    inverted[2] *= (1.0 / tmp_mat[2][2]);
    inverted[3] *= (1.0 / tmp_mat[3][3]);

    tmp_mat[0] *= (1.0 / tmp_mat[0][0]);
    tmp_mat[1] *= (1.0 / tmp_mat[1][1]);
    tmp_mat[2] *= (1.0 / tmp_mat[2][2]);
    tmp_mat[3] *= (1.0 / tmp_mat[3][3]);


    // eleminate all values above the diagonal

    for (int column = 0; column < DIM; column++) {
        for (int row = column - 1; row >= 0; row--) {
            if (tmp_mat[row][column] != 0) {
                double scale = tmp_mat[row][column];
                Vector4 tmp_row = Vector4(tmp_mat[column]);
                tmp_row *= scale;
                tmp_mat[row] -= tmp_row;

                Vector4 tmp_row_inverted = Vector4(inverted[column]);
                tmp_row_inverted *= scale;
                inverted[row] -= tmp_row_inverted;
            }
        }
    }

    return inverted;
}

void Matrix4::set_identity() {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            if (i == j)rows[i][j] = 1;
            else rows[i][j] = 0;
        }
    }
}

void Matrix4::set_scale(double scale_x, double scale_y, double scale_z) {
    rows[0][0] = scale_x;
    rows[1][1] = scale_y;
    rows[2][2] = scale_z;
}

void Matrix4::rot(Vector3 &axis, double theta) {
    Vector4 p, q, r, s;
    float cos_theta = std::cos(theta);
    float sin_theta = std::sin(theta);
    p.x = axis.x * axis.x * (1 - cos_theta) + cos_theta;
    p.y = axis.x * axis.y * (1 - cos_theta) + axis.z * sin_theta;
    p.z = axis.x * axis.z * (1 - cos_theta) - axis.y * sin_theta;
    p.w = 0;
    q.x = axis.x * axis.y * (1 - cos_theta) - axis.z * sin_theta;
    q.y = axis.y * axis.y * (1 - cos_theta) + cos_theta;
    q.z = axis.y * axis.z * (1 - cos_theta) + axis.x * sin_theta;
    q.w = 0;
    r.x = axis.x * axis.z * (1 - cos_theta) + axis.y * sin_theta;
    r.y = axis.y * axis.z * (1 - cos_theta) - axis.x * sin_theta;
    r.z = axis.z * axis.z * (1 - cos_theta) + cos_theta;
    r.w = 0;
    s.w = 1;
    set_column(0, p);
    set_column(1, q);
    set_column(2, r);
    set_column(3, s);

}

void Matrix4::rot_x(double theta) {
    std::vector<double> values = {
            1, 0, 0, 0,
            0, std::cos(theta), -std::sin(theta), 0,
            0, std::sin(theta), std::cos(theta), 0,
            0, 0, 0, 1
    };
    set(values);
}

void Matrix4::rot_y(double theta) {
    std::vector<double> values = {
            cos(theta), 0, sin(theta), 0,
            0, 1, 0, 0,
            -sin(theta), 0, cos(theta), 0,
            0, 0, 0, 1
    };
    set(values);
}

void Matrix4::rot_z(double theta) {
    std::vector<double> values = {
            cos(theta), -sin(theta), 0, 0,
            sin(theta), cos(theta), 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
    };
    set(values);
}

void Matrix4::translate(Vector3 &vector3) {
    rows[0][3] += vector3.x;
    rows[1][3] += vector3.y;
    rows[2][3] += vector3.z;
}

void Matrix4::get_translation(Vector3 &vector3) {
    vector3.x = rows[0][3];
    vector3.y = rows[1][3];
    vector3.z = rows[2][3];
}

Vector3 Matrix4::get_translation() {
    return get_column(3).xyz();
}

void Matrix4::set_translation(Vector3 &translation) {
    rows[0][3] = translation.x;
    rows[1][3] = translation.y;
    rows[2][3] = translation.z;
}

void Matrix4::set(std::vector<double> values) {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            rows[i][j] = values[4 * i + j];
        }
    }
}


void Matrix4::transform(Vector3 &vector3) {
    float x = rows[0][0] * vector3.x + rows[0][1] * vector3.y + rows[0][2] * vector3.z;
    float y = rows[1][0] * vector3.x + rows[1][1] * vector3.y + rows[1][2] * vector3.z;
    float z = rows[2][0] * vector3.x + rows[2][1] * vector3.y + rows[2][2] * vector3.z;
    vector3.x = x;
    vector3.y = y;
    vector3.z = z;
}

void Matrix4::transform(Vector4 &vector4) {
    float x = rows[0][0] * vector4.x + rows[0][1] * vector4.y + rows[0][2] * vector4.z + rows[0][3] * vector4.w;
    float y = rows[1][0] * vector4.x + rows[1][1] * vector4.y + rows[1][2] * vector4.z + rows[1][3] * vector4.w;
    float z = rows[2][0] * vector4.x + rows[2][1] * vector4.y + rows[2][2] * vector4.z + rows[2][3] * vector4.w;
    float w = rows[3][0] * vector4.x + rows[3][1] * vector4.y + rows[3][2] * vector4.z + rows[3][3] * vector4.w;
    vector4.x = x;
    vector4.y = y;
    vector4.z = z;
    vector4.w = w;
}

void Matrix4::transpose() {
    Matrix4 tmp;
    tmp.set_column(0, rows[0]);
    tmp.set_column(1, rows[1]);
    tmp.set_column(2, rows[2]);
    tmp.set_column(3, rows[3]);
    set(tmp);
}

std::ostream &operator<<(std::ostream &strm, Matrix4 &matrix4) {
    strm << "Matrix4(" << std::endl;
    for (int y = 0; y < Matrix4::DIM; y++) {
        strm << "(";
        for (int x = 0; x < Matrix4::DIM; x++) {
            strm << matrix4[y][x];
            if (x < Matrix4::DIM - 1) strm << ",";
        }
        strm << ")" << std::endl;
    }
    strm << ")" << std::endl;
}
