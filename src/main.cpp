#include "window.hpp"
#include "world.hpp"

int main() {
    if (!initWindow()) return -1;

    GLuint tex = loadTexture("../assets/hud.png");

    World world;

    bool running = true;
    SDL_Event event;
    Uint32 lastTime = SDL_GetTicks();
    
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                glm::vec3 origin = world.getCamera().getPosition();
                glm::vec3 direction = world.getCamera().getFront();
                glm::ivec3 hitPos, hitNormal;
                
                bool mode = (event.button.button == SDL_BUTTON_LEFT);
                raycastBlockInChunk(world.getChunk(), origin, direction, MAX_DISTANCE, hitPos, hitNormal, mode, tex);
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_BACKSPACE || event.key.keysym.sym == SDLK_BACKQUOTE) {
                    glm::vec3 origin = world.getCamera().getPosition();
                    glm::vec3 direction = world.getCamera().getFront();
                    glm::ivec3 hitPos, hitNormal;
                    bool mode = (event.key.keysym.sym == SDLK_BACKQUOTE);
                    raycastBlockInChunk(world.getChunk(), origin, direction, MAX_DISTANCE, hitPos, hitNormal, mode, tex);
                }
            }
        }

        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        world.render(event, deltaTime);

        SDL_GL_SwapWindow(getWindow());
    }

    destroyWindow();
    return 0;
}
