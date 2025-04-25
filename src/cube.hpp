#pragma once

#include <GL/glew.h>

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

