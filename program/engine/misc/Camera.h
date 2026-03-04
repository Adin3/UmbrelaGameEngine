#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Input.h"

class Camera {
private:
    glm::vec3 front, up;
    float     yaw, pitch;
    float     lastX, lastY;
    bool      firstMouse;

public:
    glm::vec3 position;

    Camera();
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix(float aspect) const;
    void processKeyboard(float deltaTime);
    void processMouse(float xoffset, float yoffset);

};
