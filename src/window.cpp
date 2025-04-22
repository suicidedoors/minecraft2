#include "window.hpp"
#include "constants.hpp"
#include <GL/glew.h>

SDL_Window* window = nullptr;

bool initWindow() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) return false;

    window = SDL_CreateWindow(
        "Minecraft2",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN
    );

    if (!window) return false;

    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (!context) return false;

    if (glewInit() != GLEW_OK) return false;

    return true;
}

SDL_Window* getWindow() {
    return window;
}

void destroyWindow() {
    SDL_GL_DeleteContext(SDL_GL_GetCurrentContext());
    SDL_DestroyWindow(window);
    SDL_Quit();
}
