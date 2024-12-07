#pragma once
#include <map>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include "Shader.h"

class ShaderProgram
{
public:
	~ShaderProgram();
	void createProgram();
	bool addShader(const Shader& shader) const;
	void linkProgram();
	bool isLinked() const;
	void useProgram() const;	
	void setLinked(bool b) { m_isLinked = b; }
	
	GLuint getShaderProgramID() const;

	inline void setUniform(const char* name, float value) const 
	{
		glUniform1f(glGetUniformLocation(m_shaderProgramID, name), value);
	}
	inline void setUniform(const char* name, int value) const
	{
		glUniform1i(glGetUniformLocation(m_shaderProgramID, name), value);
	}
	inline void setUniform(const char* name, const glm::vec2& value) const 
	{
		glUniform2f(glGetUniformLocation(m_shaderProgramID, name), value.x, value.y);
	}
	inline void setUniform(const char* name, const glm::vec3& value) const 
	{
		glUniform3f(glGetUniformLocation(m_shaderProgramID, name), value.x, value.y, value.z);
	}
	inline void setUniform(const char* name, const glm::vec4& value) const 
	{
		glUniform4f(glGetUniformLocation(m_shaderProgramID, name), value.x, value.y, value.z, value.w);
	}
	inline void setUniform(const char* name, const glm::mat4& value) const 
	{
		this->useProgram();
		glUniformMatrix4fv(glGetUniformLocation(m_shaderProgramID, name), 1, false, glm::value_ptr(value));
	}
private:
	GLuint m_shaderProgramID{ 0 };
	bool m_isLinked{ false };
	
	
};