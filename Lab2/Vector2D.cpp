#include "Vector2D.h"

namespace egc {

    Vector2D& Vector2D::operator =(const Vector2D &srcVector) {
        this->x = srcVector.x;
        this->y = srcVector.y;
        return *this;
    }

    // const after the parameter list makes the function constant, and it
    // means that it cannot modify "this"
    Vector2D Vector2D::operator +(const Vector2D &srcVector) const {
        Vector2D result;
        result.x = this->x + srcVector.x;
        result.y = this->y + srcVector.y;
        return result;
    }

    Vector2D &Vector2D::operator +=(const Vector2D &srcVector) {
        this->x += srcVector.x;
        this->y += srcVector.y;
        return *this;
    }

    Vector2D Vector2D::operator *(const float scalarValue) const {
        return {this->x * scalarValue, this->y * scalarValue};
    }

    Vector2D Vector2D::operator -(const Vector2D& srcVector) const {
        return {this->x - srcVector.x, this->y - srcVector.y};
    }

    Vector2D& Vector2D::operator -=(const Vector2D& srcVector) {
        this->x -= srcVector.x;
        this->y -= srcVector.y;
        return *this;
    }

    Vector2D Vector2D::operator -() const {
        return {-this->x, -this->y};
    }

    float Vector2D::length() const {
        return std::sqrt(this->x * this->x + this->y * this->y);
    }

    Vector2D& Vector2D::normalize() {
        float len = this->length();
        if (len > 0) {
            this->x /= len;
            this->y /= len;
        }
        return *this;
    }

    float dotProduct(const Vector2D& v1, const Vector2D& v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }

}

