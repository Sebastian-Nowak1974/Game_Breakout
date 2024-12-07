#pragma once

#include <string>
#include <glad/glad.h>

class Texture
{
public:
	~Texture();
	GLuint getTextureID() const;
	bool loadTexture2D(const std::string& fileName, bool generateMipmaps = true);
	bool isLoaded() const;
	void bindTexture(GLuint textureID, GLenum textureUnit = 0) const;
	
private:
	GLuint m_textureID{ 0 };
};