#pragma once

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

class Crosshair{
    public:
        Crosshair();
        GLuint createCrosshairShader();
        void renderCrosshair(GLuint crosshairShader);
    private:
        GLuint crosshairVAO, crosshairVBO;
};
