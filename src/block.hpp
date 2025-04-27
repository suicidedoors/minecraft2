#pragma once
#include <GL/glew.h>

enum BlockType : uint8_t {
    AIR,
    STONE,
    GRASS,
    DIRT,
    WATER
};

struct Block {
    BlockType type;
    GLuint textureID;
};
