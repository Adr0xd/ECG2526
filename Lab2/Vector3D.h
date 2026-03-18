//
//  vec3.h
//  Lab2
//
//  Copyright © 2016 CGIS. All rights reserved.
//

#pragma once

#include <cmath>
#include <limits>

#include "Vector4D.h"

namespace egc {
    class Vector3D {
    public:
        union {
            float x;
            float r;
            float u;
        };

        union {
            float y;
            float g;
            float v;
        };

        union {
            float z;
            float b;
            float w;
        };

        //=========================================
        //constructors
        //=========================================

        //default constructor creates a zero vector
        Vector3D() {
            x = 0.0f;
            y = 0.0f;
            z = 0.0f;
        }

        //creates a vector (fX, fY, fZ)
        Vector3D(float fX, float fY, float fZ) {
            x = fX;
            y = fY;
            z = fZ;
        }

        //copy constructor
        Vector3D(const Vector3D &srcVector) {
            x = srcVector.x;
            y = srcVector.y;
            z = srcVector.z;
        }

        Vector3D(const egc::Vector4D &srcVector) {
            x = srcVector.x;
            y = srcVector.y;
            z = srcVector.z;
        }

        //=========================================
        //
        //=========================================

        bool operator ==(const Vector3D &srcVector) const {
            return (std::abs(x - srcVector.x) < std::numeric_limits<float>::epsilon()) && (
                       std::abs(y - srcVector.y) < std::numeric_limits<float>::epsilon()) && (
                       std::abs(z - srcVector.z) < std::numeric_limits<float>::epsilon());
        }

        friend std::ostream &operator<<(std::ostream &out, const Vector3D &srcVector);

        //=========================================
        //3D vector operations
        //TO BE IMPLEMENTED
        //=========================================

        Vector3D &operator =(const Vector3D &srcVector);

        Vector3D operator +(const Vector3D &srcVector) const;

        Vector3D &operator +=(const Vector3D &srcVector);

        Vector3D operator *(float scalarValue) const;

        Vector3D operator -(const Vector3D &srcVector) const;

        Vector3D &operator -=(const Vector3D &srcVector);

        Vector3D operator -() const;

        float length() const;

        Vector3D &normalize();
    };

    inline std::ostream &operator<<(std::ostream &out, const Vector3D &srcVector) {
        out << "(" << srcVector.x << ", " << srcVector.y << ", " << srcVector.z << ")";
        return out;
    }

    float dotProduct(const Vector3D &v1, const Vector3D &v2);

    Vector3D crossProduct(const Vector3D &v1, const Vector3D &v2);
}
