#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <QtWidgets/qapplication.h>

// custom
#include "GlWindow.hpp"

int main(int argc, char * argv[]) {
    std::cout << "Hello, World!\n";
    
    QApplication app(argc, argv);
    
    GlWindow glWindow;
    glWindow.show();
    
    return app.exec();
}
