#include "SummonerEnemy.h"


const enum STATE {
	MOVING = 0, SHOOTING,
};


SummonerEnemy::SummonerEnemy(const std::string& string, glm::vec2 position, glm::vec2 size, float speed) 
	: Entity(string, position, size)
{
	m_enemySprite = TextureManager::LoadTexture("gfx/img/sprites/enemies/strop.png");
	m_state = STATE::MOVING;
	m_health = 35;
	m_speed = speed;
}

SummonerEnemy::SummonerEnemy(const unsigned int sprite, glm::vec2 position, glm::vec2 size, float speed) 
	: Entity(sprite, position, size)
{
	m_enemySprite = TextureManager::LoadTexture("gfx/img/sprites/enemies/strop.png");
	m_state = STATE::MOVING;
	m_health = 35;
	m_speed = speed;
}

void SummonerEnemy::onUpdate(float deltatime, GLFWwindow* window)
{
	Renderer::CreateQuad(m_size, m_position, m_sprite);
	switch (m_state)
	{
	case STATE::MOVING :
		m_position.y -= m_speed * deltatime;
		if ((m_position.y < 900.0f && m_position.y > 700.0f ) || m_position.y < 400.0f) {
			m_state = STATE::SHOOTING;
		}
		break;
	case STATE::SHOOTING :
		m_position.x += m_speed * deltatime * m_velocityX;
		if ((m_position.x > 800 && m_position.x < 850) || m_position.x > 1225) {
			m_velocityX = -1;
		}
		if (m_position.x < 275 || (m_position.x < 990 && m_position.x > 810)) {
			m_velocityX = 1;
		}
		if (m_lastTime > m_reloadTime)
		{
			std::shared_ptr<Entity> minionenemy = std::make_shared<MinionEnemy>(m_enemySprite, glm::vec2(m_position.x, m_position.y - m_size.y / 2 ), glm::vec2(m_size.y - m_size.y / 2, m_size.x - m_size.x / 2 ));
			EntityManager::pushEnemies(minionenemy);
			EntityManager::addEntity(minionenemy);
			m_lastTime = 0.0f;
		}
		break;
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
