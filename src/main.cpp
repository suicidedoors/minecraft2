#include "window.hpp"
#include "shader.hpp"
#include "camera.hpp"
#include "constants.hpp"
#include "textures.hpp"
#include "skybox.hpp"
#include "chunk.hpp"

int main() {
    if (!initWindow()) return -1;
    Camera camera;
    glEnable(GL_DEPTH_TEST);

    Chunk chunk;
    GLuint shaderProgram = createShaderProgram();

    Skybox skybox;
    GLuint skyboxShader = createSkyboxShaderProgram();

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
        glUniformMatrix4fv(glGetUniformLocation(skyboxShader, "projection"),  1, GL_FALSE, glm::value_ptr(projection));
        
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

        SDL_GL_SwapWindow(getWindow());
    }
    glDeleteProgram(shaderProgram);
    glDeleteProgram(skyboxShader);

    destroyWindow();
    return 0;
}
