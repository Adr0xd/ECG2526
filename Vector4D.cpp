#include "Vector4D.h"

namespace egc {
    Vector4D& Vector4D::operator =(const Vector4D &srcVector) {
        this->x = srcVector.x;
        this->y = srcVector.y;
        this->z = srcVector.z;
        this->w = srcVector.w;
        return *this;
    }

    Vector4D Vector4D::operator +(const Vector4D &srcVector) const {
        return {this->x + srcVector.x, this->y + srcVector.y, this->z + srcVector.z, this->w + srcVector.w};
    }

    Vector4D &Vector4D::operator +=(const Vector4D &srcVector) {
        this->x += srcVector.x;
        this->y += srcVector.y;
        this->z += srcVector.z;
        this->w += srcVector.w;
        return *this;
    }

    Vector4D Vector4D::operator -(const Vector4D &srcVector) const {
        return {this->x - srcVector.x, this->y - srcVector.y, this->z - srcVector.z, this->w - srcVector.w};
    }

    Vector4D &Vector4D::operator -=(const Vector4D &srcVector) {
        this->x -= srcVector.x;
        this->y -= srcVector.y;
        this->z -= srcVector.z;
        this->w -= srcVector.w;
        return *this;
    }

    float Vector4D::length() const {
        return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
    }

    Vector4D& Vector4D::normalize() {
        float len = this->length();
        if (len > 0) {
            this->x /= len;
            this->y /= len;
            this->z /= len;
            this->w /= len;
        }
        return *this;
    }
}