#include <stdexcept>
#include <iostream>
#include "ResaurceManager.h"

ResaurceManager& ResaurceManager::getInstance()
{
	static ResaurceManager rm;
	return rm;
}

void ResaurceManager::loadVertexShader(const std::string& key, const std::string& fileName)
{
	if (containsVertexShader(key))
	{
		auto msg = "Vertex shader with key '" + key + "' already exists!";
		throw std::runtime_error(msg.c_str());
	}
	auto vertexShader = std::make_unique<Shader>();
	if (!vertexShader->loadShaderFromFile(fileName, GL_VERTEX_SHADER))
	{
		auto msg = "Could not load vertex shader '" + fileName + "'!";
		throw std::runtime_error(msg);
	}
	m_vertexShaderCache[key] = std::move(vertexShader);
}

void ResaurceManager::loadFragmentShader(const std::string& key, const std::string& fileName)
{
	if (containsFragmentShader(key))
	{
		auto msg = "Fragment shader with key '" + key + "' already exists!";
		throw std::runtime_error(msg.c_str());
	}
	auto fragmentShader = std::make_unique<Shader>();
	if (!fragmentShader->loadShaderFromFile(fileName, GL_FRAGMENT_SHADER))
	{
		auto msg = "Could not load fragment shader '" + fileName + "'!";
		throw std::runtime_error(msg);
	}
	m_fragmentShaderCache[key] = std::move(fragmentShader);
}

const Shader& ResaurceManager::getVertexShader(const std::string& key) const
{
	 if (!containsVertexShader(key))
	 {
		 auto msg = "Attempting to get non-existing vertex shader with key '" + key + "'!";
		 throw std::runtime_error(msg.c_str());
	 }
	return *m_vertexShaderCache.at(key);
}

const Shader& ResaurceManager::getFragmentShader(const std::string& key) const
{
	if (!containsFragmentShader(key))
	{
		auto msg = "Attempting to get non-existing fragment shader with key '" + key + "'!";
		throw std::runtime_error(msg.c_str());
	}
	return *m_fragmentShaderCache.at(key);
}

bool ResaurceManager::containsVertexShader(const std::string& key) const
{
	return m_vertexShaderCache.count(key) > 0;
}

bool ResaurceManager::containsFragmentShader(const std::string& key) const
{
	 return m_fragmentShaderCache.count(key) > 0;
}

void ResaurceManager::loadTexture2D(const std::string& key, const std::string& fileName, bool generateMipmaps)
{
	if (containsTexture(key))
	{
		auto msg = "Vertex shader with key '" + key + "' already exists!";
		throw std::runtime_error(msg.c_str());
	}
	auto texture2D = std::make_unique<Texture>();
	if (!texture2D->loadTexture2D(fileName, generateMipmaps))
	{
		auto msg = "Could not load texture from" + fileName + "'!";
		throw std::runtime_error(msg);
	}
	m_textureCache[key] = std::move(texture2D);
}

const Texture& ResaurceManager::getTexture(const std::string& key) const
{
	if (!containsTexture(key))
	{
		auto msg = "Attempting to get non-existing texture with key '" + key + "'!";
		throw std::runtime_error(msg.c_str());
	}
	
	return *m_textureCache.at(key);
}
bool ResaurceManager::containsTexture(const std::string& key) const
{
	return m_textureCache.count(key) > 0;
}

void ResaurceManager::createShaderProgram(const std::string& key)
{	
	if (containsShaderProgram(key))
	{
		auto msg = "Shader program with key '" + key + "' already exists!";
		throw std::runtime_error(msg.c_str());
	}
	auto shaderProgramPtr = std::make_unique<ShaderProgram>();
	shaderProgramPtr->createProgram();
	m_shaderProgramCache[key] = std::move(shaderProgramPtr);
}

bool ResaurceManager::containsShaderProgram(const std::string& key) const
{
	return m_shaderProgramCache.count(key) > 0;
}

 ShaderProgram& ResaurceManager::getShaderProgram(const std::string& key) const
{
	if (!containsShaderProgram(key))
	{
		auto msg = "Attempting to get non-existing shaderProgram with key '" + key + "'!";
		throw std::runtime_error(msg.c_str());
	}
	return *m_shaderProgramCache.at(key);
}

 void ResaurceManager::clearCache()
 {
	 m_vertexShaderCache.clear();
	 m_fragmentShaderCache.clear();
	 m_textureCache.clear();
	 m_shaderProgramCache.clear();
}