#include <iostream>

#include "ShaderProgram.h"

ShaderProgram::~ShaderProgram()
{	
	glDeleteProgram(m_shaderProgramID);
}

void ShaderProgram::createProgram()
{
	m_shaderProgramID = glCreateProgram();
}

bool ShaderProgram::addShader(const Shader& shader) const
{
	if (!shader.isCompiled())
		return false;
	
	glAttachShader(m_shaderProgramID, shader.getShaderID());
	return true;
}

void ShaderProgram::linkProgram() 
{
	if (m_isLinked)
		return;
	
	glLinkProgram(m_shaderProgramID);
	int success;
	char infoLog[512];
	glGetProgramiv(m_shaderProgramID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_shaderProgramID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		return;
	}
	m_isLinked = true;;
}

void ShaderProgram::useProgram() const
{
	if (!m_isLinked)
		return;

	glUseProgram(m_shaderProgramID);
}

GLuint ShaderProgram::getShaderProgramID() const
{
	return m_shaderProgramID;
}

bool ShaderProgram::isLinked() const
{
	return  m_isLinked;
}

