#include "vec3.h"

namespace egc {
    vec3& vec3::operator =(const vec3 &srcVector) {
        this->x = srcVector.x;
        this->y = srcVector.y;
        this->z = srcVector.z;
        return *this;
    }

    vec3 vec3::operator +(const vec3 &srcVector) const {
        vec3 result;
        result.x = this->x + srcVector.x;
        result.y = this->y + srcVector.y;
        result.z = this->z + srcVector.z;
        return result;
    }

    vec3 &vec3::operator +=(const vec3 &srcVector) {
        this->x += srcVector.x;
        this->y += srcVector.y;
        this->z += srcVector.z;
        return *this;
    }

    vec3 vec3::operator *(const float scalarValue) const {
        return {this->x * scalarValue, this->y * scalarValue, this->z * scalarValue};
    }

    vec3 vec3::operator -(const vec3 &srcVector) const {
        return {this->x - srcVector.x, this->y - srcVector.y, this->z - srcVector.z};
    }

    vec3 &vec3::operator -=(const vec3 &srcVector) {
        this->x -= srcVector.x;
        this->y -= srcVector.y;
        this->z -= srcVector.z;
        return *this;
    }

    vec3 vec3::operator -() const {
        return {-this->x, -this->y, -this->z};
    }

    float vec3::length() const {
        return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    }

    vec3& vec3::normalize() {
        const float len = this->length();
        if (len > 0) {
            this->x /= len;
            this->y /= len;
            this->z /= len;
        }
        return *this;
    }

    float dotProduct(const vec3& v1, const vec3& v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    vec3 crossProduct(const vec3& v1, const vec3& v2) {
        return {
            v1.y * v2.z - v1.z * v2.y,
            v1.z * v2.x - v1.x * v2.z,
            v1.x * v2.y - v1.y * v2.x
        };
    }
}
