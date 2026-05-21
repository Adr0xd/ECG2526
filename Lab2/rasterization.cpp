#include "rasterization.h"
#include "vec4.h"
#include "globalVars.h"
#include <limits>

namespace egc {
    float f(const vec4 &a, const vec4 &b, const vec4 &p) {
        return (a.y - b.y) * p.x + (b.x - a.x) * p.y + a.x * b.y - a.y * b.x;
    }

    void computeAlphaBetaGamma(const std::vector<egc::vec4> &triangleVertices, vec2 pixel, float &alpha, float &beta,
                               float &gamma) {
        //TO DO - Compute alfa, beta and gamma => we use the function's input parameters as the return mechanism
        //Store the final results in the input parameters

        //					B						C                         P
        alpha = f(triangleVertices[1], triangleVertices[2], vec4(pixel.x, pixel.y, 0.0f, 1.0f)) /
                f(triangleVertices[1], triangleVertices[2], triangleVertices[0]);
        //                  B                       C                         A

        //					C						A                         P
        beta = f(triangleVertices[2], triangleVertices[0], vec4(pixel.x, pixel.y, 0.0f, 1.0f)) /
               f(triangleVertices[2], triangleVertices[0], triangleVertices[1]);
        //                  C                       A                         B

        //					B						C                         P
        gamma = f(triangleVertices[0], triangleVertices[1], vec4(pixel.x, pixel.y, 0.0f, 1.0f)) /
                f(triangleVertices[0], triangleVertices[1], triangleVertices[2]);
        //                  A                       B                         C
    }

    void rasterizeTriangle(SDL_Renderer *renderer, const std::vector<egc::vec4> &triangleVertices,
                           const std::vector<egc::vec4> &triangleColors) {
        //TO DO - Implement the triangle rasterization algorithm

        float x_min = triangleVertices[0].x;
        float y_min = triangleVertices[0].y;
        float x_max = triangleVertices[0].x;
        float y_max = triangleVertices[0].y;

        for (int i = 1; i < triangleVertices.size(); i++) {
            x_min = std::min(x_min, triangleVertices[i].x);
            y_min = std::min(y_min, triangleVertices[i].y);
            x_max = std::max(x_max, triangleVertices[i].x);
            y_max = std::max(y_max, triangleVertices[i].y);
        }

        for (int x = x_min; x < x_max; x++) {
            for (int y = y_min; y < y_max; y++) {
                float alpha = 0.0f;
                float beta = 0.0f;
                float gamma = 0.0f;

                computeAlphaBetaGamma(triangleVertices, vec2(x, y), alpha, beta, gamma);


                if (alpha >= 0.0f && alpha <= 1.0f &&
                    beta >= 0.0f && beta <= 1.0f &&
                    gamma >= 0.0f && gamma <= 1.0f) {
                    const float z = triangleVertices[0].z * alpha +
                              triangleVertices[1].z * beta +
                              triangleVertices[2].z * gamma;

                    if (z > depthBuffer[x][y]) {
                        depthBuffer[x][y] = z;

                        const vec4 color = triangleColors[0] * alpha +
                                           triangleColors[1] * beta +
                                           triangleColors[2] * gamma;

                        SDL_SetRenderDrawColor(renderer, color.x, color.y, color.z, color.w);
                        SDL_RenderPoint(renderer, x, y);
                    }
                }
            }
        }
    }

    void clearDepthBuffer() {
        //TODO - Implement clearing the depth buffer
        //depthBuffer is declared as an external global variable in main.cpp and thus can be accessed here as depthBuffer[i][j]
        for (int x = 0; x < WINDOW_WIDTH; x++) {
            for (int y = 0; y < WINDOW_HEIGHT; y++) {
                depthBuffer[x][y] = -1.01f;
            }
        }
    }
}
