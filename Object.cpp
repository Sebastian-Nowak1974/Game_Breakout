#include <array>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Object.h"
#include "ShaderProgram.h"
#include "ResaurceManager.h"
#include "GameInputData.h"
#include <iostream>


void Object::setPosition(const glm::vec2& position) { m_position = position; }

void Object::setSize( const glm::vec2& size) { m_size = size; }
void Object::setVelocity(const glm::vec2& velocity) { m_velocity = velocity; }
void Object::setColor(BrickColor color) { m_color = colorToVec3(color); }
const glm::vec2& Object::getPosition() const { return m_position; }
const glm::vec2& Object::getVelocity() const { return m_velocity; }
const glm::vec2& Object::getSize() const { return m_size; }

//Motion with constant speed, making sure objects stay in scope
void Object::motion(double dt)
{	
	m_position.x += m_velocity.x * dt;
    m_position.y += m_velocity.y * dt;
    if (m_position.x < m_size.x/2)
    {
        m_position.x = m_size.x/2;
        m_velocity.x = -m_velocity.x;
    }
    if (m_position.x > Input::width - m_size.x/2)
    {
        m_position.x = Input:: width - m_size.x/2;
        m_velocity.x = -m_velocity.x;
    }
    if (m_position.y > Input::height - m_size.y/2)
    {
        m_position.y = Input::height - m_size.y/2;
        m_velocity.y = -m_velocity.y;
    }
}

void Object::draw(ShaderProgram& shaderProgram, const Texture& texture) const
{            
    glm::mat4 model = glm::mat4(1.0f);  
    model = glm::translate(model, glm::vec3(m_position, 0.0));
    model = glm::scale(model, glm::vec3(m_size, 1.0f));
    
    shaderProgram.useProgram();
    shaderProgram.setUniform("spriteColor", m_color);
    shaderProgram.setUniform("model", model);    
    shaderProgram.setUniform("image", 0);
        
    texture.bindTexture(texture.getTextureID());    
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

const glm::vec3& Object::colorToVec3(BrickColor color)
{
    switch (color)
    {
    case blue: return Input::blue;
    case green: return Input::green;
    case red: return Input::red;
    case yellow: return Input::yellow;
    case grey: return Input::grey;
    default: return Input::grey;
    }
}
