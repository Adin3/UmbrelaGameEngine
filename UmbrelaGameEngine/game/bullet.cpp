#include "bullet.h"

Bullet::Bullet(const std::string& string, glm::vec2 position, glm::vec2 size, glm::vec2 velocity, float speed, glm::vec4 color) 
	: Entity(string, position, size)
{
	m_velocity = velocity;
	isCollided = false;
	m_speed = speed;
	m_color = color;
}

Bullet::Bullet(const unsigned int sprite, glm::vec2 position, glm::vec2 size, glm::vec2 velocity, float speed, glm::vec4 color) 
	: Entity(sprite, position, size)
{
	m_velocity = velocity;
	isCollided = false;
	m_speed = speed;
	m_color = color;
}

void Bullet::onUpdate(float deltatime, GLFWwindow* window)
{
	m_position.y += m_speed * deltatime * m_velocity.y;
	m_position.x += m_speed * deltatime * m_velocity.x;

	Renderer::CreateQuad(m_size, m_position, m_sprite, m_color);

	if (m_position.y > 1000 || m_position.y < -500 || m_position.x < -500 || (m_position.x > 900 && m_position.x < 925) || m_position.x > 1300) {
		isCollided = true;
	}

	if (isCollided == true) {
		m_health -= m_health;
		//delete(this);
	}
}


