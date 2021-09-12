#pragma once
#include "../entity/Entity.h"
#include "game.h"

class MinionEnemy : public Entity{
private:
	float m_lastTime = 0.0f;
	float m_reloadTime = 0.5f;
	unsigned int m_enemyBulletSprite;
public:
	MinionEnemy(const std::string& string, glm::vec2 position, glm::vec2 size, float speed = 200);
	MinionEnemy(const unsigned int sprite, glm::vec2 position, glm::vec2 size, float speed = 200);

	virtual void onUpdate(float deltatime, GLFWwindow* window) override;
};
