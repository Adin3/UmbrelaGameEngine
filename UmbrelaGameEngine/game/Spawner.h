#pragma once
#include "../entity/Entity.h"
#include "Boss.h"
#include "Player.h"
#include "basicEnemy.h"
#include "MinionEnemy.h"
#include "SummonerEnemy.h"

class Spawner {
private:
	int spwType = 6;
	int numberOfEnemies = 0;
	int isBossReady = 0;
	float m_reloadTimeBig = 2.0f;
	float m_lastFireBig = 0.0f;
	float m_reloadTimeSmall = m_reloadTimeBig / 2.0f;
	float m_lastFireSmall = 0.0f; 
	unsigned int m_playerSprite;
	unsigned int m_basicEnemySprite;
	unsigned int m_minionEnemySprite;
	unsigned int m_summonerEnemySprite;
	unsigned int m_bossSprite;
	std::shared_ptr<Entity> enemy;
	std::shared_ptr<Entity> enemyminion;
	std::shared_ptr<Entity> enemysummoner;
	std::shared_ptr<Entity> boss;
public:
	Spawner();
	void onUpdate(float deltatime);
};