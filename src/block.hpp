#pragma once
#include <GL/glew.h>

enum BlockType : uint8_t {
    AIR,
    
    SNOW,
    GRASS,
    DIRT,
    WOOD,
    PLANKS,
    BRICKS,
    STONE,
    IRON, 
    COAL,
    GOLD,
    DIAMOND,
    EMERALD,
    EVIL_STONE,

    WHITE,
    ORANGE,
    MAGENTA,
    LIGHT_BLUE,
    YELLOW,
    LIME,
    GREEN,
    CYAN,
    BLUE,
    PURPLE,
    PINK,
    GRAY,
    LIGHT_GRAY,
    BROWN,
    BLACK,
    RED,

    SAND,
    GRAVEL,

    GLASS,
    LEAVES,

    WATER,
    LAVA
};

struct Block {
    BlockType type = AIR;
    GLuint textureID = 0;
};
