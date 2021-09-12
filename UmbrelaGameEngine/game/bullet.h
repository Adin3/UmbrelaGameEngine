#pragma once
#include "../entity/Entity.h"

class Bullet : public Entity {
private:
	float m_speed = 1000.0f;
	glm::vec4 m_color;
	glm::vec2 m_velocity;
public:
	Bullet(const std::string& string, glm::vec2 position, glm::vec2 size, glm::vec2 velocity, float speed = 1000.0f, glm::vec4 color = {0.5f, 0.18f, 0.74f, 1.0f });
	Bullet(const unsigned int sprite, glm::vec2 position, glm::vec2 size, glm::vec2 velocity, float speed = 1000.0f, glm::vec4 color = {0.5f, 0.18f, 0.74f, 1.0f });

	virtual void onUpdate(float deltatime, GLFWwindow* window) override;
};