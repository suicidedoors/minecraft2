#pragma once

#include "stb_image.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>


class Skybox{
    public:
        Skybox();
        ~Skybox();
        GLuint getTextureID() const;
        GLuint getVAO() const;

    private:
        GLuint VAO, VBO, cubemapTexture;
        std::vector<std::string> faces;
        void init();
        GLuint loadCubemap(const std::vector<std::string>& faces);
        static float skyboxVertices[];
};