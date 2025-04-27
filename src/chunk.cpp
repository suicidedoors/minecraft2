#include "chunk.hpp"
#include "textures.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    GLuint stoneTex = loadTexture("../assets/stone.png");
    GLuint dirtTex = loadTexture("../assets/dirt.png");
    GLuint grassTex = loadTexture("../assets/grass.png");

    for (int x = 0; x < CHUNK_SIZE; ++x)
        for (int y = 0; y < CHUNK_SIZE; ++y)
            for (int z = 0; z < CHUNK_SIZE; ++z)
                if (y > CHUNK_SIZE / 2){
                    blocks[x][y][z] = Block{AIR, 0};
                } else if (y > CHUNK_SIZE / 2 - 1){
                    blocks[x][y][z] = Block{GRASS, grassTex};
                } else if (y > CHUNK_SIZE /2 - 3){
                    blocks[x][y][z] = Block{DIRT, dirtTex};
                } else { blocks[x][y][z] = Block{STONE, stoneTex};};
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

void Chunk::render(GLuint shaderProgram) {
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
