#include <fstream>
#include <iostream>
#include <vector>

#include "Shader.h"


Shader::~Shader()
{
    glDeleteShader(m_shaderID);
}
bool Shader::loadShaderFromFile(const std::string& fileName, GLenum shaderType)
{
    std::ifstream file{ fileName };
    if (!file)
    {
        std::cout << "couldn't open file" + fileName + "for reading\n";
        return false;
    }
    std::string line;
    std::vector<std::string> linesFromFile;
    while (std::getline(file, line))
    {
        line += "\n";
        linesFromFile.push_back(line);
    }
    std::vector<const char*> shaderSource;
    for (const auto& line : linesFromFile)
    {
        shaderSource.push_back(line.c_str());
    }
    m_shaderID = glCreateShader(shaderType);

    glShaderSource(m_shaderID, static_cast<GLsizei>(shaderSource.size()), shaderSource.data(), NULL);
    glCompileShader(m_shaderID);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(m_shaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(m_shaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }
    m_isCompiled = true;    
    return true;
    
}

bool Shader::isCompiled() const
{
    return m_isCompiled;
}

GLuint Shader::getShaderID() const 
{ 
    return m_shaderID; 
}