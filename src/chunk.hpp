#pragma once
#include "block.hpp"
#include <vector>
#include <glm/gtc/type_ptr.hpp>


const int CHUNK_SIZE = 16;

class Chunk {
    public:        
        Chunk();
        void render(GLuint shaderProgram);
        Block blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
        Block getBlock(const glm::ivec3& pos) const;
        void setBlock(const glm::ivec3& pos, const Block& block);
        bool isInside(const glm::ivec3& pos) const;
        
    private:
        GLuint VAO, VBO;
        void setupMesh();
};
