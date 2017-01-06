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
    const float ROTATIONAL_SPEED = 0.5f;
    vec3 toRotateAround = glm::cross(viewDirection, UP);
    mat4 rotator = rotate(radians(-mouseDelta.x * ROTATIONAL_SPEED), UP) *
                   rotate(radians(-mouseDelta.y * ROTATIONAL_SPEED), toRotateAround);
    
    viewDirection = mat3(rotator) * viewDirection;

    *oldMousePosition = *newMousePosition;
}
