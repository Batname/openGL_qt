#include "Camera.hpp"

Camera::Camera():
    viewDirection(0.0f, 0.0f, -1.0f),
    UP(0.0f, 1.0f, 0.0f)
{

}

mat4 Camera::getWorldToMatrix() const {
    return glm::lookAt(position, position + viewDirection, UP);
}

void Camera::mouseUpdate(const vec2* newMousePosition) {

    vec2 mouseDelta = *newMousePosition - *oldMousePosition;
    if(length(mouseDelta) > 50.0f) {
        *oldMousePosition = *newMousePosition;
        return;
    }
    viewDirection = mat3(rotate(radians(-mouseDelta.x * 0.5f), UP)) * viewDirection;
    *oldMousePosition = *newMousePosition;
}
