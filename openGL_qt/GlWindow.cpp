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
}

void GlWindow::sendDataToOpenGL()
{
    
    GLuint VBO, VAO, EBO;
    
    ShapeData tri = ShapeGenerator::makeTrianle();
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBufferData(GL_ARRAY_BUFFER, tri.vertexBufferSize(), tri.vertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, tri.indexBufferSize(), tri.indices, GL_STATIC_DRAW);
    
    GLint positionAttrib = glGetAttribLocation(ProgramID, "position"); // 0
    glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(positionAttrib);
    
    GLint colorAttrib = glGetAttribLocation(ProgramID, "color"); // 1
    glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(colorAttrib);
    
    // deallocate memory
    tri.clean();
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
    
    // send uniform data
    GLint dominatingColorLocation = glGetUniformLocation(ProgramID, "dominatingColor");
    GLint yFlipUniformLocation = glGetUniformLocation(ProgramID, "yFlip");
    
    vec3 dominatingColor(1.0f, 0.0f, 0.0f);
    glUniform3fv(dominatingColorLocation, 1, ((float*)(&dominatingColor) + 0) );
    glUniform1f(yFlipUniformLocation, 1.0f);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    dominatingColor.r = 0.0f;
    dominatingColor.b = 1.0f;
    glUniform3fv(dominatingColorLocation, 1, ((float*)(&dominatingColor) + 0) );
    glUniform1f(yFlipUniformLocation, -1.0f);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

