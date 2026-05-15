#include "ShaderProgram.hpp"

//Operator =
Renderer::ShaderProgram& Renderer::ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept{
    glDeleteProgram(programShaderID);
    programShaderID = shaderProgram.programShaderID;
    programShaderID_isCompiled = shaderProgram.programShaderID_isCompiled;

    shaderProgram.programShaderID = 0;
    shaderProgram.programShaderID_isCompiled = false;
    return *this;
}

//consturctor =
Renderer::ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept{
    programShaderID = shaderProgram.programShaderID;
    programShaderID_isCompiled = shaderProgram.programShaderID_isCompiled;

    shaderProgram.programShaderID = 0;
    shaderProgram.programShaderID_isCompiled = false;
}

//CreateShader
bool Renderer::ShaderProgram::createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID)
{
    shaderID = glCreateShader(shaderType);
    const char* code = source.c_str();
    glShaderSource(shaderID, 1, &code, NULL);
    glCompileShader(shaderID);

    GLint succes;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &succes);
    if (!succes) {
        char infoLog[512];
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILED_FAILED\n" << infoLog << "\n";
        return false;
    }
    return true;
}

//CreateProgram (Linked shaders)
Renderer::ShaderProgram::ShaderProgram(const std::string& vertex_shader, const std::string& fragment_shader) {
    //Create vertex shader
    GLuint vertexShaderID;
    if (!(createShader(vertex_shader, GL_VERTEX_SHADER, vertexShaderID))) {
        std::cout << "VERTEX::SHADER::NOT::CREATED\n";
        glDeleteShader(vertexShaderID);
        return;
    }
    //Create fragment shader
    GLuint fragmentShaderID;
    if (!(createShader(fragment_shader, GL_FRAGMENT_SHADER, fragmentShaderID))) {
        std::cout << "FRAGMENT::SHADER::NOT::CREATED\n";
        glDeleteShader(fragmentShaderID);
        return;
    }
    //Link program
    programShaderID = glCreateProgram();
    glAttachShader(programShaderID, vertexShaderID);
    glAttachShader(programShaderID, fragmentShaderID);
    glLinkProgram(programShaderID);

    GLint success;
    glGetProgramiv(programShaderID, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(programShaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << "\n";
        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
    }
    else {
        programShaderID_isCompiled = true;
    }

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
}

//Program shader destructor
Renderer::ShaderProgram::~ShaderProgram(){
    glDeleteProgram(programShaderID);
}

//Use program
void Renderer::ShaderProgram::use() const
{
    glUseProgram(programShaderID);
}

GLuint Renderer::ShaderProgram::getProgramID() const{
    return programShaderID;
}