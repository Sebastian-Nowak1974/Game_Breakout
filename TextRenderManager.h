#pragma once

#include <map>
#include <string>
#include <memory>

#include "TextRender.h"

class TextRenderManager
{
public:
	~TextRenderManager();
	static TextRenderManager& getInstance();
	void createFont(const std::string& key, const std::string& fontFileName, int fontSize);
	const TextRender& getFont(const std::string& key) const;
	bool containsFont(const std::string& key) const;
	void clearCache();

private:
	TextRenderManager() {};
	TextRenderManager(TextRenderManager&) = delete;
	void operator=(TextRenderManager&) = delete;
	std::map<std::string, std::unique_ptr<TextRender>> m_glyphsCache;
};
