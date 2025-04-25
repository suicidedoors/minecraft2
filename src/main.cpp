#include "window.hpp"
#include "shader.hpp"
#include "cube.hpp"
#include "camera.hpp"
#include "constants.hpp"
#include "textures.hpp"
#include "skybox.hpp"

int main() {
    if (!initWindow()) return -1;
    initCamera();
    glEnable(GL_DEPTH_TEST);

    Cube cube;
    cube.init(); 
    GLuint shaderProgram = createShaderProgram();
    GLuint texture = loadTexture("../assets/grass.png");

    GLuint skyboxVAO = createSkyboxVAO();
    std::vector<std::string> faces = {
        "../assets/skybox/right.bmp",
        "../assets/skybox/left.bmp",
        "../assets/skybox/top.bmp",
        "../assets/skybox/bottom.bmp",
        "../assets/skybox/front.bmp",
        "../assets/skybox/back.bmp"
    };
    GLuint cubemapTexture = loadCubemap(faces);
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

        updateCamera(event, deltaTime);
        glm::mat4 view = getViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(60.0f), 
                              (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
        glDepthFunc(GL_LEQUAL);
        glUseProgram(skyboxShader);
        
        glm::mat4 skyboxView = glm::mat4(glm::mat3(view));
        glUniformMatrix4fv(glGetUniformLocation(skyboxShader, "view"), 
                          1, GL_FALSE, glm::value_ptr(skyboxView));
        glUniformMatrix4fv(glGetUniformLocation(skyboxShader, "projection"), 
                          1, GL_FALSE, glm::value_ptr(projection));
        
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDepthFunc(GL_LESS); 

        glUseProgram(shaderProgram);
        glm::mat4 model = glm::mat4(1.0f);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 
                          1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 
                          1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 
                          1, GL_FALSE, glm::value_ptr(projection));

        cube.draw(shaderProgram); 
        SDL_GL_SwapWindow(getWindow());
    }

    glDeleteTextures(1, &texture);
    glDeleteTextures(1, &cubemapTexture);
    glDeleteProgram(shaderProgram);
    glDeleteProgram(skyboxShader);

    destroyWindow();
    return 0;
}
