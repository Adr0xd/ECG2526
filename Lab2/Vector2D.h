//
//  vec2.h
//  Lab2
//
//  Copyright © 2016 CGIS. All rights reserved.
//

#pragma once

#include <cmath>
#include <iostream>
#include <limits>

#include "Vector3D.h"
#include "Vector4D.h"

namespace egc {

class Vector2D
{
public:
    union
    {
        float x;
        float u;
    };

    union
    {
        float y;
        float v;
    };

    //=========================================
    //constructors
    //=========================================

    //default constructor creates a zero vector
    Vector2D()
    {
		x = 0.0f;
		y = 0.0f;
    }

    //creates a vector (fX, fY)
    Vector2D(float fX, float fY)
    {
		x = fX;
		y = fY;
    }

    //copy constructor
    Vector2D(const Vector2D &srcVector)
    {
		x = srcVector.x;
		y = srcVector.y;
    }

    Vector2D(const egc::Vector3D &srcVector)
    {
		x = srcVector.x;
		y = srcVector.y;
    }

    Vector2D(const egc::Vector4D &srcVector)
    {
		x = srcVector.x;
		y = srcVector.y;
    }

    //=========================================
    //
    //=========================================

    bool operator ==(const Vector2D& srcVector) const
    {
        return (std::abs(x - srcVector.x) < std::numeric_limits<float>::epsilon()) && (std::abs(y - srcVector.y) < std::numeric_limits<float>::epsilon());
    }

    friend std::ostream& operator<< (std::ostream &out, const Vector2D& srcVector);

    //=========================================
    //2D vector operations
    //TO BE IMPLEMENTED
    //=========================================

    Vector2D& operator =(const Vector2D &srcVector);
    Vector2D operator +(const Vector2D& srcVector) const;
    Vector2D& operator +=(const Vector2D& srcVector);
    Vector2D operator *(float scalarValue) const;
    Vector2D operator -(const Vector2D& srcVector) const;
    Vector2D& operator -=(const Vector2D& srcVector);
    Vector2D operator -() const;
    float length() const;
    Vector2D& normalize();
};

    inline std::ostream& operator<< (std::ostream &out, const Vector2D& srcVector)
    {
        out << "(" << srcVector.x << ", " << srcVector.y << ")";
        return out;
    };


    float dotProduct(const Vector2D& v1, const Vector2D& v2);
}
