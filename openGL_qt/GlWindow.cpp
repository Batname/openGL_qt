#include "GlWindow.hpp"

using namespace std;
using namespace glm;

//const uint NUM_VERTICES_PER_TRI = 3;
const uint NUM_FLOATS_PER_VERTICE = 9;
const uint VERTEX_BYTE_SIZE = NUM_FLOATS_PER_VERTICE * sizeof(float);

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
    ShapeData cube = ShapeGenerator::makeCube();
    ShapeData arrow  = ShapeGenerator::makeArrow();

    glGenBuffers(1, &theBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, theBufferID);
    glBufferData(GL_ARRAY_BUFFER,
                 cube.vertexBufferSize() + cube.indexBufferSize() +
                 arrow.vertexBufferSize() + arrow.indexBufferSize(),
    0, GL_STATIC_DRAW);
    
    GLsizeiptr currentOffset = 0;
    glBufferSubData(GL_ARRAY_BUFFER, currentOffset, cube.vertexBufferSize(), cube.vertices);
    currentOffset += cube.vertexBufferSize();
    glBufferSubData(GL_ARRAY_BUFFER, currentOffset, cube.indexBufferSize(), cube.indices);
    currentOffset += cube.indexBufferSize();
    glBufferSubData(GL_ARRAY_BUFFER, currentOffset, arrow.vertexBufferSize(), arrow.vertices);
    currentOffset += arrow.vertexBufferSize();
    glBufferSubData(GL_ARRAY_BUFFER, currentOffset, arrow.indexBufferSize(), arrow.indices);
    
    cubeNumIndices = cube.numIndices;
    arrowNumIndices = arrow.numIndices;

    glGenVertexArrays(1, &cubeVertexArrayObjectID);
    glGenVertexArrays(1, &arrowVertexArrayObjectID);

    glBindVertexArray(cubeVertexArrayObjectID);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, theBufferID);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (char*)(3 * sizeof(GLfloat)));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theBufferID);
    
    glBindVertexArray(arrowVertexArrayObjectID);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, theBufferID);
    GLuint arrowByteOffset = cube.vertexBufferSize() + cube.indexBufferSize();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)arrowByteOffset);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(arrowByteOffset + 3 * sizeof(float)));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theBufferID);

    cubeIndexDataBuffetOffset = cube.vertexBufferSize();
    arrowIndexDataBuffetOffset = arrowByteOffset + arrow.vertexBufferSize();
    
    // deallocate memory
    cube.clean();
    arrow.clean();
}

void GlWindow::initializeGL()
{
    setMouseTracking(true);
    glewExperimental = GL_TRUE;
    assert(glewInit() == GLEW_OK && "Failed to inin glew with experemental");
    
    // openGl options
    glEnable(GL_DEPTH_TEST);
    
    sendDataToOpenGL();
    installShaders();
    
    fullTransformMatrixLocation = glGetUniformLocation(ProgramID, "fullTransformMatrix");
}

void GlWindow::paintGL()
{
    // clear
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    mat4 fullTransformMatrix;
    mat4 viewToProjecitonMatrix = glm::perspective(glm::radians(60.0f), ((float)width()) / height(), 0.1f, 10.0f);
    mat4 worldToViewMatrix = camera.getWorldToMatrix();
    mat4 worldToProjectionMatrix = viewToProjecitonMatrix * worldToViewMatrix;
    
    /* ----- Cubes ----- */
    glBindVertexArray(cubeVertexArrayObjectID);
    mat4 cube1ModelToWorldMatrix =
        glm::translate(vec3(-2.0f, 0.0f, -3.0f)) *
        glm::rotate(glm::radians(36.0f), vec3(1.0f, 0.0f, 0.0f));
    
    fullTransformMatrix = worldToProjectionMatrix * cube1ModelToWorldMatrix;
    glUniformMatrix4fv(fullTransformMatrixLocation, 1, GL_FALSE, (float*)((vec4 *)(&fullTransformMatrix)));
    glDrawElements(GL_TRIANGLES, cubeNumIndices, GL_UNSIGNED_SHORT, (void*)cubeIndexDataBuffetOffset);
    
    mat4 cube2ModelToWorldMatrix =
        glm::translate(vec3(2.0f, 0.0f, -3.75f)) *
        glm::rotate(glm::radians(126.0f), vec3(0.0f, 1.0f, 0.0f));
    fullTransformMatrix = worldToProjectionMatrix * cube2ModelToWorldMatrix;
    glUniformMatrix4fv(fullTransformMatrixLocation, 1, GL_FALSE, (float*)((vec4 *)(&fullTransformMatrix)));
    glDrawElements(GL_TRIANGLES, cubeNumIndices, GL_UNSIGNED_SHORT, (void*)cubeIndexDataBuffetOffset);


    /* ----- Arrow ----- */
    glBindVertexArray(arrowVertexArrayObjectID);
    mat4 arrowModelToWorldMatrix = glm::translate(vec3(0.0f, 0.0f, -3.0f));
    fullTransformMatrix = worldToProjectionMatrix * arrowModelToWorldMatrix;

    glUniformMatrix4fv(fullTransformMatrixLocation,1,GL_FALSE,&fullTransformMatrix[0][0]);
    glDrawElements(GL_TRIANGLES, arrowNumIndices, GL_UNSIGNED_SHORT, (void*)arrowIndexDataBuffetOffset);
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
    glDeleteBuffers(1, &theBufferID);
    
    glUseProgram(0);
    glDeleteProgram(ProgramID);
}
