//
//  projection.cpp
//  Lab8_TODO
//
//  Copyright © 2016 CGIS. All rights reserved.
//

#include "projection.h"
#include "transform.h"
#include <cmath>

namespace egc {
    // Section 3: Viewport transformation matrix
    // mat4 stores data in COLUMN-MAJOR order, so the flat array must be
    // written column-by-column (NOT row-by-row).
    mat4 defineViewTransformMatrix(int startX, int startY, int width, int height) {
        const float nx = static_cast<float>(width);
        const float ny = static_cast<float>(height);

        float srcSMTMatrix[] = {
            nx / 2.0f, 0.0f, 0.0f, 0.0f, // col 0
            0.0f, -ny / 2.0f, 0.0f, 0.0f, // col 1
            0.0f, 0.0f, 1.0f, 0.0f, // col 2
            nx / 2.0f, ny / 2.0f, 0.0f, 1.0f // col 3
        };
        const mat4 smtMatrix(srcSMTMatrix);

        const mat4 translationMatrix = translate(
            static_cast<float>(startX),
            static_cast<float>(startY),
            0.0f);

        return translationMatrix * smtMatrix;
    }

    // Section 4: Camera transformation matrix
    mat4 defineCameraMatrix(Camera mc) {
        // BUG FIX: normalize() returns *this by reference — calling it on a
        // temporary (like the return value of crossProduct) is undefined behaviour.
        // Store every intermediate result in a named variable first.
        vec3 g = mc.cameraTarget - mc.cameraPosition;
        g.normalize(); // normalize in place (safe: g is a named variable)
        vec3 w = -g; // w = -normalize(gaze)

        vec3 u = crossProduct(mc.cameraUp, w);
        u.normalize(); // safe: u is a named variable

        vec3 v = crossProduct(w, u);

        const vec3 &e = mc.cameraPosition;

        float srcCamMatrix[] = {
            u.x, u.y, u.z, 0.0f, // col 0
            v.x, v.y, v.z, 0.0f, // col 1
            w.x, w.y, w.z, 0.0f, // col 2
            -dotProduct(u, e), -dotProduct(v, e), -dotProduct(w, e), 1.0f // col 3
        };

        return mat4(srcCamMatrix);
    }

    // Section 5: Perspective projection matrix
    mat4 definePerspectiveProjectionMatrix(float fov, float aspect, float zNear, float zFar) {
        const float tanHalfFov = tanf(fov * 3.14159265358979f / 180.0f / 2.0f);
        const float n = zNear;
        const float f = zFar;

        const float A = -1.0f / (aspect * tanHalfFov);
        const float B = -1.0f / tanHalfFov;
        const float C = (f + n) / (n - f);
        const float D = 2.0f * f * n / (f - n);

        float srcPerspMatrix[] = {
            A, 0.0f, 0.0f, 0.0f,
            0.0f, B, 0.0f, 0.0f,
            0.0f, 0.0f, C, 1.0f,
            0.0f, 0.0f, D, 0.0f
        };

        return mat4(srcPerspMatrix);
    }

    // Section 5: Perspective divide
    void perspectiveDivide(vec4 &iv) {
        if (iv.w != 0.0f) {
            iv.x /= iv.w;
            iv.y /= iv.w;
            iv.z /= iv.w;
            iv.w = 1.0f;
        }
    }

    // Section 9: Returns true when the point is outside the view frustum.
    bool clipPointInHomogeneousCoordinate(const egc::vec4 &vertex) {
        const float absW = std::abs(vertex.w);
        if (vertex.x < -absW || vertex.x > absW) return true;
        if (vertex.y < -absW || vertex.y > absW) return true;
        if (vertex.z < -absW || vertex.z > absW) return true;
        return false;
    }

     bool clipTriangleInHomegeneousCoordinates(const std::vector<egc::vec4> &triangle)
    {
        for (const auto &vertex : triangle)
            if (clipPointInHomogeneousCoordinate(vertex))
                return true;
        return false;
    }

    // Section 7: n = normalize((B-A) x (C-A))
    egc::vec3 findNormalVectorToTriangle(const std::vector<egc::vec4> &triangle) {
        const vec3 A(triangle[0].x, triangle[0].y, triangle[0].z);
        const vec3 B(triangle[1].x, triangle[1].y, triangle[1].z);
        const vec3 C(triangle[2].x, triangle[2].y, triangle[2].z);
        vec3 n = crossProduct(B - A, C - A);
        n.normalize();
        return n;
    }

    // Section 7: Average of the three vertex positions.
    egc::vec4 findCenterPointOfTriangle(const std::vector<egc::vec4> &triangle) {
        vec4 center;
        center.x = (triangle[0].x + triangle[1].x + triangle[2].x) / 3.0f;
        center.y = (triangle[0].y + triangle[1].y + triangle[2].y) / 3.0f;
        center.z = (triangle[0].z + triangle[1].z + triangle[2].z) / 3.0f;
        center.w = 1.0f;
        return center;
    }

    // Section 8: Back-face culling — in camera space the eye is at the origin.
    bool isTriangleVisible(const std::vector<vec4> &triangle, const vec3 &normalVector) {
        const vec3 A(triangle[0].x, triangle[0].y, triangle[0].z);
        const vec3 v = vec3(0.0f, 0.0f, 0.0f) - A;
        return dotProduct(v, normalVector) > 0.0f;
    }

    // Section 7: Draw a short line from triangleCenter along normalVector.
    void displayNormalVectors(vec3 &normalVector, egc::vec4 &triangleCenter,
                              SDL_Renderer *renderer,
                              egc::mat4 viewTransformMatrix,
                              egc::mat4 perspectiveMatrix) {
        const float offset = 0.1f;

        vec4 secondPoint;
        secondPoint.x = triangleCenter.x + normalVector.x * offset;
        secondPoint.y = triangleCenter.y + normalVector.y * offset;
        secondPoint.z = triangleCenter.z + normalVector.z * offset;
        secondPoint.w = 1.0f;

        vec4 p1 = perspectiveMatrix * triangleCenter;
        perspectiveDivide(p1);
        p1 = viewTransformMatrix * p1;

        vec4 p2 = perspectiveMatrix * secondPoint;
        perspectiveDivide(p2);
        p2 = viewTransformMatrix * p2;

        SDL_RenderLine(renderer, p1.x, p1.y, p2.x, p2.y);
    }
} // namespace egc
