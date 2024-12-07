#include <stdexcept>
#include <iostream>

#include "TextRenderManager.h"

TextRenderManager::~TextRenderManager()
{    
    clearCache();
}


TextRenderManager& TextRenderManager::getInstance()
{
	static TextRenderManager trm;
	return trm;
}

void TextRenderManager::createFont(const std::string& key, const std::string& fontFileName, int fontSize)
{
    if (containsFont(key))
    {
        auto msg = "Font with key '" + key + "' already exists!";
        throw std::runtime_error(msg.c_str());
    }
	auto ptr =  std::make_unique<TextRender>();
	ptr->loadGlyphs(fontFileName, fontSize);
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    ptr -> setVAO(VAO);
    ptr -> setVBO(VBO);
	m_glyphsCache[key] = std::move(ptr);
}

bool TextRenderManager::containsFont(const std::string& key) const
{
    return m_glyphsCache.count(key);
}

const TextRender& TextRenderManager::getFont(const std::string& key) const
{
    if (!containsFont(key))
    {
        auto msg = "You are trying to access nonexistent font with '" + key + "'!";
        throw std::runtime_error(msg.c_str());
    }
	return *m_glyphsCache.at(key);
}

void TextRenderManager::clearCache()
{
    m_glyphsCache.clear();
}