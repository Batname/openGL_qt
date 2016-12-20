#ifndef GlWindow_hpp
#define GlWindow_hpp

#include <iostream>
#include <fstream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <QtOpenGL/qgl.h>

#include "Vertex.h"
#include "ShapeGenerator.hpp"

class GlWindow : public QGLWidget
{
protected:
    void initializeGL();
    void paintGL();
public:
    
private:
    void sendDataToOpenGL();
    void installShaders();
    std::string readShaderCode(const char * filePath);
    
    GLuint ProgramID;
};


#endif /* GlWindow_hpp */
