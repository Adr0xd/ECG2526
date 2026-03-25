#include "vec4.h"

namespace egc {
    vec4& vec4::operator =(const vec4 &srcVector) {
        this->x = srcVector.x;
        this->y = srcVector.y;
        this->z = srcVector.z;
        this->w = srcVector.w;
        return *this;
    }

    vec4 vec4::operator +(const vec4 &srcVector) const {
        return {this->x + srcVector.x, this->y + srcVector.y, this->z + srcVector.z, this->w + srcVector.w};
    }

    vec4 &vec4::operator +=(const vec4 &srcVector) {
        this->x += srcVector.x;
        this->y += srcVector.y;
        this->z += srcVector.z;
        this->w += srcVector.w;
        return *this;
    }

    vec4 vec4::operator -(const vec4 &srcVector) const {
        return {this->x - srcVector.x, this->y - srcVector.y, this->z - srcVector.z, this->w - srcVector.w};
    }

    vec4 &vec4::operator -=(const vec4 &srcVector) {
        this->x -= srcVector.x;
        this->y -= srcVector.y;
        this->z -= srcVector.z;
        this->w -= srcVector.w;
        return *this;
    }

    float vec4::length() const {
        return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
    }

    vec4& vec4::normalize() {
        const float len = this->length();
        if (len > 0) {
            this->x /= len;
            this->y /= len;
            this->z /= len;
            this->w /= len;
        }
        return *this;
    }
}