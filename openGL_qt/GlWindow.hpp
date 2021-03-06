#ifndef GlWindow_hpp
#define GlWindow_hpp

#include <iostream>
#include <fstream>
#include <cassert>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>

#include <QtOpenGL/qgl.h>
#include <QtGui/qevent.h>

#include "Vertex.h"
#include "ShapeGenerator.hpp"
#include "Camera.hpp"

class GlWindow : public QGLWidget
{
protected:
    void initializeGL();
    void paintGL();
    void mouseMoveEvent(QMouseEvent*);
    void keyPressEvent(QKeyEvent*);
public:
    ~GlWindow();
    
private:
    void sendDataToOpenGL();
    void installShaders();

    std::string readShaderCode(const char * filePath);
    
    GLuint ProgramID;
    GLuint theBufferID;
    GLuint teapotNumIndices;
    GLuint arrowNumIndices;
    GLuint planeNumIndices;
    GLuint teapotVertexArrayObjectID;
    GLuint arrowVertexArrayObjectID;
    GLuint planeVertexArrayObjectID;
    GLuint arrowIndexDataBuffetOffset;
    GLuint teapotIndexDataBuffetOffset;
    GLuint planeIndexDataBuffetOffset;
    
    GLuint modelToProjectionMatrixLocation;
    GLuint modelToWorldMatrixLocation;

    Camera camera;
};


#endif /* GlWindow_hpp */
