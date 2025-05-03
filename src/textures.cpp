#include "textures.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLuint loadTexture(const char* path) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, channels;
    unsigned char* data = stbi_load(path, &width, &height, &channels, 0);
    if (data) {
        GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data);
    return textureID;
}

void loadAllTextures() {
    blockTextures[SNOW]      = loadTexture("../assets/blocks/snow.png");
    blockTextures[GRASS]     = loadTexture("../assets/blocks/grass.png");
    blockTextures[DIRT]      = loadTexture("../assets/blocks/dirt.png");
    blockTextures[STONE]     = loadTexture("../assets/blocks/stone.png");
    blockTextures[WOOD]      = loadTexture("../assets/blocks/wood.png");
    blockTextures[PLANKS]    = loadTexture("../assets/blocks/planks.png");
    blockTextures[BRICKS]    = loadTexture("../assets/blocks/bricks.png");
    blockTextures[IRON]      = loadTexture("../assets/blocks/iron.png");
    blockTextures[COAL]      = loadTexture("../assets/blocks/coal.png");
    blockTextures[GOLD]      = loadTexture("../assets/blocks/gold.png");
    blockTextures[DIAMOND]   = loadTexture("../assets/blocks/diamond.png");
    blockTextures[EMERALD]   = loadTexture("../assets/blocks/emerald.png");
    blockTextures[EVIL_STONE] = loadTexture("../assets/blocks/stone.png");
    blockTextures[WHITE]     = loadTexture("../assets/blocks/white.png");
    blockTextures[ORANGE]    = loadTexture("../assets/blocks/orange.png");
    blockTextures[MAGENTA]   = loadTexture("../assets/blocks/magenta.png");
    blockTextures[LIGHT_BLUE]= loadTexture("../assets/blocks/light_blue.png");
    blockTextures[YELLOW]    = loadTexture("../assets/blocks/yellow.png");
    blockTextures[LIME]      = loadTexture("../assets/blocks/lime.png");
    blockTextures[GREEN]     = loadTexture("../assets/blocks/green.png");
    blockTextures[CYAN]      = loadTexture("../assets/blocks/cyan.png");
    blockTextures[BLUE]      = loadTexture("../assets/blocks/blue.png");
    blockTextures[PURPLE]    = loadTexture("../assets/blocks/purple.png");
    blockTextures[PINK]      = loadTexture("../assets/blocks/pink.png");
    blockTextures[GRAY]      = loadTexture("../assets/blocks/gray.png");
    blockTextures[LIGHT_GRAY]= loadTexture("../assets/blocks/light_gray.png");
    blockTextures[BROWN]     = loadTexture("../assets/blocks/brown.png");
    blockTextures[BLACK]     = loadTexture("../assets/blocks/black.png");
    blockTextures[RED]       = loadTexture("../assets/blocks/red.png");
    blockTextures[SAND]      = loadTexture("../assets/blocks/sand.png");
    blockTextures[GRAVEL]    = loadTexture("../assets/blocks/gravel.png");
    blockTextures[GLASS]     = loadTexture("../assets/blocks/glass.png");
    blockTextures[LEAVES]    = loadTexture("../assets/blocks/leaves.png");
    blockTextures[WATER]     = loadTexture("../assets/blocks/water.png");
    blockTextures[LAVA]      = loadTexture("../assets/blocks/lava.png");
}
