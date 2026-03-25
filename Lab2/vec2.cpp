#include "vec2.h"

namespace egc {

    vec2& vec2::operator =(const vec2 &srcVector) {
        this->x = srcVector.x;
        this->y = srcVector.y;
        return *this;
    }

    // const after the parameter list makes the function constant, and it
    // means that it cannot modify "this"
    vec2 vec2::operator +(const vec2 &srcVector) const {
        vec2 result;
        result.x = this->x + srcVector.x;
        result.y = this->y + srcVector.y;
        return result;
    }

    vec2 &vec2::operator +=(const vec2 &srcVector) {
        this->x += srcVector.x;
        this->y += srcVector.y;
        return *this;
    }

    vec2 vec2::operator *(const float scalarValue) const {
        return {this->x * scalarValue, this->y * scalarValue};
    }

    vec2 vec2::operator -(const vec2& srcVector) const {
        return {this->x - srcVector.x, this->y - srcVector.y};
    }

    vec2& vec2::operator -=(const vec2& srcVector) {
        this->x -= srcVector.x;
        this->y -= srcVector.y;
        return *this;
    }

    vec2 vec2::operator -() const {
        return {-this->x, -this->y};
    }

    float vec2::length() const {
        return std::sqrt(this->x * this->x + this->y * this->y);
    }

    vec2& vec2::normalize() {
        const float len = this->length();
        if (len > 0) {
            this->x /= len;
            this->y /= len;
        }
        return *this;
    }

    float dotProduct(const vec2& v1, const vec2& v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }

}

