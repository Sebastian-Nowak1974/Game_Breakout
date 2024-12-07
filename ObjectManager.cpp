#include <iostream>

#include "ObjectManager.h"

ObjectManager& ObjectManager::getInstance()
{
	static ObjectManager om;
	return om;
}

void ObjectManager::createObject(const std::string& key, const glm::vec2& size, const glm::vec2& velocity, const
	glm::vec2& position, Object::BrickColor color )
{
	if (containsObject(key))
	{
		auto msg = "Object with key '" + key + "' already exists!";
		throw std::runtime_error(msg.c_str());
	}
	Object object;
	object.setPosition(position);	
	object.setSize(size);
	object.setVelocity(velocity);
	object.setColor(color);
	auto ptr = std::make_unique<Object>(object);
	m_objectCache[key] = std::move(ptr);	
}

bool ObjectManager::containsObject(const std::string& key) const
{
	return m_objectCache.count(key) > 0;
}

Object& ObjectManager::getObject(const std::string& key) const
{
	if (!containsObject(key))
	{
		auto msg = "You are trying to access nonexistent object with key '" + key + "'!";
		throw std::runtime_error(msg.c_str());
	}
	return * m_objectCache.at(key);
}

void ObjectManager::clearCache()
{
	m_objectCache.clear();
}