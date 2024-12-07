#pragma once

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Shader
{
public:
	~Shader();		
	GLuint getShaderID() const;
	bool loadShaderFromFile(const std::string& fileName, GLenum shaderType);
	bool isCompiled() const;
	void deleteShader();

private:
	GLuint m_shaderID{ 0 };
	bool m_isCompiled{ false };
};

