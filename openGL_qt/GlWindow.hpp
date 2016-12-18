#ifndef GlWindow_hpp
#define GlWindow_hpp

#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include <QtOpenGL/qgl.h>

class GlWindow : public QGLWidget
{
    
protected:
    void initializeGL();
    void paintGL();
public:
    
private:
    void sendDataToOpenGL();
    void installShaders();
    
    GLuint ProgramID;
};


#endif /* GlWindow_hpp */
