#include "chunk.hpp"
#include "textures.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <random>

BlockType getRandomBlock(int start, int end) {
    return static_cast<BlockType>(rand() % (end - start) + start); 
}

float cubeVertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

Chunk::Chunk() {
    setupMesh();

    for (int x = 0; x < CHUNK_SIZE; ++x)
        for (int y = 0; y < CHUNK_SIZE; ++y)
            for (int z = 0; z < CHUNK_SIZE; ++z)
                if (y > CHUNK_SIZE / 2){
                    blocks[x][y][z] = Block{AIR, 0};
                } else if (y > CHUNK_SIZE / 2 - 1){
                    blocks[x][y][z] = Block{GRASS, blockTextures[GRASS]};
                } else if (y > CHUNK_SIZE /2 - 3){
                    blocks[x][y][z] = Block{DIRT, blockTextures[DIRT]};
                } else if (y > CHUNK_SIZE /2 - 6){
                    blocks[x][y][z] = Block{DIRT, blockTextures[getRandomBlock(7, 11)]};
                } else { blocks[x][y][z] = Block{STONE, blockTextures[getRandomBlock(11, 14)]};};
}

void Chunk::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Chunk::render(GLuint shaderProgram, const glm::mat4& viewProj) {
    glBindVertexArray(VAO);

    for (int x = 0; x < CHUNK_SIZE; ++x) {
        for (int y = 0; y < CHUNK_SIZE; ++y) {
            for (int z = 0; z < CHUNK_SIZE; ++z) {
                Block& block = blocks[x][y][z];
                if (block.type == AIR) continue;

                bool exposed = false;
                if (blocks[x][y + 1][z].type == AIR) exposed = true; // Top
                if (y == 0 || blocks[x][y - 1][z].type == AIR) exposed = true; // Bottom
                if (x == 0 || blocks[x - 1][y][z].type == AIR) exposed = true; // Left
                if (x == CHUNK_SIZE - 1 || blocks[x + 1][y][z].type == AIR) exposed = true; // Right
                if (z == 0 || blocks[x][y][z - 1].type == AIR) exposed = true; // Front
                if (z == CHUNK_SIZE - 1 || blocks[x][y][z + 1].type == AIR) exposed = true; // Back
                if (!exposed) continue; 

                glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
                glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, block.textureID);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }
    }
}

Block Chunk::getBlock(const glm::ivec3& pos) const {
    return blocks[pos.x][pos.y][pos.z];
}

void Chunk::setBlock(const glm::ivec3& pos, const Block& block) {
    blocks[pos.x][pos.y][pos.z] = block;
}

bool Chunk::isInside(const glm::ivec3& pos) const {
    return pos.x >= 0 && pos.x < CHUNK_SIZE &&
           pos.y >= 0 && pos.y < CHUNK_SIZE &&
           pos.z >= 0 && pos.z < CHUNK_SIZE;
}
