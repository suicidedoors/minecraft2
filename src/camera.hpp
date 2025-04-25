#pragma once

#include <SDL2/SDL.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void initCamera();
void updateCamera(SDL_Event& event, float deltaTime);
glm::mat4 getViewMatrix();
