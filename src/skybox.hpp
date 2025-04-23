#pragma once

#include "stb_image.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

GLuint loadCubemap(const std::vector<std::string>& faces);
GLuint createSkyboxVAO();
void renderSkybox(GLuint skyboxVAO, GLuint skyboxShader, GLuint cubemapTexture, const glm::mat4& view, const glm::mat4& projection);

