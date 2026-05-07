#include "bresenham.h"

//Detects in which octant a line is situated
int getOctant(const BresenhamLine line) {
    const int dx = static_cast<int>(line.endX - line.startX);
    const int dy = static_cast<int>(line.endY - line.startY); // Note: In SDL, dy > 0 means moving DOWN

    if (dx >= 0 && dy <= 0) {
        return abs(dx) >= abs(dy) ? 1 : 2;
    }
    if (dx < 0 && dy <= 0) {
        return abs(dy) >= abs(dx) ? 3 : 4;
    }
    if (dx < 0 && dy > 0) {
        return abs(dx) >= abs(dy) ? 5 : 6;
    }
    return abs(dy) >= abs(dx) ? 7 : 8;
}

//Draws a new raster line using Bresenham's algorithm
void BresenhamDraw(const BresenhamLine line, SDL_Renderer *renderer) {
    const int dx = abs(line.endX - line.startX);
    const int dy = abs(line.endY - line.startY);
    int x = line.startX;
    int y = line.startY;

    int d, inc1, inc2;
    const int octant = getOctant(line);

    switch (octant) {
        case 1:
            d = 2 * dy - dx;
            inc1 = 2 * dy;
            inc2 = 2 * (dy - dx);
            for (; x <= line.endX; x++) {
                SDL_RenderPoint(renderer, x, y);
                if (d > 0) {
                    y--;
                    d += inc2;
                } else { d += inc1; }
            }
            break;

        case 2:
            d = 2 * dx - dy;
            inc1 = 2 * dx;
            inc2 = 2 * (dx - dy);
            for (; y >= line.endY; y--) {
                SDL_RenderPoint(renderer, x, y);
                if (d > 0) {
                    x++;
                    d += inc2;
                } else { d += inc1; }
            }
            break;

        case 3:
            d = 2 * dx - dy;
            inc1 = 2 * dx;
            inc2 = 2 * (dx - dy);
            for (; y >= line.endY; y--) {
                SDL_RenderPoint(renderer, x, y);
                if (d > 0) {
                    x--;
                    d += inc2;
                } else { d += inc1; }
            }
            break;

        case 4:
            d = 2 * dy - dx;
            inc1 = 2 * dy;
            inc2 = 2 * (dy - dx);
            for (; x >= line.endX; x--) {
                SDL_RenderPoint(renderer, x, y);
                if (d > 0) {
                    y--;
                    d += inc2;
                } else { d += inc1; }
            }
            break;

        case 5:
            d = 2 * dy - dx;
            inc1 = 2 * dy;
            inc2 = 2 * (dy - dx);
            for (; x >= line.endX; x--) {
                SDL_RenderPoint(renderer, x, y);
                if (d > 0) {
                    y++;
                    d += inc2;
                } else { d += inc1; }
            }
            break;

        case 6:
            d = 2 * dx - dy;
            inc1 = 2 * dx;
            inc2 = 2 * (dx - dy);
            for (; y <= line.endY; y++) {
                SDL_RenderPoint(renderer, x, y);
                if (d > 0) {
                    x--;
                    d += inc2;
                } else { d += inc1; }
            }
            break;

        case 7:
            d = 2 * dx - dy;
            inc1 = 2 * dx;
            inc2 = 2 * (dx - dy);
            for (; y <= line.endY; y++) {
                SDL_RenderPoint(renderer, x, y);
                if (d > 0) {
                    x++;
                    d += inc2;
                } else { d += inc1; }
            }
            break;

        case 8:
            d = 2 * dy - dx;
            inc1 = 2 * dy;
            inc2 = 2 * (dy - dx);
            for (; x <= line.endX; x++) {
                SDL_RenderPoint(renderer, x, y);
                if (d > 0) {
                    y++;
                    d += inc2;
                } else { d += inc1; }
            }
            break;
        default:
            break;
    }
}

void renderPoints(SDL_Renderer* renderer, const int x, const int y, const int cx, const int cy) {
    SDL_RenderPoint(renderer, static_cast<float>(cx + x), static_cast<float>(cy + y));
    SDL_RenderPoint(renderer, static_cast<float>(cx + x), static_cast<float>(cy - y));
    SDL_RenderPoint(renderer, static_cast<float>(cx - x), static_cast<float>(cy + y));
    SDL_RenderPoint(renderer, static_cast<float>(cx - x), static_cast<float>(cy - y));
    SDL_RenderPoint(renderer, static_cast<float>(cx + y), static_cast<float>(cy + x));
    SDL_RenderPoint(renderer, static_cast<float>(cx - y), static_cast<float>(cy + x));
    SDL_RenderPoint(renderer, static_cast<float>(cx + y), static_cast<float>(cy - x));
    SDL_RenderPoint(renderer, static_cast<float>(cx - y), static_cast<float>(cy - x));
}

//Draws a new raster circle using Bresenham's algorithm
void BresenhamDraw(const BresenhamCircle circle, SDL_Renderer* renderer) {
    int currentY = circle.radius;

    float d = 0.25f - circle.radius;

    const int end = static_cast<int>(ceil(circle.radius / sqrt(2.0)));

    for (int x = 0; x <= end; x++) {
        renderPoints(renderer, x, currentY, circle.centerX, circle.centerY);

        d += 2 * x + 1;

        if (d > 0) {
            d += 2 - (2 * currentY);
            currentY--;
        }
    }
}


