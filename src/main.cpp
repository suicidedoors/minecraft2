#include "window.hpp"
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



int main() {
    if (!initWindow()) return -1;
    Camera camera;
    glEnable(GL_DEPTH_TEST);

    Chunk chunk;
    GLuint shaderProgram = createShaderProgram();

    Skybox skybox;
    GLuint skyboxShader = createSkyboxShaderProgram();

    Crosshair crosshair;
    GLuint crosshairShader = crosshair.createCrosshairShader();


    GLuint tex = loadTexture("../assets/hud.png");

    glUseProgram(shaderProgram);
    glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
    glUseProgram(skyboxShader);
    glUniform1i(glGetUniformLocation(skyboxShader, "skybox"), 0);

    bool running = true;
    SDL_Event event;
    Uint32 lastTime = SDL_GetTicks();
    
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                glm::vec3 origin = camera.getPosition();
                glm::vec3 direction = camera.getFront();
                glm::ivec3 hitPos, hitNormal;
            
                if (event.button.button == SDL_BUTTON_LEFT) {
                    raycastBlockInChunk(chunk, origin, direction, MAX_DISTANCE, hitPos, hitNormal, false, tex);
                } else if (event.button.button == SDL_BUTTON_RIGHT) {
                    raycastBlockInChunk(chunk, origin, direction, MAX_DISTANCE, hitPos, hitNormal, true, tex);
                }
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_BACKSPACE) {
                    glm::vec3 origin = camera.getPosition();
                    glm::vec3 direction = camera.getFront();
                    glm::ivec3 hitPos, hitNormal;
                    raycastBlockInChunk(chunk, origin, direction, MAX_DISTANCE, hitPos, hitNormal, false, tex);
                }
                if (event.key.keysym.sym == SDLK_BACKQUOTE) {
                    glm::vec3 origin = camera.getPosition();
                    glm::vec3 direction = camera.getFront();
                    glm::ivec3 hitPos, hitNormal;
                    raycastBlockInChunk(chunk, origin, direction, MAX_DISTANCE, hitPos, hitNormal, true, tex);
                }
            }
        }

        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        camera.update(event, deltaTime);
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDepthFunc(GL_LEQUAL);
        glUseProgram(skyboxShader);
        glm::mat4 skyboxView = glm::mat4(glm::mat3(view));
        glUniformMatrix4fv(glGetUniformLocation(skyboxShader, "view"), 1, GL_FALSE, glm::value_ptr(skyboxView));
        glUniformMatrix4fv(glGetUniformLocation(skyboxShader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glBindVertexArray(skybox.getVAO());
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.getTextureID());
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDepthFunc(GL_LESS); 

        glUseProgram(shaderProgram);
        glm::mat4 model = glm::mat4(1.0f);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        chunk.render(shaderProgram);

        crosshair.renderCrosshair(crosshairShader);

        SDL_GL_SwapWindow(getWindow());
    }

    glDeleteProgram(shaderProgram);
    glDeleteProgram(skyboxShader);
    glDeleteProgram(crosshairShader);
    destroyWindow();
    return 0;
}
