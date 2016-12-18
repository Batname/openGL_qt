#ifndef GlWindow_hpp
#define GlWindow_hpp

#include <iostream>
#include <fstream>

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
    std::string readShaderCode(const char * filePath);
    
    GLuint ProgramID;
};


#endif /* GlWindow_hpp */
