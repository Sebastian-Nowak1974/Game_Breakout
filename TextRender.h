#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "ShaderProgram.h"

struct Glyph
{
	unsigned int textureID; // ID handle of the glyph texture
	glm::ivec2 size;      // Size of glyph
	glm::ivec2 bearing;   // Offset from baseline to left/top of glyph
	unsigned int advance;   // Horizontal offset to advance to next glyph
};
class TextRender
{
public:
	GLuint getVAO() const;
	GLuint getVBO() const;
	void setVAO(GLuint VAO);
	void setVBO(GLuint VBO);
	~TextRender();
	void loadGlyphs(std::string fontFilePath, int fontSize );
	Glyph& getChar(unsigned char c);
	void RenderText(const ShaderProgram& shader, std::string text, float x, float y, float scale, glm::vec3 color) const;
private:
	static constexpr unsigned char glyphNumber{ 128 };
	Glyph m_glyphs[glyphNumber];
	GLuint m_VAO;
	GLuint m_VBO;
};