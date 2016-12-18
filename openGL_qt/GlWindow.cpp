#include "GlWindow.hpp"

void GlWindow::initializeGL()
{
    glewInit();
}

void GlWindow::paintGL()
{
    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}
