//
//  All the auxiliary code (window creation/destruction, validation method and others) has been moved to "auxiliary.h" to keep the main file as simple as possible
//
//  Copyright ? 2016 CGIS. All rights reserved.
//

#include <iostream>
#include <SDL3/SDL.h>

#include "auxiliary.h"
#include "rasterization.h"

bool quit { false };

float mouseX { -1.0f }, mouseY { -1.0f };
float rotationAngle { 0.0f };

egc::mat4 viewTransformMatrix;
egc::mat4 cameraMatrix;
egc::mat4 perspectiveMatrix;
egc::mat4 modelMatrix;
egc::Camera myCamera;

// 1. Fill the full window instead of 400x400
egc::vec2 viewportTopLeftCorner { 0.0f, 0.0f };
egc::vec2 viewportDimensions { static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT) };

bool backFaceCulling { true };
bool displayNormals { false };

egc::vec2 zMinMax;
float depthBuffer[WINDOW_WIDTH][WINDOW_HEIGHT];

void handleMouseEvents()
{
	if (currentEvent.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
	{
		if (currentEvent.button.button == SDL_BUTTON_LEFT || currentEvent.button.button == SDL_BUTTON_RIGHT)
		{
			SDL_GetMouseState(&mouseX, &mouseY);
		}
	}
}

void handleKeyboardEvents()
{
	if (currentEvent.type == SDL_EVENT_KEY_DOWN)
	{
		switch (currentEvent.key.key)
		{
		case SDLK_ESCAPE:
			quit = true;
			break;

		case SDLK_A:
			rotationAngle -= 10.0f;
			break;

		case SDLK_D:
			rotationAngle += 10.0f;
			break;

		case SDLK_W:
			cameraZ -= 0.5f;
			break;

		case SDLK_S:
			cameraZ += 0.5f;
			break;

		case SDLK_Z:
			backFaceCulling = true;
			break;

		case SDLK_C:
			backFaceCulling = false;
			break;

		case SDLK_Q:
			displayNormals = true;
			break;

		case SDLK_E:
			displayNormals = false;
			break;

		default:
			break;
		}
	}
}

void drawWireframeTriangle(SDL_Renderer *renderer, const std::vector<egc::vec4> &triangle)
{
	for (int i = 0; i < 3; i++)
		SDL_RenderLine(renderer, triangle.at((i + 1) % 3).x, triangle.at((i + 1) % 3).y, triangle.at(i).x, triangle.at(i).y);
}

void renderMesh(SDL_Renderer *renderer, std::vector<tinyobj::shape_t> shapes)
{
	egc::vec3 normalVector;
	egc::vec4 triangleCenter;

	int vertexId = -1;

	for (size_t i = 0; i < shapes.size(); i++) {
		for (size_t f = 0; f < shapes[i].mesh.indices.size() / 3; f++) {
			std::vector<egc::vec4> triangle;
			std::vector<egc::vec4> triangleColors;

			for (int k = 0; k < 3; k++)
			{
				vertexId = shapes[i].mesh.indices[3 * f + k];
				triangle.push_back(egc::vec4(shapes[i].mesh.positions[3 * vertexId + 0], shapes[i].mesh.positions[3 * vertexId + 1], shapes[i].mesh.positions[3 * vertexId + 2], 1));
				const float colorCoeff = 255 * ((shapes[i].mesh.positions[3 * vertexId + 2] - zMinMax.x) / (zMinMax.y - zMinMax.x));
				triangleColors.push_back(egc::vec4(colorCoeff, colorCoeff, colorCoeff, 255.0f));
			}

			for (int k = 0; k < 3; k++)
				triangle.at(k) = cameraMatrix * modelMatrix * triangle.at(k);

			normalVector = findNormalVectorToTriangle(triangle);
			triangleCenter = findCenterPointOfTriangle(triangle);

			if (!isTriangleVisible(triangle, normalVector) && backFaceCulling)
			{
				continue;
			}

			for (int k = 0; k < 3; k++)
				triangle.at(k) = perspectiveMatrix * triangle.at(k);

			if (clipTriangleInHomegeneousCoordinates(triangle))
			{
				continue;
			}

			for (int k = 0; k < 3; k++)
			{
				egc::perspectiveDivide(triangle.at(k));
				triangle.at(k) = viewTransformMatrix * triangle.at(k);
			}

			egc::rasterizeTriangle(renderer, triangle, triangleColors);

			if (displayNormals)
				displayNormalVectors(normalVector, triangleCenter, renderer, viewTransformMatrix, perspectiveMatrix);
		}
	}
}

int main(int argc, char * argv[]) {
	if (!initWindow())
	{
		SDL_Log("Failed to initialize");
		return -1;
	}

	// 2. Fix Mac Retina scaling: stretch the WINDOW_WIDTH x WINDOW_HEIGHT canvas to full window
	SDL_SetRenderLogicalPresentation(renderer, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_LOGICAL_PRESENTATION_STRETCH);

	myCamera = egc::Camera(egc::vec3(-0.3f, 1.5f, cameraZ), egc::vec3(-0.3f, 1.5f, -10.0f), egc::vec3(0.0f, 1.0f, 0.0f));
	viewTransformMatrix = egc::defineViewTransformMatrix(static_cast<int>(viewportTopLeftCorner.x), static_cast<int>(viewportTopLeftCorner.y), static_cast<int>(viewportDimensions.x), static_cast<int>(viewportDimensions.y));
	cameraMatrix = egc::defineCameraMatrix(myCamera);

	// 3. Match projection aspect ratio to window dimensions
	float aspectRatio = static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT);
	perspectiveMatrix = egc::definePerspectiveProjectionMatrix(45.0f, aspectRatio, -0.1f, -10.0f);

	std::vector<tinyobj::shape_t> shapes = readOBJ("../bunny.obj");
	zMinMax = getZminZmax(shapes.at(0));

	SDL_zero(currentEvent);

	while (!quit) {
		// Process all events
		while (SDL_PollEvent(&currentEvent))
		{
			if (currentEvent.type == SDL_EVENT_QUIT)
			{
				quit = true;
			}

			handleMouseEvents();
			handleKeyboardEvents();
		}

		// 4. Render loop runs every frame
		SDL_SetRenderDrawColor(renderer, 224, 224, 224, 0);
		SDL_RenderClear(renderer);

		modelMatrix = egc::rotateY(rotationAngle) * egc::scale(15.0f, 15.0f, 15.0f);
		myCamera.cameraPosition.z = cameraZ;
		cameraMatrix = egc::defineCameraMatrix(myCamera);

		egc::clearDepthBuffer();

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
		renderMesh(renderer, shapes);

		SDL_RenderPresent(renderer);
	}

	destroyWindow();
	return 0;
}