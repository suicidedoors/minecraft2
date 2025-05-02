#include "world.hpp"

World::World(){
    glEnable(GL_DEPTH_TEST);

    shaderProgram = createShaderProgram();
    skyboxShader = createSkyboxShaderProgram();
    crosshairShader = crosshair.createCrosshairShader();

    glUseProgram(shaderProgram);
    glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
    glUseProgram(skyboxShader);
    glUniform1i(glGetUniformLocation(skyboxShader, "skybox"), 0);
}

World::~World(){
    glDeleteProgram(shaderProgram);
    glDeleteProgram(skyboxShader);
    glDeleteProgram(crosshairShader);
}


void World::render(SDL_Event event, float deltaTime){
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
}

