#include <iostream>
#include <stb/stb_image.h>

#include "Texture.h"

Texture::~Texture()
{
	glDeleteTextures(1, &m_textureID);
}

GLuint Texture::getTextureID() const
{
	return m_textureID;
}

bool Texture::loadTexture2D(const std::string& fileName, bool generateMipmaps)
{
	if (isLoaded()) 
		return false;

	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels;
	unsigned char* data;
	data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);

	GLenum format{ 0 };
	if (nrChannels == 4)
		format = GL_RGBA;
	if (nrChannels == 3)
		format = GL_RGB;
	if(nrChannels == 1)
		format = GL_DEPTH_COMPONENT;

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		if(generateMipmaps)
			glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
		return true;
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
		return false;
	}	
}

bool Texture::isLoaded() const
{
	return m_textureID != 0;
}

void Texture::bindTexture(GLuint textureID, GLenum textureUnit) const
{
	if (!isLoaded())
	{
		std::cout << "Trying to access unloaded texture!" << '\n';
		return;
	}
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, textureID);	
}

