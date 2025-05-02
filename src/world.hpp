#pragma once
#include "shader.hpp"
#include "constants.hpp"
#include "textures.hpp"
#include "skybox.hpp"
#include "chunk.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "player/raycast.hpp"
#include "player/camera.hpp"
#include "player/crosshair.hpp"


class World{
    public:
        World();
        ~World();
        void render(SDL_Event event, float deltaTime);
        Camera getCamera() const {return camera;}
        Chunk& getChunk() {return chunk;}

    private:
        GLuint shaderProgram;
        GLuint skyboxShader;
        GLuint crosshairShader;
        Camera camera;
        Crosshair crosshair;
        Chunk chunk;
        Skybox skybox;
};