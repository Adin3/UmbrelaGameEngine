#include "Player.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "bullet.h"

int Player::numberOfLifes;

Player::Player(const std::string& string, glm::vec2 position, glm::vec2 size) : Entity(string, position, size)
{
	m_bulletsprite = TextureManager::LoadTexture("gfx/img/sprites/pewpew.png");
	floare = TextureManager::LoadTexture("gfx/shader/rec/hp.png");
	isCollided = false;
	m_health = 4;
}

Player::Player(const unsigned int sprite, glm::vec2 position, glm::vec2 size) : Entity(sprite, position, size)
{
	m_bulletsprite = TextureManager::LoadTexture("gfx/img/sprites/pewpew.png");
	floare = TextureManager::LoadTexture("gfx/img/sprites/hp.png");
	isCollided = false;
	m_health = 4;
}

Player::~Player()
{
	Game::isGameOver = true;
}

void Player::onCreate()
{

}

void Player::onUpdate(float deltatime, GLFWwindow* window)
{
	for (int number = 0; number < numberOfLifes; number++)
	{
		Renderer::CreateQuad({ 25, 50 }, { 1000 + (number * 10), 700 }, m_bulletsprite);
	}
	Renderer::CreateQuad(m_size, m_position, m_sprite);
	m_collisionMin = { m_position.x - m_size.x / 8, (m_position.y - 10.0f) - m_size.y / 9 };
	m_collisionMax = { m_position.x + m_size.x / 8, (m_position.y - 10.0f) + m_size.y / 9 };
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && m_position.y < 1000)
			m_position.y += m_speed * deltatime;
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && m_position.y > 0)
			m_position.y -= m_speed * deltatime;
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && m_position.x > 245)
			m_position.x -= m_speed * deltatime;
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && m_position.x < 875)
			m_position.x += m_speed * deltatime;
		if ((glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) && m_lastFire > m_reloadTime)
		{
			std::shared_ptr<Entity> bulletLeft = std::make_shared<Bullet>(m_bulletsprite, glm::vec2(m_position.x - 12.0f, m_position.y + m_size.y - 24.0f), glm::vec2(10.0f, 40.0f), glm::vec2(0, 1));
			EntityManager::pushPlayersBullets(bulletLeft);
			EntityManager::addEntity(bulletLeft);
			std::shared_ptr<Entity> bulletMid = std::make_shared<Bullet>(m_bulletsprite, glm::vec2(m_position.x, m_position.y + m_size.y - 12.0f), glm::vec2(10.0f, 40.0f), glm::vec2(0, 1));
			EntityManager::pushPlayersBullets(bulletMid);
			EntityManager::addEntity(bulletMid);
			std::shared_ptr<Entity> bulletRight = std::make_shared<Bullet>(m_bulletsprite, glm::vec2(m_position.x + 12.0f, m_position.y + m_size.y - 24.0f), glm::vec2(10.0f, 40.0f), glm::vec2(0, 1));
			EntityManager::pushPlayersBullets(bulletRight);
			EntityManager::addEntity(bulletRight);
			m_lastFire = 0.0f;
		}
	}
	else
	{
		Renderer::CreateQuad({ m_collisionMax.x - m_collisionMin.x, m_collisionMax.y - m_collisionMin.y },
			{ m_position.x, m_position.y - 10}, floare, glm::vec4(1.0f, 0.1f, 0.1f, 1.0f));
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && m_position.y < 1000)
			m_position.y += m_speed / 2 * deltatime;
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && m_position.y > 0)
			m_position.y -= m_speed / 2 * deltatime;
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && m_position.x > 245)
			m_position.x -= m_speed / 2 * deltatime;
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && m_position.x < 875)
			m_position.x += m_speed / 2 * deltatime;
		if ((glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) && m_lastFire > m_reloadTime)
		{
			std::shared_ptr<Entity> bulletLeft = std::make_shared<Bullet>(m_bulletsprite, glm::vec2(m_position.x - 12.0f, m_position.y + m_size.y - 24.0f), glm::vec2(10.0f, 40.0f), glm::vec2(0, 1), 1500, glm::vec4(0.5f, 0.2f, 0.8f, 1.0f));
			EntityManager::pushPlayersBullets(bulletLeft);
			EntityManager::addEntity(bulletLeft);
			std::shared_ptr<Entity> bulletMid = std::make_shared<Bullet>(m_bulletsprite, glm::vec2(m_position.x, m_position.y + m_size.y - 12.0f), glm::vec2(10.0f, 40.0f), glm::vec2(0, 1), 1500, glm::vec4(0.5f, 0.2f, 0.8f, 1.0f));
			EntityManager::pushPlayersBullets(bulletMid);
			EntityManager::addEntity(bulletMid);
			std::shared_ptr<Entity> bulletRight = std::make_shared<Bullet>(m_bulletsprite, glm::vec2(m_position.x + 12.0f, m_position.y + m_size.y - 24.0f), glm::vec2(10.0f, 40.0f), glm::vec2(0, 1), 1500, glm::vec4(0.5f, 0.2f, 0.8f, 1.0f));
			EntityManager::pushPlayersBullets(bulletRight);
			EntityManager::addEntity(bulletRight);
			m_lastFire = 0.0f;
		}
	}
	

	if (isCollided == true) {
		if (m_lastiFrame > m_reloadiFrame)
		{
			m_health--;;
			numberOfLifes--;
			m_lastiFrame = 0.0f;
		}

		if (m_health <= 0) Game::isGameOver = true;
		isCollided = false;
	}

	m_lastiFrame += deltatime;
	m_lastFire += deltatime;
}
