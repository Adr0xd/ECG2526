#include <iostream>
#include <SDL3/SDL.h>
#include "clip.h"
#include "polygon.h"
#include "transform.h"
#include <cmath>
#include <unistd.h>

using namespace egc;

// define rectangle vertices
vec3 p1{0.0f, 0.0f, 1.0f};
vec3 p2{0.0f, 0.0f, 1.0f};

//define clipping window
std::vector<vec3> clipWindow;

//define a square
polygon square;

//define the bezier curve control points
std::vector<vec3> curveControlPoints;

//define window dimensions
constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

SDL_Window *window{nullptr};
SDL_Renderer *renderer{nullptr};
SDL_Event currentEvent;

SDL_Color backgroundColor{255, 255, 255, 255};
SDL_Color green{0, 255, 0, 255};
SDL_Color black{0, 0, 0, 255};
SDL_Color clippingWindowColor{0, 128, 0, 255};
SDL_Color lineColor{255, 0, 255, 255};

bool quit{false};

bool iHave4{false};

float mouseX{-1.0f}, mouseY{-1.0f};

float displayScale{1.0f};

bool initWindow() {
    bool success{true};

    //Try to initialize SDL
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL initialization failed: %s\n", SDL_GetError());
        success = false;
    } else {
        //Try to create the window and renderer
        displayScale = SDL_GetDisplayContentScale(1);

        if (!SDL_CreateWindowAndRenderer(
            "SDL Hello World Example",
            static_cast<int>(displayScale * WINDOW_WIDTH),
            static_cast<int>(displayScale * WINDOW_HEIGHT),
            SDL_WINDOW_HIGH_PIXEL_DENSITY,
            &window, &renderer)) {
            SDL_Log("Failed to create window and renderer: %s\n", SDL_GetError());
            success = false;
        } else {
            //Apply global display scaling to renderer
            SDL_SetRenderScale(renderer, displayScale, displayScale);

            //Set background color
            SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b,
                                   backgroundColor.a);

            //Apply background color
            SDL_RenderClear(renderer);
        }
    }

    return success;
}

void destroyWindow() {
    //Destroy renderer
    if (renderer)
        SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    //Destroy window
    if (window)
        SDL_DestroyWindow(window);
    window = nullptr;

    //Quit SDL
    SDL_Quit();
}

void initASquare() {
    square.addVertex(vec3(100.0f, 150.0f, 1.0f));
    square.addVertex(vec3(150.0f, 150.0f, 1.0f));
    square.addVertex(vec3(150.0f, 200.0f, 1.0f));
    square.addVertex(vec3(100.0f, 200.0f, 1.0f));
}

vec3 getPointAt(const float t, const std::vector<vec3> &points) {
    const vec3 p1 = points.at(0);
    const vec3 p2 = points.at(1);
    const vec3 p3 = points.at(2);
    const vec3 p4 = points.at(3);

    return p1 * (1 - t) * (1 - t) * (1 - t) + p2 * 3 * t * (1 - t) * (1 - t) + p3 * 3 * t * t * (1 - t) + p4 * t * t *
           t;
}

vec3 getTangentAt(const float t, const std::vector<vec3> &points) {
    const vec3 p1 = points.at(0);
    const vec3 p2 = points.at(1);
    const vec3 p3 = points.at(2);
    const vec3 p4 = points.at(3);

    return (p2 - p1) * 3.0f * (1.0f - t) * (1.0f - t) +
           (p3 - p2) * 6.0f * (1.0f - t) * t +
           (p4 - p3) * 3.0f * t * t;
}

void drawBulina(SDL_Renderer *renderer, const int cx, const int cy, const int radius) {
    SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b,
                           black.a);
    for (int dy = -radius; dy <= radius; dy++) {
        const int dx = static_cast<int>(sqrt(radius * radius - dy * dy));

        SDL_RenderLine(renderer,
                       cx - dx, cy + dy,
                       cx + dx, cy + dy);
    }
}

int thing = 0;
float t = 0.0f;

int main(int argc, char *argv[]) {
    if (!initWindow()) {
        SDL_Log("Failed to initialize");
        return -1;
    }

    initASquare();

    std::cout << "Click on the screen on the 4 points to make the control points for the curve" << "\n";

    SDL_zero(currentEvent);

    while (!quit) {
        //Handle events on queue
        while (SDL_PollEvent(&currentEvent)) {
            if (currentEvent.type == SDL_EVENT_QUIT) {
                quit = true;
            }

            //Mouse event -> mouse movement
            if (currentEvent.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                if (currentEvent.button.button == SDL_BUTTON_LEFT) {
                    //left button pressed while moving
                    if (!iHave4) {
                        SDL_GetMouseState(&mouseX, &mouseY);
                        mouseX /= displayScale;
                        mouseY /= displayScale;

                        curveControlPoints.push_back(vec3(mouseX, mouseY, 1.0f));

                        if (curveControlPoints.size() > 3) {
                            iHave4 = true;
                        }

                        std::cout << "Point " << curveControlPoints.size() << " added!" << "\n";
                    } else {
                        curveControlPoints.clear();
                        iHave4 = false;
                        thing = 0;
                        t = 0.0f;
                    }
                }
            }

            //Keyboard event
            if (currentEvent.type == SDL_EVENT_KEY_DOWN) {
                switch (currentEvent.key.key) {
                    case SDLK_C:

                        break;
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    default:
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b,
                               backgroundColor.a);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, lineColor.r, lineColor.g, lineColor.b,
                               lineColor.a);

        if (curveControlPoints.size() > 0)
            for (int i = 0; i < curveControlPoints.size(); i++) {
                drawBulina(renderer, curveControlPoints.at(i).x, curveControlPoints.at(i).y, 2);
            }

        switch (thing) {
            case 0:
                square.draw(renderer);
                if (iHave4) thing = 1;
                t = 0.0f;
                break;
            case 1:
                SDL_SetRenderDrawColor(renderer, lineColor.r, lineColor.g, lineColor.b,
                                                       lineColor.a);
                for (float tt = 0; tt < 1.0f; tt += 0.005f) {
                    const vec3 p1 = getPointAt(tt, curveControlPoints);
                    const vec3 p2 = getPointAt(tt + 0.005f, curveControlPoints);
                    SDL_RenderLine(renderer, p1.x, p1.y, p2.x, p2.y);
                }
                SDL_SetRenderDrawColor(renderer, 10, 10, 10,
                                       1);
                SDL_RenderLine(renderer, curveControlPoints.at(0).x, curveControlPoints.at(0).y,
                               curveControlPoints.at(1).x, curveControlPoints.at(1).y);
                SDL_RenderLine(renderer, curveControlPoints.at(2).x, curveControlPoints.at(2).y,
                               curveControlPoints.at(3).x, curveControlPoints.at(3).y);

                if (t <= 1.0f) {
                    const vec3 p = getPointAt(t, curveControlPoints);
                    const vec3 tangent = getTangentAt(t, curveControlPoints);

                    const float angleDeg = atan2(tangent.y, tangent.x) * 180.0f / M_PI;

                    square.transformationMatrix =
                            translate(p.x, p.y) *
                            rotate(angleDeg) *
                            translate(-square.centerPoint.x, -square.centerPoint.y);

                    square.draw(renderer);

                    t += 0.001f;
                } else {
                    square.draw(renderer);
                }

                if (t > 1.0f) {
                    curveControlPoints.clear();
                    iHave4 = false;
                    thing = 0;
                    t = 0.0f;
                }

                break;
            default:
                break;
        }

        if (!iHave4) thing = 0;

        SDL_RenderPresent(renderer);

        SDL_Delay(1);
    }

    destroyWindow();
    return 0;
}
