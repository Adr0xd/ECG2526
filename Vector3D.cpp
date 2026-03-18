#include "Vector3D.h"

namespace egc {
    Vector3D& Vector3D::operator =(const Vector3D &srcVector) {
        this->x = srcVector.x;
        this->y = srcVector.y;
        this->z = srcVector.z;
        return *this;
    }

    Vector3D Vector3D::operator +(const Vector3D &srcVector) const {
        Vector3D result;
        result.x = this->x + srcVector.x;
        result.y = this->y + srcVector.y;
        result.z = this->z + srcVector.z;
        return result;
    }

    Vector3D &Vector3D::operator +=(const Vector3D &srcVector) {
        this->x += srcVector.x;
        this->y += srcVector.y;
        this->z += srcVector.z;
        return *this;
    }

    Vector3D Vector3D::operator *(const float scalarValue) const {
        return {this->x * scalarValue, this->y * scalarValue, this->z * scalarValue};
    }

    Vector3D Vector3D::operator -(const Vector3D &srcVector) const {
        return {this->x - srcVector.x, this->y - srcVector.y, this->z - srcVector.z};
    }

    Vector3D &Vector3D::operator -=(const Vector3D &srcVector) {
        this->x -= srcVector.x;
        this->y -= srcVector.y;
        this->z -= srcVector.z;
        return *this;
    }

    Vector3D Vector3D::operator -() const {
        return {-this->x, -this->y, -this->z};
    }

    float Vector3D::length() const {
        return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    }

    Vector3D& Vector3D::normalize() {
        float len = this->length();
        if (len > 0) {
            this->x /= len;
            this->y /= len;
            this->z /= len;
        }
        return *this;
    }

    float dotProduct(const Vector3D& v1, const Vector3D& v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    Vector3D crossProduct(const Vector3D& v1, const Vector3D& v2) {
        return {
            v1.y * v2.z - v1.z * v2.y,
            v1.z * v2.x - v1.x * v2.z,
            v1.x * v2.y - v1.y * v2.x
        };
    }
}
