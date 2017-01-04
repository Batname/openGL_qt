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
}

void GlWindow::initializeGL()
{
    glewExperimental = GL_TRUE;
    assert(glewInit() == GLEW_OK && "Failed to inin glew with experemental");
    
    // openGl options
    glEnable(GL_DEPTH_TEST);
    
    installShaders();
    sendDataToOpenGL();
}

void GlWindow::paintGL()
{
    // clear
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    mat4 projectionMatrix = glm::perspective(glm::radians(60.0f), ((float)width()) / height(), 0.1f, 10.0f);
    mat4 projectionTranslationMatrix = glm::translate(projectionMatrix, vec3(0.0f, 0.0f, -3.0f));
    mat4 fullTransformMatrix = glm::rotate(projectionTranslationMatrix, glm::radians(54.0f), vec3(1.0f, 0.0f, 0.0f));
    
    GLint fullTransformMatrixUniformLocation = glGetUniformLocation(ProgramID, "fullTransformMatrix");
    
    glUniformMatrix4fv(
        fullTransformMatrixUniformLocation,
        1,
        GL_FALSE,
        (float*)((vec4 *)(&fullTransformMatrix)) // == &fullTransformMatrix[0][0]
    );

    
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);
}

GlWindow::~GlWindow() {
    glUseProgram(0);
    glDeleteProgram(ProgramID);
}
