#include "crosshair.hpp"

const char* crosshairVert = R"(
    #version 330 core
    layout (location = 0) in vec2 aPos;
    uniform mat4 projection;
    void main() {
        gl_Position = projection * vec4(aPos, 0.0, 1.0);
    }
    )";
    
    const char* crosshairFrag = R"(
    #version 330 core
    out vec4 FragColor;
    void main() {
        FragColor = vec4(1.0);
    }
    )";

float crosshairVerts[] = {
    -0.01f,  0.0f,
        0.01f,  0.0f,
        0.0f,  -0.01f,
        0.0f,   0.01f
};

GLuint Crosshair::createCrosshairShader() {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &crosshairVert, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &crosshairFrag, nullptr);
    glCompileShader(fragmentShader);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return program;
}

Crosshair::Crosshair(){
    glGenVertexArrays(1, &crosshairVAO);
    glGenBuffers(1, &crosshairVBO);
    glBindVertexArray(crosshairVAO);
    glBindBuffer(GL_ARRAY_BUFFER, crosshairVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(crosshairVerts), crosshairVerts, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
}

void Crosshair::renderCrosshair(GLuint crosshairShader){
    glUseProgram(crosshairShader);
    glm::mat4 ortho = glm::ortho(-1.f, 1.f, -1.f, 1.f);
    glUniformMatrix4fv(glGetUniformLocation(crosshairShader, "projection"), 1, GL_FALSE, glm::value_ptr(ortho));
    glBindVertexArray(crosshairVAO);
    glDrawArrays(GL_LINES, 0, 4);
}