#pragma once
#include <GL/glew.h>

enum BlockType {
    AIR,
    STONE,
    GRASS,
    DIRT,
    WATER
};

struct Block {
    BlockType type = AIR;
    GLuint textureID = 0;
};
