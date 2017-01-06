#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

using namespace glm;

class Camera {
public:
    Camera();
    
    mat4 getWorldToMatrix() const;
    void mouseUpdate(const vec2* newMousePosition);
protected:
    
private:
    vec2* oldMousePosition;
    vec3 position;
    vec3 viewDirection;
    const vec3 UP;
};
