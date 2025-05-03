#pragma once

#include <GL/glew.h>
#include <unordered_map>
#include "block.hpp"

GLuint loadTexture(const char* path);
extern std::unordered_map<BlockType, GLuint> blockTextures;
void loadAllTextures();