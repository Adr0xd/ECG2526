//
//  vec3.h
//  Lab2
//
//  Copyright © 2016 CGIS. All rights reserved.
//

#pragma once

#include <cmath>
#include <iostream>
#include <limits>

namespace egc {

class Vector4D
{
public:
    union
    {
        float x;
        float r;
    };
    
    union
    {
        float y;
        float g;
    };
    
    union
    {
        float z;
        float b;
    };
    
    union
    {
        float w;
        float a;
    };
    
    //=========================================
    //constructors
    //=========================================
    
    //default constructor creates a zero vector
    Vector4D()
    {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
    }
    
    //creates a vector (fX, fY, fZ, fW)
    Vector4D(float fX, float fY, float fZ, float fW)
    {
		x = fX;
		y = fY;
		z = fZ;
		w = fW;
    }
    
    //copy constructor
    Vector4D(const Vector4D &srcVector)
    {
		x = srcVector.x;
		y = srcVector.y;
		z = srcVector.z;
		w = srcVector.w;
    }
    
    //=========================================
    //
    //=========================================
    
    bool operator ==(const Vector4D& srcVector) const
    {
        return (std::abs(x - srcVector.x) < std::numeric_limits<float>::epsilon()) && (std::abs(y - srcVector.y) < std::numeric_limits<float>::epsilon()) && (std::abs(z - srcVector.z) < std::numeric_limits<float>::epsilon()) && (std::abs(w - srcVector.w) < std::numeric_limits<float>::epsilon());
    }
    
    friend std::ostream& operator<< (std::ostream &out, const Vector4D& srcVector);
    
    //=========================================
    //4D vector operations
    //TO BE IMPLEMENTED
    //=========================================
    
    Vector4D& operator =(const Vector4D &srcVector);
    Vector4D operator +(const Vector4D& srcVector) const;
    Vector4D& operator +=(const Vector4D& srcVector);
    Vector4D operator *(float scalarValue) const;
    Vector4D operator -(const Vector4D& srcVector) const;
    Vector4D& operator -=(const Vector4D& srcVector);
    Vector4D operator -() const;
    float length() const;
    Vector4D& normalize();
};
    
    inline std::ostream& operator<< (std::ostream &out, const Vector4D& srcVector)
    {
        out << "(" << srcVector.x << ", " << srcVector.y << ", " << srcVector.z << ", " << srcVector.w << ")";
        return out;
    }
      
}
