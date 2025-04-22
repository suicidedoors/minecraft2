#include "window.hpp"
#include "shader.hpp"
#include "cube.hpp"
#include "camera.hpp"
#include "constants.hpp"

int main() {
    if (!initWindow()) return -1;
    initCamera();
    GLuint shaderProgram = createShaderProgram();
    GLuint VAO = createCubeVAO();
    GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
    glLinkProgram(shaderProgram);
    glm::mat4 view = getViewMatrix();  

    glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
    bool running = true;
    SDL_Event event;
    Uint32 lastTime = SDL_GetTicks();

    while (running) {
        while (SDL_PollEvent(&event))
            if (event.type == SDL_QUIT) running = false;

        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;
        updateCamera(event, deltaTime);

        view = getViewMatrix();  
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glm::mat4 model = glm::mat4(1.0f);

        glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f);

        GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
        GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
        GLuint projLoc = glGetUniformLocation(shaderProgram, "projection");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glm::mat4 view = getViewMatrix();
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        SDL_GL_SwapWindow(getWindow());
    }

    destroyWindow();
    return 0;
}
