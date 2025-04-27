#include "camera.hpp"
#include "constants.hpp"

Camera::Camera()
    : position(STARTING_CAMERA_POSITION),
    front(0.0f, 0.0f, -1.0f),
    up(0.0f, 1.0f, 0.0f), 
    speed(4.0f), 
    yaw(-90.0f), 
    pitch(0.0f) {
    SDL_SetRelativeMouseMode(SDL_TRUE);
}

void Camera::update(SDL_Event& event, float deltaTime) {
    const Uint8* keystate = SDL_GetKeyboardState(nullptr);
    float velocity = speed * deltaTime;

    // keyboard input
    if (keystate[SDL_SCANCODE_W]) position += front * velocity;
    if (keystate[SDL_SCANCODE_S]) position -= front * velocity;
    if (keystate[SDL_SCANCODE_A]) position -= glm::normalize(glm::cross(front, up)) * velocity;
    if (keystate[SDL_SCANCODE_D]) position += glm::normalize(glm::cross(front, up)) * velocity;
    if (keystate[SDL_SCANCODE_SPACE]) position += up * velocity;
    if (keystate[SDL_SCANCODE_LSHIFT]) position -= up * velocity;

    if (keystate[SDL_SCANCODE_UP]) pitch -= ARROW_SENSITIVITY; 
    if (keystate[SDL_SCANCODE_LEFT]) yaw -= ARROW_SENSITIVITY; 
    if (keystate[SDL_SCANCODE_RIGHT]) yaw += ARROW_SENSITIVITY; 
    if (keystate[SDL_SCANCODE_DOWN]) pitch += ARROW_SENSITIVITY; 

    // mouse input
    int xRel, yRel;
    SDL_GetRelativeMouseState(&xRel, &yRel);

    float xOffset = xRel * MOUSE_SENSITIVITY;
    float yOffset = yRel * MOUSE_SENSITIVITY;
    
    yaw += xOffset;
    pitch -= yOffset;
    
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;
    
    glm::vec3 frontDirection;
    frontDirection.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    frontDirection.y = sin(glm::radians(pitch));
    frontDirection.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(frontDirection);    
}

glm::mat4 Camera::getViewMatrix() const{
    return glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::getPosition() const {
    return position;
}
