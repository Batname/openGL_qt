#include <iostream>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <QtWidgets/qapplication.h>

// custom
#include "GlWindow.hpp"

int main(int argc, char * argv[]) {    
    QApplication app(argc, argv);
    
    QGLFormat glFormat;
    glFormat.setVersion(3, 2);
    glFormat.setProfile(QGLFormat::CoreProfile);
    
    // Set the default GL format to OpenGL 3.2 Core
    QGLFormat::setDefaultFormat(glFormat);
    
    GlWindow glWindow;
    glWindow.show();
    
    return app.exec();
}
