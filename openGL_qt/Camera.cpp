#include "Camera.hpp"

Camera::Camera():
    viewDirection(0.008024f, -0.283830f, -0.959020f),
    UP(0.0f, 1.0f, 0.0f),
    ROTATIONAL_SPEED(0.5f),
    MOVEMENT_SPEED(0.5f),
    position(-0.052156, 5.480894, 6.233630)
{
}

mat4 Camera::getWorldToMatrix() const {
    return glm::lookAt(position, position + viewDirection, UP);
}

void Camera::mouseUpdate(const vec2* newMousePosition) {

    vec2 mouseDelta = *newMousePosition - oldMousePosition;
    if(length(mouseDelta) > 50.0f) {
        oldMousePosition = *newMousePosition;
        return;
    }
    
    strafeDirection = glm::cross(viewDirection, UP);
    mat4 rotator = rotate(radians(-mouseDelta.x * ROTATIONAL_SPEED), UP) *
                   rotate(radians(-mouseDelta.y * ROTATIONAL_SPEED), strafeDirection);
    
    viewDirection = mat3(rotator) * viewDirection;

    oldMousePosition = *newMousePosition;
}

void Camera::moveForward() {
    position += MOVEMENT_SPEED * viewDirection;
}

void Camera::moveBackward() {
    position += -MOVEMENT_SPEED * viewDirection;
}

void Camera::strafeLeft() {
    position += -MOVEMENT_SPEED * strafeDirection;
}

void Camera::strafeRight() {
    position += MOVEMENT_SPEED * strafeDirection;
}

void Camera::moveUp() {
    position += MOVEMENT_SPEED * UP;

}

void Camera::moveDown() {
    position += -MOVEMENT_SPEED * UP;
}
