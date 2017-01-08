#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

using namespace glm;

class Camera {
public:
    Camera();
    
    mat4 getWorldToMatrix() const;
    void mouseUpdate(const vec2* newMousePosition);
    
    void moveForward();
    void moveBackward();
    void strafeLeft();
    void strafeRight();
    void moveUp();
    void moveDown();
protected:
    
private:
    vec2 oldMousePosition;
    vec3 position;
    vec3 viewDirection;
    vec3 strafeDirection;
    const vec3 UP;
    const float ROTATIONAL_SPEED;
    const float MOVEMENT_SPEED;
};
