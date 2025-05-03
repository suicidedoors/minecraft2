#pragma once

#include "../chunk.hpp"
#include "../constants.hpp"
#include <GL/glew.h>

extern std::unordered_map<BlockType, GLuint> blockTextures;

bool raycastBlockInChunk(
    Chunk& chunk,
    const glm::vec3& origin,
    const glm::vec3& direction,
    float maxDist,
    glm::ivec3& hitPos,
    glm::ivec3& hitNormal,
    bool place,
    BlockType picked_block
);