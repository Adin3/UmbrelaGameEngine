#include "basicEnemy.h"
#include "bullet.h"
#include <cmath>

BasicEnemy::BasicEnemy(const std::string& string, glm::vec2 position, glm::vec2 size, float speed) 
	: Entity(string, position, size)
{
	m_enemyBulletSprite = TextureManager::LoadTexture("gfx/img/sprites/pewpew.png");
	m_health = 20;
	m_bspeed = speed;
}

BasicEnemy::BasicEnemy(const unsigned int sprite, glm::vec2 position, glm::vec2 size, float speed) 
	: Entity(sprite, position, size)
{
	m_enemyBulletSprite = TextureManager::LoadTexture("gfx/img/sprites/pewpew.png");
	m_health = 20;
	m_bspeed = speed;
}

void BasicEnemy::onUpdate(float deltatime, GLFWwindow* window)
{
	Renderer::CreateQuad(m_size, m_position, m_sprite);
	if (m_lastMovementTime > m_movementTime) {
		m_velocityX = -m_velocityX;
		m_lastMovementTime = 0.0f;
	}

	m_speed = std::lerp(m_bspeed, 10, m_lastMovementTime / 2.5);
	m_velocityY = std::lerp(10.0f, -5.0f, m_lastMovementTime / 2.5f);
	m_position.x += deltatime * m_speed * m_velocityX;
	m_position.y -= deltatime * m_bspeed * (m_velocityY / 15.0f);

	if (m_lastTime > m_reloadTime)
	{
		if (Game::isHardMode == false)
		{
			std::shared_ptr<Entity> bulletLeft = std::make_shared<Bullet>(m_enemyBulletSprite, glm::vec2( m_position.x, m_position.y - m_size.y / 2 ), glm::vec2(10.0f, 10.0f ),
				glm::vec2(-cos(glm::radians(30.0f)), -sin(glm::radians(30.0f)) ), 500.0f, glm::vec4(0.05f, 0.45f, 0.2f, 1.0f));
			EntityManager::pushEnemiesBullets(bulletLeft);
			EntityManager::addEntity(bulletLeft);
			std::shared_ptr<Entity> bulletMid = std::make_shared<Bullet>(m_enemyBulletSprite, glm::vec2(m_position.x, m_position.y - m_size.y / 2 ), glm::vec2(10.0f, 10.0f ),
				glm::vec2(0.0f, -1.0f), 350.0f, glm::vec4(0.05f, 0.45f, 0.2f, 1.0f));
			EntityManager::pushEnemiesBullets(bulletMid);
			EntityManager::addEntity(bulletMid);
			std::shared_ptr<Entity> bulletRight = std::make_shared<Bullet>(m_enemyBulletSprite, glm::vec2(m_position.x, m_position.y - m_size.y / 2 ), glm::vec2(10.0f, 10.0f ),
				glm::vec2(cos(glm::radians(30.0f)), -sin(glm::radians(30.0f))), 500.0f, glm::vec4(0.05f, 0.45f, 0.2f, 1.0f));
			EntityManager::pushEnemiesBullets(bulletRight);
			EntityManager::addEntity(bulletRight);
		}
		else
		{
			std::shared_ptr<Entity> bulletLeft = std::make_shared<Bullet>(m_enemyBulletSprite, glm::vec2(m_position.x, m_position.y - m_size.y / 2), glm::vec2(10.0f, 10.0f),
				glm::vec2(-cos(glm::radians(30.0f)), -sin(glm::radians(30.0f))), 800.0f, glm::vec4(0.05f, 0.45f, 0.2f, 1.0f));
			EntityManager::pushEnemiesBullets(bulletLeft);
			EntityManager::addEntity(bulletLeft);
			std::shared_ptr<Entity> bulletMid = std::make_shared<Bullet>(m_enemyBulletSprite, glm::vec2(m_position.x, m_position.y - m_size.y / 2), glm::vec2(10.0f, 10.0f),
				glm::vec2(0.0f, -1.0f), 650.0f, glm::vec4(0.05f, 0.45f, 0.2f, 1.0f));
			EntityManager::pushEnemiesBullets(bulletMid);
			EntityManager::addEntity(bulletMid);
			std::shared_ptr<Entity> bulletRight = std::make_shared<Bullet>(m_enemyBulletSprite, glm::vec2(m_position.x, m_position.y - m_size.y / 2), glm::vec2(10.0f, 10.0f),
				glm::vec2(cos(glm::radians(30.0f)), -sin(glm::radians(30.0f))), 800.0f, glm::vec4(0.05f, 0.45f, 0.2f, 1.0f));
			EntityManager::pushEnemiesBullets(bulletRight);
			EntityManager::addEntity(bulletRight);
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
	m_lastMovementTime += deltatime;
}
