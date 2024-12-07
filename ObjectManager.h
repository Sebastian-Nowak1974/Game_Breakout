#pragma once

#include <map>
#include <string>
#include <memory>

#include "Object.h"

class ObjectManager
{
public:
	static ObjectManager& getInstance();	
	void createObject(const std::string& key, const glm::vec2& size, const glm::vec2& velocity, const
		glm::vec2& position,  Object::BrickColor color = Object::grey);
	Object& getObject(const std::string& key) const ;
	bool containsObject(const std::string& key) const;
	void clearCache();

private:
	ObjectManager() {};
	ObjectManager(ObjectManager&) = delete;
	void operator=(ObjectManager&) = delete;
	std::map<std::string, std::unique_ptr<Object>> m_objectCache;
};