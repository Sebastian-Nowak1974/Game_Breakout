#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"ShaderProgram.h"
#include "Texture.h"

//This class defines objects in the game
class Object
{
public:	
	enum BrickColor
	{
		none,
		grey,		
		blue,
		green,
		red,
		yellow
	};
	//Function managing time evolutuion of scene
	void motion(double dt);		
	void draw(ShaderProgram& shaderProgram, const Texture& texture) const;
	void setPosition(const glm::vec2& position);
	void setSize( const glm::vec2& size);
	void setVelocity(const glm::vec2& velocity);
	void setColor(BrickColor color);
	const glm::vec2& getPosition() const;	
	const glm::vec2& getVelocity() const;
	const glm::vec2& getSize() const;
	const glm::vec3& colorToVec3(BrickColor color);

	

private:
	glm::vec2 m_position{ 0 };
	glm::vec2 m_size{ 50.0f };
	glm::vec2 m_velocity{ 0.0f };
	glm::vec3 m_color{ grey};
	
};