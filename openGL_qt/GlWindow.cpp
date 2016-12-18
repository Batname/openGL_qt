#include "GlWindow.hpp"

using namespace std;

std::string GlWindow::readShaderCode(const char * filePath)
{
    ifstream meInput(filePath);
    
    if (!meInput.good()) {
        exit(EXIT_FAILURE);
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
    GLfloat verts[] = {
        +0.0f, +1.0f,   +1.0f, +0.0f, +0.0f,
        +1.0f, -1.0f,   +0.0f, +1.0f, +0.0f,
        -1.0f, -1.0f,   +0.0f, +0.0f, +1.0f
    };
    
    GLuint indices[] = {
        0, 1, 2
    };
    
    GLuint VBO, VAO, EBO;
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    GLint positionAttrib = glGetAttribLocation(ProgramID, "position"); // 0
    glVertexAttribPointer(positionAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(positionAttrib);
    
    GLint colorAttrib = glGetAttribLocation(ProgramID, "color"); // 0
    glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(colorAttrib);
}

void GlWindow::initializeGL()
{
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        cout << "Failed to inin glew with experemental"  << endl;
    }
    
    installShaders();
    sendDataToOpenGL();
}

void GlWindow::paintGL()
{
    // clear
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}

