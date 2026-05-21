#pragma once
#include <SDL3/SDL.h>
#include "vec2.h"
#include "vec4.h"
#include <vector>


namespace egc {

	float f(const vec4 &a, const vec4 &b, const vec4 &p);

	void computeAlphaBetaGamma(const std::vector<egc::vec4>& triangleVertices, vec2 pixel, float& alpha, float& beta, float& gamma);

	void rasterizeTriangle(SDL_Renderer *renderer, const std::vector<egc::vec4> &triangleVertices, const std::vector<egc::vec4> &triangleColors);

	void clearDepthBuffer();
}

