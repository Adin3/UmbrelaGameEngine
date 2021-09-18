#include "EntityManager.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <algorithm>

std::vector<std::shared_ptr<Entity>> EntityManager::m_Entities;
std::vector<std::shared_ptr<Entity>> EntityManager::m_PlayerBullets;
std::vector<std::shared_ptr<Entity>> EntityManager::m_Enemies;
std::vector<std::shared_ptr<Entity>> EntityManager::m_LowEnemies;
std::vector<std::shared_ptr<Entity>> EntityManager::m_EnemiesBullets;
 
std::shared_ptr<Entity> EntityManager::m_player;

void EntityManager::addEntity(const std::shared_ptr<Entity>& entity)
{
	auto it = std::find(m_Entities.begin(), m_Entities.end(), entity);
	if (it == m_Entities.end())
		m_Entities.push_back(entity);
}

void EntityManager::removeEntity(const std::shared_ptr<Entity>& entity)
{
	auto it = std::find(m_Entities.begin(), m_Entities.end(), entity);
	if (it != m_Entities.end())
		m_Entities.erase(it);
}

void EntityManager::cleanEntity()
{
	m_Entities.clear();
	m_Enemies.clear();
	m_EnemiesBullets.clear();
	m_LowEnemies.clear();
	m_PlayerBullets.clear();
	m_player.reset();
}

void EntityManager::updateEntities(float deltaTime, GLFWwindow* window)
{
	for (int i = 0; i < m_Entities.size(); i++)
	{
		if (m_Entities[i])
		{
			m_Entities[i]->onUpdate(deltaTime, window);
		}
	}

	for (auto& enemy : m_Enemies)
	{
		if (enemy != nullptr)
		{
			for (auto& bullet : m_PlayerBullets)
			{
				if (checkCollision(enemy, bullet))
				{
					bullet->isCollided = true;
					enemy->isCollided = true;
				}
			}
		}
	}

	for (auto& ebullet : m_EnemiesBullets)
	{
		if (m_player != nullptr)
		{
			if (checkCollisionPlayer(ebullet, m_player))
			{
				ebullet->isCollided = true;
				m_player->isCollided = true;
			}
		}
	}

	if(m_player)
		if (m_player->IsAlive() == true) removePlayer();
	checkForDeadEntities(m_Entities);
	checkForDeadEntities(m_Enemies);
	checkForDeadEntities(m_EnemiesBullets);
	checkForDeadEntities(m_LowEnemies);
	checkForDeadEntities(m_PlayerBullets);
}

void EntityManager::pushEnemies(const std::shared_ptr<Entity>& entity)
{
	m_Enemies.push_back(entity);
}

void EntityManager::pushLowEnemies(const std::shared_ptr<Entity>& entity)
{
	m_LowEnemies.push_back(entity);
}

void EntityManager::pushEnemiesBullets(const std::shared_ptr<Entity>& entity)
{
	m_EnemiesBullets.push_back(entity);
}

void EntityManager::pushPlayersBullets(const std::shared_ptr<Entity>& entity)
{
	m_PlayerBullets.push_back(entity);
}

void EntityManager::pushPlayer(const std::shared_ptr<Entity>& entity)
{
	m_player = entity;
}

void EntityManager::removePlayerBullets(const std::shared_ptr<Entity>& entity)
{
	auto it = std::find(m_PlayerBullets.begin(), m_PlayerBullets.end(), entity);
	if (it != m_PlayerBullets.end())
		m_PlayerBullets.erase(it);
}

void EntityManager::removeEnemies(const std::shared_ptr<Entity>& entity)
{
	auto it = std::find(m_Enemies.begin(), m_Enemies.end(), entity);
	if (it != m_Enemies.end())
		m_Enemies.erase(it);
}

void EntityManager::removeEnemiesBullets(const std::shared_ptr<Entity>& entity)
{
	auto it = std::find(m_EnemiesBullets.begin(), m_EnemiesBullets.end(), entity);
	if (it != m_EnemiesBullets.end())
		m_EnemiesBullets.erase(it);
}

void EntityManager::cleanLowEnemies()
{
	for (auto& it : m_LowEnemies)
	{
		removeEntity(it);
	}
	m_LowEnemies.clear();
}

void EntityManager::checkForDeadEntities(std::vector<std::shared_ptr<Entity>>& vect)
{
	vect.erase(std::remove_if(vect.begin(), vect.end(), [](const std::shared_ptr<Entity>& en)->bool {return en->IsAlive(); }), vect.end());
}

void EntityManager::removePlayer()
{
	removeEntity(m_player);
}

