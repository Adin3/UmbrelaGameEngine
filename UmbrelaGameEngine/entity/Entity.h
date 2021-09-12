#pragma once
#include "../gfx/graphics.h"
#include "EntityManager.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Entity {

friend class EntityManager;
friend bool checkCollision(std::shared_ptr<Entity> left, std::shared_ptr<Entity> right);
friend bool checkCollisionPlayer(std::shared_ptr<Entity> left, std::shared_ptr<Entity> right);

private:

public:
	Entity(const std::string& string, glm::vec2 position, glm::vec2 size);
	Entity(const unsigned int sprite, glm::vec2 position, glm::vec2 size);
	virtual void onCreate() { }
	virtual void onUpdate(float deltatime, GLFWwindow* window) { }
	virtual void getCollisionPos() { }
	bool IsAlive() const { return m_health <= 0; }

protected:
	glm::vec2 m_position;
	glm::vec2 m_size;
	glm::vec2 m_collisionMax;
	glm::vec2 m_collisionMin;
	unsigned int m_sprite;
	float m_speed = 350.0f;
	float m_damage = 1.0f;
	bool isCollided = false;
	int m_health = 4;
};