//
//  main.cpp
//  SDL_Lab1
//
//  Created by CGIS on 16/02/25.
//  Copyright � 2025 CGIS. All rights reserved.
//

#include <iostream>
#include <SDL3/SDL.h>

//define window dimensions
constexpr int WINDOW_WIDTH{640};
constexpr int WINDOW_HEIGHT{480};

SDL_Window *window{nullptr};
SDL_Renderer *renderer{nullptr};
SDL_Event currentEvent;

SDL_FRect rectangleCoordinates{50, 50, 50, 50};
SDL_Color rectangleColor{0, 0, 0, 255};
SDL_Color backgroundColor{255, 255, 255, 255};

SDL_FRect rect2Coordinates{0, 0, 0, 0};
float rect2X = 0, rect2Y = 0, rect2Width = 0, rect2Height = 0;

Uint8 r = 0, g = 0, b = 0;
Uint8 channelValue = 255;

bool quit{false};

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

int main(int argc, char *argv[]) {
    if (!initWindow()) {
        SDL_Log("Failed to initialize");
        return -1;
    }

    rectangleColor = SDL_Color{0, 0, 255, 255};
    SDL_zero(currentEvent);

    while (!quit) {
        //Handle events on queue
        while (SDL_PollEvent(&currentEvent)) {
            //User requests quit
            if (currentEvent.type == SDL_EVENT_QUIT) {
                quit = true;
            }

            //Mouse event -> pressed button
            if (currentEvent.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                if (currentEvent.button.button == SDL_BUTTON_LEFT) {
                    SDL_GetMouseState(&mouseX, &mouseY);
                    mouseX /= displayScale;
                    mouseY /= displayScale;
                    std::cout << "Left mouse click => " << "x: " << mouseX << ", y: " << mouseY << std::endl;
                    rect2X = mouseX; // new rectangle wants to be created
                    rect2Y = mouseY;
                    rect2Width = 0;
                    rect2Height = 0;
                }
                if (currentEvent.button.button == SDL_BUTTON_RIGHT) {
                    rect2X = 0, rect2Y = 0, rect2Width = 0, rect2Height = 0;
                }
            }

            //Mouse event -> mouse movement
            if (currentEvent.type == SDL_EVENT_MOUSE_MOTION) {
                SDL_MouseButtonFlags mouseButtons = SDL_GetMouseState(nullptr, nullptr);
                if (mouseButtons & SDL_BUTTON_MASK(SDL_BUTTON_LEFT)) {
                    SDL_GetMouseState(&mouseX, &mouseY);
                    mouseX /= displayScale;
                    mouseY /= displayScale;
                    std::cout << "Mouse move while left clicking => " << "x: " << mouseX << ", y: " << mouseY <<
                            std::endl;

                    rect2Width = mouseX - rect2X;
                    rect2Height = mouseY - rect2Y;

                }

                if (mouseButtons & SDL_BUTTON_MASK(SDL_BUTTON_RIGHT)) {
                    SDL_GetMouseState(&mouseX, &mouseY);
                    mouseX /= displayScale;
                    mouseY /= displayScale;
                    std::cout << "Mouse move while right clicking => " << "x: " << mouseX << ", y: " << mouseY <<
                            std::endl;
                }
            }

            //Keyboard event
            if (currentEvent.type == SDL_EVENT_KEY_DOWN) {
                switch (currentEvent.key.key) {
                    case SDLK_R:
                        r = 255;
                        g = 0;
                        b = 0;
                        break;

                    case SDLK_G:
                        r = 0;
                        g = 255;
                        b = 0;
                        break;

                    case SDLK_B:
                        r = 0;
                        g = 0;
                        b = 255;
                        break;

                    case SDLK_UP:
                        if (r != 0 && g != 0) {
                            r++;
                            g++;
                        }
                        if (r != 0) r++;
                        else if (g != 0)g++;
                        else b++;
                        break;

                    case SDLK_DOWN:
                        if (r != 0 && g != 0) {
                            r--;
                            g--;
                        }
                        if (r != 0) r--;
                        else if (g != 0)g--;
                        else b--;
                        break;

                    default:
                        r = g = 255;
                        b = 0;
                        break;
                }
                rectangleColor = SDL_Color{r, g, b, 255};
            }



            SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b,
                                   backgroundColor.a);
            SDL_RenderClear(renderer);


            SDL_SetRenderDrawColor(renderer, rectangleColor.r, rectangleColor.g, rectangleColor.b, rectangleColor.a);
            SDL_RenderFillRect(renderer, &rectangleCoordinates);

            rect2Coordinates = SDL_FRect{rect2X, rect2Y, rect2Width, rect2Height};
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

            SDL_RenderFillRect(renderer, &rect2Coordinates);

            SDL_RenderPresent(renderer);
        }
    }

    destroyWindow();
    return 0;
}
