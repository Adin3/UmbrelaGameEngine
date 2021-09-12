#pragma once
#include "MinionEnemy.h"
#include "../entity/Entity.h"

class SummonerEnemy : public Entity {
private:
	float m_lastTime = 0.0f;
	float m_reloadTime = 1.0f;
	unsigned int m_enemySprite;
	int m_state;
	int m_velocityX = 1;
public:
	SummonerEnemy(const std::string& string, glm::vec2 position, glm::vec2 size, float speed = 80.0f);
	SummonerEnemy(const unsigned int sprite, glm::vec2 position, glm::vec2 size, float speed = 80.0f);

	virtual void onUpdate(float deltatime, GLFWwindow* window) override;
};
