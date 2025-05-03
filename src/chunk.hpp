#pragma once
#include "block.hpp"
#include <vector>
#include <unordered_map>
#include <glm/gtc/type_ptr.hpp>

const int CHUNK_SIZE = 16;
extern std::unordered_map<BlockType, GLuint> blockTextures;

class Chunk {
    public:        
        Chunk();
        void render(GLuint shaderProgram, const glm::mat4& viewProj);
        Block blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
        Block getBlock(const glm::ivec3& pos) const;
        void setBlock(const glm::ivec3& pos, const Block& block);
        bool isInside(const glm::ivec3& pos) const;

    private:
        GLuint VAO, VBO;
        void setupMesh();
};
