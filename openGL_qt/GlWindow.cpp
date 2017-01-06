#include "GlWindow.hpp"

using namespace std;
using namespace glm;


std::string GlWindow::readShaderCode(const char * filePath)
{
    ifstream meInput(filePath);
    
    if (!meInput.good()) {
        
    }
    
    return std::string(
       std::istreambuf_iterator<char>(meInput),
       std::istreambuf_iterator<char>()
    );
}

void GlWindow::installShaders()
{
    GLint success;
    GLchar infoLog[521];
    
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    
    const char *adapter[1];
    
    string vShaderCode = readShaderCode("res/shaders/core.vs");
    string fShaderCode = readShaderCode("res/shaders/core.frag");
    
    adapter[0] = vShaderCode.c_str();
    glShaderSource(vertexShaderID, 1, adapter, nullptr);
    adapter[0] = fShaderCode.c_str();
    glShaderSource(fragmentShaderID, 1, adapter, 0);
    
    glCompileShader(vertexShaderID);
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
    }
    
    glCompileShader(fragmentShaderID);
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
        cout << "ERROR::SHADER::FRAFMENT::COMPILATION_FAILED\n" << infoLog << endl;
    }
    
    ProgramID = glCreateProgram();
    glAttachShader(ProgramID, vertexShaderID);
    glAttachShader(ProgramID, fragmentShaderID);
    
    glLinkProgram(ProgramID);
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &success);
    
    if (!success) {
        glGetProgramInfoLog(ProgramID, 512, NULL, infoLog);
        cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
    }
    
    glUseProgram(ProgramID);
    
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
}

void GlWindow::sendDataToOpenGL()
{
    
    GLuint VBO, VAO, EBO;
    
    ShapeData shape = ShapeGenerator::makeCube();
    numIndices = shape.numIndices;
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBufferData(GL_ARRAY_BUFFER, shape.vertexBufferSize(), shape.vertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.indexBufferSize(), shape.indices, GL_STATIC_DRAW);
    
    GLint positionAttrib = glGetAttribLocation(ProgramID, "position"); // 0
    glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(positionAttrib);
    
    GLint colorAttrib = glGetAttribLocation(ProgramID, "color"); // 1
    glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(colorAttrib);
    
    // deallocate memory
    shape.clean();
    
    GLuint transformationMatrixBufferId;
    glGenBuffers(1, &transformationMatrixBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, transformationMatrixBufferId);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(mat4) * 2, 0, GL_DYNAMIC_DRAW);
    
    /*
     2  |f|f|f|f| size = mat4 = 16; offset 0
     3  |f|f|f|f| size = mat4 = 16; offset 4
     4  |f|f|f|f| size = mat4 = 16; offset 8
     5  |f|f|f|f| size = mat4 = 16; offset 12
    */
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (GLvoid*)(sizeof(float) * 0));
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (GLvoid*)(sizeof(float) * 4));
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (GLvoid*)(sizeof(float) * 8));
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (GLvoid*)(sizeof(float) * 12));
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);
    glEnableVertexAttribArray(5);
    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
}

void GlWindow::initializeGL()
{
    setMouseTracking(true);
    glewExperimental = GL_TRUE;
    assert(glewInit() == GLEW_OK && "Failed to inin glew with experemental");
    
    // openGl options
    glEnable(GL_DEPTH_TEST);
    
    installShaders();
    sendDataToOpenGL();
}

void GlWindow::paintGL()
{
    mat4 projectionMatrix = glm::perspective(glm::radians(60.0f), ((float)width()) / height(), 0.1f, 10.0f);
    
    mat4 fullTransforms[] = {
        projectionMatrix * camera.getWorldToMatrix() * glm::translate(vec3(-1.0f, 0.0f, -3.0f)) * glm::rotate(glm::radians(36.0f), vec3(1.0f, 0.0f, 0.0f)),
        projectionMatrix * camera.getWorldToMatrix() * glm::translate(vec3(1.0f, 0.0f, -3.75f)) * glm::rotate(glm::radians(126.0f), vec3(0.0f, 1.0f, 0.0f))
    };
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(fullTransforms), fullTransforms, GL_DYNAMIC_DRAW);
    
    // clear
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
     glDrawElementsInstanced(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0, 2);
}

void GlWindow::mouseMoveEvent(QMouseEvent* e) {
    vec2 vec(vec2(e->x(), e->y()));
    camera.mouseUpdate(&vec);
    repaint();
}

void GlWindow::keyPressEvent(QKeyEvent* e) {
    switch (e->key()) {
    case Qt::Key::Key_W:
        camera.moveForward();
        break;
            
    case Qt::Key::Key_S:
        camera.moveBackward();
        break;
            
    case Qt::Key::Key_A:
        camera.strafeLeft();
        break;

    case Qt::Key::Key_D:
        camera.strafeRight();
        break;

    case Qt::Key::Key_R:
        camera.moveUp();
        break;
            
    case Qt::Key::Key_F:
        camera.moveDown();
        break;
    }
    
    repaint();
    
}

GlWindow::~GlWindow() {
    glUseProgram(0);
    glDeleteProgram(ProgramID);
}
