#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

class Cube {
public:
    Cube();
    ~Cube();
    
    void init();  
    void draw(GLuint shaderProgram);  
    GLuint getVAO() const;  

private:
    GLuint VAO, VBO;
    static float cubeVertices[];
};

