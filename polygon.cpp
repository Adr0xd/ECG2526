#include "polygon.h"

namespace egc {
    polygon::polygon() {
    }

    void polygon::addVertex(vec3 vertex) {
        this->vertices.push_back(vertex);

        const int size = this->vertices.size();

        centerPoint.x = 0;
        centerPoint.y = 0;

        for (int i = 0; i < size; i++) {
            centerPoint.x += this->vertices.at(i).x;
            centerPoint.y += this->vertices.at(i).y;
        }
        centerPoint.x /= size;
        centerPoint.y /= size;
        centerPoint.z = 1;
    }

    void polygon::clearVertices() {
        this->vertices.clear();
        centerPoint.x = 0;
        centerPoint.y = 0;
    }

    void polygon::transformVertices() {
        this->transformedVertices = this->vertices;

        const int size = this->vertices.size();

        for (int i = 0; i < size; i++)
            this->transformedVertices.at(i) = this->transformationMatrix * this->transformedVertices.at(i);
    }

    void polygon::draw(SDL_Renderer *renderer) {
        transformVertices();

        if (this->vertices.size() >= 2) {
            SDL_SetRenderDrawColor(renderer, this->polygonColor.r, this->polygonColor.g, this->polygonColor.b,
                                   this->polygonColor.a);

            const int size = this->vertices.size();

            for (int i = 0; i < size; i++) {
                SDL_RenderLine(
                    renderer,
                    this->transformedVertices.at(i % size).x,
                    this->transformedVertices.at(i % size).y,
                    this->transformedVertices.at((i + 1) % size).x,
                    this->transformedVertices.at((i + 1) % size).y
                );
            }
        }
    }
}
