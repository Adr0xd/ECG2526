#include "mat3.h"

namespace egc {
    mat3 &mat3::operator =(const mat3 &srcMatrix) {
        for (int i = 0; i < 9; i++) {
            this->matrixData[i] = srcMatrix.matrixData[i];
        }
        return *this;
    }

    mat3 mat3::operator *(float scalarValue) const {
        mat3 result = *this;
        for (int i = 0; i < 9; i++) {
            result.matrixData[i] *= scalarValue;
        }
        return result;
    }

    mat3 mat3::operator *(const mat3 &srcMatrix) const {
        auto result = mat3(); // identity matrix;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                result.at(i, j) = 0;
                for (int k = 0; k < 3; k++) {
                    result.at(i, j) += this->at(i, k) * srcMatrix.at(k, j);
                }
            }
        }
        return result;
    }

    vec3 mat3::operator *(const vec3 &srcVector) const {
        auto result = vec3();
        result.x = this->at(0, 0) * srcVector.x + this->at(0, 1) * srcVector.y + this->at(0, 2) * srcVector.z;
        result.y = this->at(1, 0) * srcVector.x + this->at(1, 1) * srcVector.y + this->at(1, 2) * srcVector.z;
        result.z = this->at(2, 0) * srcVector.x + this->at(2, 1) * srcVector.y + this->at(2, 2) * srcVector.z;
        return result;
    }

    mat3 mat3::operator +(const mat3 &srcMatrix) const {
        mat3 result = *this;
        for (int i = 0; i < 9; i++) {
            result.matrixData[i] += srcMatrix.matrixData[i];
        }
        return result;
    }

    //get element by (row, column)
    float &mat3::at(int i, int j) {
        return this->matrixData[i + j * 3];
    }

    const float &mat3::at(int i, int j) const {
        return this->matrixData[i + j * 3];
    }

    float mat3::determinant() const {
        return
                this->at(0, 0) * (this->at(1, 1) * this->at(2, 2) - this->at(2, 1) * this->at(1, 2))
                - this->at(0, 1) * (this->at(1, 0) * this->at(2, 2) - this->at(1, 2) * this->at(2, 0))
                + this->at(0, 2) * (this->at(1, 0) * this->at(2, 1) - this->at(1, 1) * this->at(2, 0));
    }

    mat3 mat3::inverse() const {
        mat3 thisT = this->transpose();

        const float a00 = +thisT.at(1, 1) * thisT.at(2, 2) - thisT.at(2, 1) * thisT.at(1, 2);
        const float a01 = -thisT.at(1, 0) * thisT.at(2, 2) + thisT.at(1, 2) * thisT.at(2, 0);
        const float a02 = +thisT.at(1, 0) * thisT.at(2, 1) - thisT.at(1, 1) * thisT.at(2, 0);

        const float a10 = -thisT.at(0, 1) * thisT.at(2, 2) + thisT.at(0, 2) * thisT.at(2, 1);
        const float a11 = +thisT.at(0, 0) * thisT.at(2, 2) - thisT.at(0, 2) * thisT.at(2, 0);
        const float a12 = -thisT.at(0, 0) * thisT.at(2, 1) + thisT.at(0, 1) * thisT.at(2, 0);

        const float a20 = +thisT.at(0, 1) * thisT.at(1, 2) - thisT.at(0, 2) * thisT.at(1, 1);
        const float a21 = -thisT.at(0, 0) * thisT.at(1, 2) + thisT.at(0, 2) * thisT.at(1, 0);
        const float a22 = +thisT.at(0, 0) * thisT.at(1, 1) - thisT.at(0, 1) * thisT.at(1, 0);

        const float det = this->determinant();

        float srcMatrix[] = {
            a00 / det, a10 / det, a20 / det,
            a01 / det, a11 / det, a21 / det,
            a02 / det, a12 / det, a22 / det
        };

        return mat3(srcMatrix);
    }

    mat3 mat3::transpose() const {
        float srcMatrix[] = {
            this->at(0, 0), this->at(0, 1), this->at(0, 2),
            this->at(1, 0), this->at(1, 1), this->at(1, 2),
            this->at(2, 0), this->at(2, 1), this->at(2, 2)
        };
        return mat3(srcMatrix);
    }
}
