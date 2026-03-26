#include "vec2.h"
#include "vec3.h"
#include "mat3.h"
#include "mat4.h"
#include "transform.h"

namespace egc {
    mat3 translate(const vec2 translateArray) {
        float src[] = {1, 0, 0, 0, 1, 0, translateArray.x, translateArray.y, 1};
        return mat3(src);
    }

    mat3 translate(float tx, float ty) {
        float src[] = {1, 0, 0, 0, 1, 0, tx, ty, 1};
        return mat3(src);
    }

    mat3 scale(const vec2 scaleArray) {
        float src[] = {scaleArray.x, 0, 0, 0, scaleArray.y, 0, 0, 0, 1};
        return mat3(src);
    }

    mat3 scale(float sx, float sy) {
        float src[] = {sx, 0, 0, 0, sy, 0, 0, 0, 1};
        return mat3(src);
    }

    mat3 rotate(float angle) {
        angle = angle * PI / 180;
        float src[] = {
            (float) cos(angle), (float) sin(angle), 0,
            (float) -sin(angle), (float) cos(angle), 0,
            0, 0, 1
        };
        return mat3(src);
    }

    //transformation matrices in 3D
    mat4 translate(const vec3 translateArray) {
        float src[] = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            translateArray.x, translateArray.y, translateArray.z, 1
        };
        return mat4(src);
    }

    mat4 translate(float tx, float ty, float tz) {
        float src[] = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            tx, ty, tz, 1
        };
        return mat4(src);
    }

    mat4 scale(const vec3 scaleArray) {
        float src[] = {
            scaleArray.x, 0, 0, 0,
            0, scaleArray.y, 0, 0,
            0, 0, scaleArray.z, 0,
            0, 0, 0, 1
        };
        return mat4(src);
    }

    mat4 scale(float sx, float sy, float sz) {
        float src[] = {
            sx, 0, 0, 0,
            0, sy, 0, 0,
            0, 0, sz, 0,
            0, 0, 0, 1
        };
        return mat4(src);
    }

    mat4 rotateX(float angle) {
        angle = angle * PI / 180; // convert to radians
        float src[] = {
            1, 0, 0, 0,
            0, (float) cos(angle), (float) sin(angle), 0,
            0, (float) -sin(angle), (float) cos(angle), 0,
            0, 0, 0, 1
        };
        return mat4(src);
    }

    mat4 rotateY(float angle) {
        angle = angle * PI / 180; // convert to radiansg
        float src[] = {
            (float) cos(angle), 0, (float) -sin(angle), 0,
            0, 1, 0, 0,
            (float) sin(angle), 0, (float) cos(angle), 0,
            0, 0, 0, 1
        };
        return mat4(src);
    }

    mat4 rotateZ(float angle) {
        angle = angle * PI / 180; // convert to radians
        float src[] = {
            (float) cos(angle), (float) sin(angle), 0, 0,
            (float) -sin(angle), (float) cos(angle), 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        };
        return mat4(src);
    }
}
