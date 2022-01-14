#include "Entity.h"
#include <math.h>
#include <cmath>

Entity::Entity(const std::string& string, glm::vec2 position, glm::vec2 size)
{
	m_sprite = TextureManager::LoadTexture(string.c_str());
	m_position = position;
	m_size = size;
	m_collisionMin = {m_position.x - m_size.x / 2, m_position.y + m_size.y / 2};
	m_collisionMax = { m_position.x + m_size.x / 2, m_position.y - m_size.y / 2 };
}

Entity::Entity(const unsigned int sprite, glm::vec2 position, glm::vec2 size)
{
	m_sprite = sprite;
	m_position = position;
	m_size = size;
	m_collisionMin = { m_position.x - m_size.x / 2, m_position.y + m_size.y / 2 };
	m_collisionMax = { m_position.x + m_size.x / 2, m_position.y - m_size.y / 2 };
}

Entity::Entity(glm::vec2 position, glm::vec2 size)
{
	m_position = position;
	m_size = size;
	m_collisionMin = { m_position.x - m_size.x / 2, m_position.y + m_size.y / 2 };
	m_collisionMax = { m_position.x + m_size.x / 2, m_position.y - m_size.y / 2 };
}

bool checkCollision(std::shared_ptr<Entity> left, std::shared_ptr<Entity> right)
{
	left->m_collisionMin = { left->m_position.x - left->m_size.x / 2, left->m_position.y - left->m_size.y / 2 };
	left->m_collisionMax = { left->m_position.x + left->m_size.x / 2, left->m_position.y + left->m_size.y / 2 };
	right->m_collisionMin = { right->m_position.x - right->m_size.x / 2, right->m_position.y - right->m_size.y / 2 };
	right->m_collisionMax = { right->m_position.x + right->m_size.x / 2, right->m_position.y + right->m_size.y / 2 };
	
	//maxx1 > minx2 && minx1 < maxx2 && maxy1 > miny1 && miny1 < maxy2
	if(left->m_collisionMax.x > right->m_collisionMin.x &&
		left->m_collisionMin.x < right->m_collisionMax.x &&
		left->m_collisionMax.y > right->m_collisionMin.y &&
		left->m_collisionMin.y < right->m_collisionMax.y)
		return true;
	return false;
}

bool checkCollisionPlayer(std::shared_ptr<Entity> left, std::shared_ptr<Entity> right)
{
	left->m_collisionMin = { left->m_position.x - left->m_size.x / 2, left->m_position.y - left->m_size.y / 2 };
	left->m_collisionMax = { left->m_position.x + left->m_size.x / 2, left->m_position.y + left->m_size.y / 2 };

	//maxx1 > minx2 && minx1 < maxx2 && maxy1 > miny1 && miny1 < maxy2
	if (left->m_collisionMax.x > right->m_collisionMin.x &&
		left->m_collisionMin.x < right->m_collisionMax.x &&
		left->m_collisionMax.y > right->m_collisionMin.y &&
		left->m_collisionMin.y < right->m_collisionMax.y)
		return true;
	return false;
}
