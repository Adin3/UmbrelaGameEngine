#include "Boss.h"

const enum STATE {
	MOVING = 0, SHOOTING,
};

Boss::Boss(const std::string& string, glm::vec2 position, glm::vec2 size, float speed, float bspeed, bool showhp)
	: Entity(string, position, size)
{
	m_enemyBulletSprite = TextureManager::LoadTexture("gfx/img/sprites/pewpew.png");
	hp = TextureManager::LoadTexture("gfx/img/sprites/hpboss.png");
	m_state = STATE::MOVING;
	m_health = 1000;
	m_speed = speed;
	m_bspeed = bspeed;
	m_showhp = showhp;
}

Boss::Boss(const unsigned int sprite, glm::vec2 position, glm::vec2 size, float speed, float bspeed, bool showhp)
	: Entity(sprite, position, size)
{
	m_enemyBulletSprite = TextureManager::LoadTexture("gfx/img/sprites/pewpew.png");
	hp = TextureManager::LoadTexture("gfx/img/sprites/hpboss.png");
	m_state = STATE::MOVING;
	m_health = 1000;
	m_speed = speed;
	m_bspeed = bspeed;
	m_showhp = showhp;
}

void Boss::onUpdate(float deltatime, GLFWwindow* window)
{
	Renderer::CreateQuad(m_size, m_position, m_sprite);
	
	switch (m_state)
	{
	case STATE::MOVING :
		m_position.y -= m_speed * deltatime;
		if ((m_position.y < 700.0f && m_position.y > 600.0f) || m_position.y < 350.0f) {
			m_state = STATE::SHOOTING;
		}
		break;
	case STATE::SHOOTING :
		if (m_showhp == true)
		{
			for (int number = 0; number < numberOfLifes; number++)
			{
				Renderer::CreateQuad({ 50, 25 }, { 400 + (number * 42), 975 }, hp, { 0.5f, 0.18f, 0.74f, 1.0f });
			}
		}
		m_position.x += m_speed * deltatime * m_velocityX;
		if (m_position.x < 275 || (m_position.x < 990 && m_position.x > 810)) {
			m_velocityX = 1;
		}
		if ((m_position.x > 800 && m_position.x < 850) || m_position.x > 1225) {
			m_velocityX = -1;
		}
		if (m_lastTime > m_reloadTime)
		{
			float offset = rand() % 10 + 20;
			if (Game::isHardMode == true)
			{
				for (float angle = 0.0f; angle <= 360; angle += offset)
				{
					std::shared_ptr<Entity> bullet = std::make_shared<Bullet>(m_enemyBulletSprite, glm::vec2(m_position.x, m_position.y), glm::vec2(10.0f, 10.0f ),
						glm::vec2( cos(glm::radians(angle)), sin(glm::radians(angle)) ), m_bspeed);
					EntityManager::pushEnemiesBullets(bullet);
					EntityManager::addEntity(bullet);
					std::shared_ptr<Entity> bullet2 = std::make_shared<Bullet>(m_enemyBulletSprite, glm::vec2(m_position.x, m_position.y), glm::vec2(10.0f, 10.0f),
						glm::vec2(cos(glm::radians(angle+10.0f)), sin(glm::radians(angle+10.0f))), m_bspeed);
					EntityManager::pushEnemiesBullets(bullet2);
					EntityManager::addEntity(bullet2);
					std::shared_ptr<Entity> bullet3 = std::make_shared<Bullet>(m_enemyBulletSprite, glm::vec2(m_position.x, m_position.y), glm::vec2(10.0f, 10.0f ),
						glm::vec2(cos(glm::radians(angle)), sin(glm::radians(angle)) ), m_bspeed + 200.0f);
					EntityManager::pushEnemiesBullets(bullet3);
					EntityManager::addEntity(bullet3);
					std::shared_ptr<Entity> bullet4 = std::make_shared<Bullet>(m_enemyBulletSprite, glm::vec2(m_position.x, m_position.y), glm::vec2(10.0f, 10.0f),
						glm::vec2(cos(glm::radians(angle+20.0f)), sin(glm::radians(angle+20.0f))), m_bspeed + 200.0f);
					EntityManager::pushEnemiesBullets(bullet4);
					EntityManager::addEntity(bullet4);
				}
			}
			else
			{
				for (float angle = 0.0f; angle <= 360; angle += offset)
				{
					std::shared_ptr<Entity> bullet = std::make_shared<Bullet>(m_enemyBulletSprite, glm::vec2(m_position.x, m_position.y), glm::vec2(10.0f, 10.0f),
						glm::vec2(cos(glm::radians(angle)), sin(glm::radians(angle))), m_bspeed);
					EntityManager::pushEnemiesBullets(bullet);
					EntityManager::addEntity(bullet);
					std::shared_ptr<Entity> bullet2 = std::make_shared<Bullet>(m_enemyBulletSprite, glm::vec2(m_position.x, m_position.y), glm::vec2(10.0f, 10.0f),
						glm::vec2(cos(glm::radians(angle + 10.0f)), sin(glm::radians(angle + 10.0f))), m_bspeed);
					EntityManager::pushEnemiesBullets(bullet2);
					EntityManager::addEntity(bullet2);
				}
			}
			m_lastTime = 0.0f;
		}
		break;
	}
	if (isCollided == true || m_position.y < 0)
	{
		m_health -= m_damage;
		if (m_health % 100 == 0) {
			numberOfLifes--;
		}
		if (m_health <= 0)
		{
			Game::isGameWon = true;
		}
		isCollided = false;
	}
	m_lastTime += deltatime;
}
