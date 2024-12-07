#pragma once

#include <string>
#include <map>
#include <memory>
#include <glad/glad.h>
#include "Shader.h"
#include  "Texture.h"
#include "ShaderProgram.h"

//Singleton class that manages and keeps track of resaurces in the program.
//Shaders, textures and shader programs are created and cached with appropriate keys for later use in the program
class ResaurceManager
{
public:
	// Gets the one and only instance of the manager
	static ResaurceManager& getInstance();	

	void loadVertexShader(const std::string& key, const std::string& fileName);
	const Shader& getVertexShader(const std::string& key) const;
	bool containsVertexShader(const std::string& key) const;

	void loadFragmentShader(const std::string& key, const std::string& fileName);
	const Shader& getFragmentShader(const std::string& key) const;
	bool containsFragmentShader(const std::string& key) const;

	void loadTexture2D(const std::string& key, const std::string& fileName, bool generateMipmaps = true);	
	const Texture& getTexture(const std::string& key) const;
	bool containsTexture(const std::string& key) const;

	void createShaderProgram(const std::string& key);
	ShaderProgram& getShaderProgram(const std::string& key) const;	
	bool containsShaderProgram(const std::string& key) const;	
	
	void clearCache();
	
private:
	ResaurceManager() {};
	ResaurceManager(const ResaurceManager&) = delete;
	void operator=(const ResaurceManager&) = delete;
	std::map<std::string, std::unique_ptr<Shader>> m_vertexShaderCache;
	std::map<std::string, std::unique_ptr<Shader>> m_fragmentShaderCache;
	std::map<std::string, std::unique_ptr<Texture>> m_textureCache;
	std::map<std::string, std::unique_ptr<ShaderProgram>> m_shaderProgramCache;
};
