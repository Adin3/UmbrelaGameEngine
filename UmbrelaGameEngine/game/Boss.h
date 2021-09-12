#pragma once
#include "../entity/Entity.h"
#include "bullet.h"
#include "game.h"

class Boss : public Entity {
private:
	unsigned int m_enemyBulletSprite;
	unsigned int hp;
	float m_lastTime = 0.0f;
	float m_reloadTime = 0.3f;
	int m_velocityX = 1;
	int m_state;
	int numberOfLifes = 10;
	bool m_showhp;
	float m_bspeed;
public:
	Boss(const std::string& string, glm::vec2 position, glm::vec2 size, float speed = 100.0f, float bspeed = 200.0f, bool showhp = true);
	Boss(const unsigned int sprite, glm::vec2 position, glm::vec2 size, float speed = 100.0f, float bspeed = 200.0f, bool showhp = true);

	virtual void onUpdate(float deltatime, GLFWwindow* window) override;
};