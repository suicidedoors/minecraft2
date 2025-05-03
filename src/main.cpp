#include "window.hpp"
#include "world.hpp"

std::unordered_map<BlockType, GLuint> blockTextures;

int main() {
    stbi_set_flip_vertically_on_load(true);
    if (!initWindow()) return -1;
    std::unordered_map<BlockType, GLuint> blockTextures;
    loadAllTextures();

    World world;

    BlockType picked_block = SNOW;

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
                
                bool mode = (event.button.button == SDL_BUTTON_RIGHT);
                raycastBlockInChunk(world.getChunk(), origin, direction, MAX_DISTANCE, hitPos, hitNormal, mode, picked_block);
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_BACKSPACE || event.key.keysym.sym == SDLK_BACKQUOTE) {
                    glm::vec3 origin = world.getCamera().getPosition();
                    glm::vec3 direction = world.getCamera().getFront();
                    glm::ivec3 hitPos, hitNormal;
                    bool mode = (event.key.keysym.sym == SDLK_BACKQUOTE);
                    raycastBlockInChunk(world.getChunk(), origin, direction, MAX_DISTANCE, hitPos, hitNormal, mode, picked_block);
                }
                switch (event.key.keysym.sym) {
                    case SDLK_1: picked_block = SNOW; break;
                    case SDLK_2: picked_block = GRASS; break;
                    case SDLK_3: picked_block = WATER; break;
                    case SDLK_4: picked_block = GLASS; break;
                    case SDLK_5: picked_block = SAND; break;
                    case SDLK_6: picked_block = GRAVEL; break;
                    case SDLK_7: picked_block = PLANKS; break;
                    case SDLK_8: picked_block = BRICKS; break;
                    case SDLK_9: picked_block = WOOD; break;
                    case SDLK_0: picked_block = LEAVES; break;
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
