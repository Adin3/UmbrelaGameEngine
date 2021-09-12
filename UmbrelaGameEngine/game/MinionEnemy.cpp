#include "MinionEnemy.h"
#include "bullet.h"
#include <cmath>

MinionEnemy::MinionEnemy(const std::string& string, glm::vec2 position, glm::vec2 size, float speed) 
	: Entity(string, position, size)
{
	m_enemyBulletSprite = TextureManager::LoadTexture("gfx/img/sprites/pewpew.png");
	m_speed = speed;
	m_health = 10;
}

MinionEnemy::MinionEnemy(const unsigned int sprite, glm::vec2 position, glm::vec2 size, float speed) 
	: Entity(sprite, position, size)
{
	m_enemyBulletSprite = TextureManager::LoadTexture("gfx/img/sprites/pewpew.png");
	m_speed = speed;
	m_health = 10;
}

void MinionEnemy::onUpdate(float deltatime, GLFWwindow* window)
{
	Renderer::CreateQuad(m_size, m_position, m_sprite);
	m_position.y -= m_speed * deltatime;
	if (m_lastTime > m_reloadTime)
	{
		if (Game::isHardMode == false)
		{
			for (float angle = 0.0f; angle <= 360; angle += 30.0f)
			{
				std::shared_ptr<Entity> bullet = std::make_shared<Bullet>(m_enemyBulletSprite, glm::vec2(m_position.x, m_position.y - m_size.y / 2), glm::vec2(10.0f, 10.0f),
					glm::vec2(cos(glm::radians(angle)), sin(glm::radians(angle))), 200.0f, glm::vec4(0.0f, 0.44f, 0.67f, 1.0f));
				EntityManager::pushEnemiesBullets(bullet);
				EntityManager::addEntity(bullet);
			}
		}
		else
		{
			for (float angle = 0.0f; angle <= 360; angle += 10.0f)
			{
				std::shared_ptr<Entity> bullet = std::make_shared<Bullet>(m_enemyBulletSprite, glm::vec2(m_position.x, m_position.y - m_size.y / 2), glm::vec2(10.0f, 10.0f),
					glm::vec2(cos(glm::radians(angle)), sin(glm::radians(angle))), 300.0f, glm::vec4(0.0f, 0.44f, 0.67f, 1.0f));
				EntityManager::pushEnemiesBullets(bullet);
				EntityManager::addEntity(bullet);
			}
		}

		m_lastTime = 0.0f;
	}
	if (isCollided == true || m_position.y < 0)
	{
		m_health -= m_damage;
		if (m_health <= 0) {
			//delete this;
		}
		isCollided = false;
	}
	m_lastTime += deltatime;
}
