#ifndef GlWindow_hpp
#define GlWindow_hpp

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
    
};


#endif /* GlWindow_hpp */
