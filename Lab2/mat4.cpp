#include "mat4.h"

#include "mat3.h"

namespace egc {
    mat4 &mat4::operator =(const mat4 &srcMatrix) {
        for (int i = 0; i < 16; i++) {
            this->matrixData[i] = srcMatrix.matrixData[i];
        }
        return *this;
    }

    mat4 mat4::operator *(float scalarValue) const {
        mat4 result = *this;
        for (int i = 0; i < 16; i++) {
            result.matrixData[i] *= scalarValue;
        }
        return result;
    }

    mat4 mat4::operator *(const mat4 &srcMatrix) const {
        mat4 result = mat4(); // identity matrix;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.at(i, j) = 0;
                for (int k = 0; k < 4; k++) {
                    result.at(i, j) += this->at(i, k) * srcMatrix.at(k, j);
                }
            }
        }
        return result;
    }

    vec4 mat4::operator *(const vec4 &srcVector) const {
        vec4 result = vec4();
        for (int i = 0; i < 4; i++) {
            result.x += this->at(0, i) * srcVector.x;
            result.y += this->at(1, i) * srcVector.y;
            result.z += this->at(2, i) * srcVector.z;
            result.w += this->at(3, i) * srcVector.w;
        }
        return result;
    }

    mat4 mat4::operator +(const mat4 &srcMatrix) const {
        mat4 result = *this;
        for (int i = 0; i < 16; i++) {
            result.matrixData[i] += srcMatrix.matrixData[i];
        }
        return result;
    }

    //get element by (row, column)
    float &mat4::at(int i, int j) {
        return this->matrixData[i + j * 4];
    }

    const float &mat4::at(int i, int j) const {
        return this->matrixData[i + j * 4];
    }

    float mat4::determinant() const {
        float src_mat3_00[] = {
            this->at(1, 1), this->at(2, 1), this->at(3, 1),
            this->at(1, 2), this->at(2, 2), this->at(3, 2),
            this->at(1, 3), this->at(2, 3), this->at(3, 3),
        };
        mat3 mat3_00 = mat3(src_mat3_00);

        float src_mat3_01[] = {
            this->at(1, 0), this->at(2, 0), this->at(3, 0),
            this->at(1, 2), this->at(2, 2), this->at(3, 2),
            this->at(1, 3), this->at(2, 3), this->at(3, 3),
        };
        mat3 mat3_01 = mat3(src_mat3_01);

        float src_mat3_02[] = {
            this->at(1, 0), this->at(2, 0), this->at(3, 0),
            this->at(1, 1), this->at(2, 1), this->at(3, 1),
            this->at(3, 1), this->at(2, 3), this->at(3, 3),
        };
        mat3 mat3_02 = mat3(src_mat3_02);

        float src_mat3_03[] = {
            this->at(1, 0), this->at(2, 0), this->at(3, 0),
            this->at(1, 1), this->at(2, 1), this->at(3, 1),
            this->at(1, 2), this->at(2, 2), this->at(3, 2),
        };
        mat3 mat3_03 = mat3(src_mat3_03);
        return
                this->at(0, 0) * mat3_00.determinant()
                - this->at(0, 1) * mat3_01.determinant()
                + this->at(0, 2) * mat3_02.determinant()
                - this->at(0, 3) * mat3_03.determinant();
    }

    mat4 mat4::inverse() const {
        mat4 thisT = this->transpose();

        const float det = this->determinant();
        if (det == 0) {
            return nullptr;
        }

        float src_mat3_00[] = {
            thisT.at(1, 1), thisT.at(2, 1), thisT.at(3, 1),
            thisT.at(1, 2), thisT.at(2, 2), thisT.at(3, 2),
            thisT.at(1, 3), thisT.at(2, 3), thisT.at(3, 3),
        };
        const float a00 = mat3(src_mat3_00).determinant();

        float src_mat3_01[] = {
            thisT.at(1, 0), thisT.at(2, 0), thisT.at(3, 0),
            thisT.at(1, 2), thisT.at(2, 2), thisT.at(3, 2),
            thisT.at(1, 3), thisT.at(2, 3), thisT.at(3, 3),
        };
        const float a01 = -mat3(src_mat3_01).determinant();

        float src_mat3_02[] = {
            thisT.at(1, 0), thisT.at(2, 0), thisT.at(3, 0),
            thisT.at(1, 1), thisT.at(2, 1), thisT.at(3, 1),
            thisT.at(1, 3), thisT.at(2, 3), thisT.at(3, 3),
        };
        const float a02 = mat3(src_mat3_02).determinant();

        float src_mat3_03[] = {
            thisT.at(1, 0), thisT.at(2, 0), thisT.at(3, 0),
            thisT.at(1, 1), thisT.at(2, 1), thisT.at(3, 1),
            thisT.at(1, 2), thisT.at(2, 2), thisT.at(3, 2),
        };
        const float a03 = -mat3(src_mat3_03).determinant();

        float src_mat3_10[] = {
            thisT.at(0, 1), thisT.at(2, 1), thisT.at(3, 1),
            thisT.at(0, 2), thisT.at(2, 2), thisT.at(3, 2),
            thisT.at(0, 3), thisT.at(2, 3), thisT.at(3, 3),
        };
        const float a10 = -mat3(src_mat3_10).determinant();

        float src_mat3_11[] = {
            thisT.at(0, 0), thisT.at(2, 0), thisT.at(3, 0),
            thisT.at(0, 2), thisT.at(2, 2), thisT.at(3, 2),
            thisT.at(0, 3), thisT.at(2, 3), thisT.at(3, 3),
        };
        const float a11 = mat3(src_mat3_11).determinant();

        float src_mat3_12[] = {
            thisT.at(0, 0), thisT.at(2, 0), thisT.at(3, 0),
            thisT.at(0, 1), thisT.at(2, 1), thisT.at(3, 1),
            thisT.at(0, 3), thisT.at(2, 3), thisT.at(3, 3),
        };
        const float a12 = -mat3(src_mat3_12).determinant();

        float src_mat3_13[] = {
            thisT.at(0, 0), thisT.at(2, 0), thisT.at(3, 0),
            thisT.at(0, 1), thisT.at(2, 1), thisT.at(3, 1),
            thisT.at(0, 2), thisT.at(2, 2), thisT.at(3, 2),
        };
        const float a13 = mat3(src_mat3_13).determinant();

        float src_mat3_20[] = {
            thisT.at(0, 1), thisT.at(1, 1), thisT.at(3, 1),
            thisT.at(0, 2), thisT.at(1, 2), thisT.at(3, 2),
            thisT.at(0, 3), thisT.at(1, 3), thisT.at(3, 3),
        };
        const float a20 = mat3(src_mat3_20).determinant();

        float src_mat3_21[] = {
            thisT.at(0, 0), thisT.at(1, 0), thisT.at(3, 0),
            thisT.at(0, 2), thisT.at(1, 2), thisT.at(3, 2),
            thisT.at(0, 3), thisT.at(1, 3), thisT.at(3, 3),
        };
        const float a21 = -mat3(src_mat3_21).determinant();

        float src_mat3_22[] = {
            thisT.at(0, 0), thisT.at(1, 0), thisT.at(3, 0),
            thisT.at(0, 1), thisT.at(1, 1), thisT.at(3, 1),
            thisT.at(0, 3), thisT.at(1, 3), thisT.at(3, 3),
        };
        const float a22 = mat3(src_mat3_22).determinant();

        float src_mat3_23[] = {
            thisT.at(0, 0), thisT.at(1, 0), thisT.at(3, 0),
            thisT.at(0, 1), thisT.at(1, 1), thisT.at(3, 1),
            thisT.at(0, 2), thisT.at(1, 2), thisT.at(3, 2),
        };
        const float a23 = -mat3(src_mat3_23).determinant();

        float src_mat3_30[] = {
            thisT.at(0, 1), thisT.at(1, 1), thisT.at(2, 1),
            thisT.at(0, 2), thisT.at(1, 2), thisT.at(2, 2),
            thisT.at(0, 3), thisT.at(1, 3), thisT.at(2, 3),
        };
        const float a30 = -mat3(src_mat3_30).determinant();

        float src_mat3_31[] = {
            thisT.at(0, 0), thisT.at(1, 0), thisT.at(2, 0),
            thisT.at(0, 2), thisT.at(1, 2), thisT.at(2, 2),
            thisT.at(0, 3), thisT.at(1, 3), thisT.at(2, 3),
        };
        const float a31 = mat3(src_mat3_31).determinant();

        float src_mat3_32[] = {
            thisT.at(0, 0), thisT.at(1, 0), thisT.at(2, 0),
            thisT.at(0, 1), thisT.at(1, 1), thisT.at(2, 1),
            thisT.at(0, 3), thisT.at(1, 3), thisT.at(2, 3),
        };
        const float a32 = -mat3(src_mat3_32).determinant();

        float src_mat3_33[] = {
            thisT.at(0, 0), thisT.at(1, 0), thisT.at(2, 0),
            thisT.at(0, 1), thisT.at(1, 1), thisT.at(2, 1),
            thisT.at(0, 2), thisT.at(1, 2), thisT.at(2, 2),
        };
        const float a33 = mat3(src_mat3_33).determinant();

        float srcMatrix[] = {
            a00 / det, a10 / det, a20 / det, a30 / det,
            a01 / det, a11 / det, a21 / det, a31 / det,
            a02 / det, a12 / det, a22 / det, a32 / det,
            a03 / det, a13 / det, a23 / det, a33 / det
        };

        return mat4(srcMatrix);
    }

    mat4 mat4::transpose() const {
        float srcMat[] = {
            this->at(0, 0), this->at(0, 1), this->at(0, 2), this->at(0, 3),
            this->at(1, 0), this->at(1, 1), this->at(1, 2), this->at(1, 3),
            this->at(2, 0), this->at(2, 1), this->at(2, 2), this->at(2, 3),
            this->at(3, 0), this->at(3, 1), this->at(3, 2), this->at(3, 3),
        };
        return mat4(srcMat);
    }
}
