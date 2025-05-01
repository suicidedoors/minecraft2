#pragma once

#include <SDL2/SDL.h>
#include <glm/gtc/type_ptr.hpp>

class Camera {
    public:
        Camera();
        void update(SDL_Event& event, float deltaTime);

        glm::mat4 getViewMatrix() const{return glm::lookAt(position, position + front, up);}
        glm::vec3 getPosition() const {return position;}
        glm::vec3 getFront() const { return front;}

    private:
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;
        float speed;
        float yaw;
        float pitch;
};

