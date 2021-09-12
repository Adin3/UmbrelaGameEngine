#pragma once
#include "../gfx/graphics.h"
#include "../entity/Entity.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "game.h"

class Player : public Entity{
private:
	float m_reloadTime = 0.1f;
	float m_lastFire = 0.0f;
	unsigned int m_bulletsprite;
	unsigned int floare;
	float m_lastiFrame = 0.0f;
	float m_reloadiFrame = 1.0f;
public:
	static int numberOfLifes;
	Player(const std::string& string, glm::vec2 position, glm::vec2 size);
	Player(const unsigned int sprite, glm::vec2 position, glm::vec2 size);
	~Player();

	virtual void onCreate() override;
	virtual void onUpdate(float deltatime, GLFWwindow* window) override;
};