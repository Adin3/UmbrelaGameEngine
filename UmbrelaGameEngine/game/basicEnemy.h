#pragma once
#include "../gfx/graphics.h"
#include "../entity/Entity.h"
#include "game.h"

class BasicEnemy : public Entity {
private:
	unsigned int m_enemyBulletSprite;
	float m_reloadTime = 0.6f;
	float m_lastTime = 0.0f;
	float m_movementTime = 2.5f;
	int m_velocityX = 1;
	float m_velocityY = 1;
	float m_lastMovementTime = 0.0f;
	int m_bspeed;
public:
	BasicEnemy(const std::string& string, glm::vec2 position, glm::vec2 size, float speed = 200);
	BasicEnemy(const unsigned int sprite, glm::vec2 position, glm::vec2 size, float speed = 200);

	virtual void onUpdate(float deltatime, GLFWwindow* window) override;
};