#pragma once
#include "block.hpp"
#include <vector>

const int CHUNK_SIZE = 16;

class Chunk {
    public:        
        Chunk();
        void render(GLuint shaderProgram);

    private:
        Block blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
        GLuint VAO, VBO;
        void setupMesh();
};
