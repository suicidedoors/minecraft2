#include "raycast.hpp"
#include "../textures.hpp"


bool raycastBlockInChunk(
    Chunk& chunk,
    const glm::vec3& origin,
    const glm::vec3& direction,
    float maxDist,
    glm::ivec3& hitPos,
    glm::ivec3& hitNormal,
    bool place,
    GLuint tex){

    glm::vec3 rayStep = glm::sign(direction);
    glm::vec3 delta = glm::abs(1.0f / direction);

    glm::ivec3 currentBlock = glm::floor(origin);
    glm::vec3 rayDist;

    for (int axis = 0; axis < 3; axis++) {
        if (rayStep[axis] > 0) {
            rayDist[axis] = (currentBlock[axis] + 1 - origin[axis]) / direction[axis];
        } else {
            rayDist[axis] = (origin[axis] - currentBlock[axis]) / -direction[axis];
        }
    }

    glm::ivec3 step;
    float max = 0.0f;
    int axis = 0;

    for (float t = 0.0f; t < maxDist; ) {
        if (chunk.isInside(currentBlock)) {
            if (chunk.getBlock(currentBlock).type != AIR) {
                hitPos = currentBlock;
                hitNormal = glm::ivec3(0);
                hitNormal[axis] = -step[axis];

                if (place) {
                    glm::ivec3 placePos = hitPos + hitNormal;
                    if (chunk.isInside(placePos)) {
                        chunk.setBlock(placePos, Block{SNOW, tex});
                    }
                } else {
                    chunk.setBlock(hitPos, Block{AIR, 0});
                }
                    return true;
            }
        }

        axis = 0;
        max = rayDist[0];
        if (rayDist[1] < max) { max = rayDist[1]; axis = 1; }
        if (rayDist[2] < max) { max = rayDist[2]; axis = 2; }

        rayDist[axis] += delta[axis];
        step = glm::ivec3(0);
        step[axis] = rayStep[axis];
        currentBlock += step;
        t = max;
        
    }
    

    return false;
}