#pragma once
#include "../src/Application.h"
#include "Boss.h"
#include "Player.h"
#include "basicEnemy.h"
#include "MinionEnemy.h"
#include "SummonerEnemy.h"
#include "Spawner.h"
#include "../entity/Entity.h"

class Spawner;

class Game : public Application {
private:
	std::shared_ptr<Entity> m_player;
	unsigned int player;
	unsigned int hud;
	unsigned int pause;
	unsigned int gameover;
	unsigned int hp;
	unsigned int winscreen;
	unsigned int winscreen1;
	unsigned int menu;
	unsigned int info;
	unsigned int credits;
	unsigned int nori_bg;
	unsigned int point;
	unsigned int difficulty;
	std::shared_ptr<TextureManager> texture;
	std::shared_ptr<Spawner> spawner;
	bool isPause = false;
	float lastTime = 0.0f;
	float pauseTime = 0.1f;
	float lastTime1 = 0.0f;
	float lastTimeAfterDeath = 0.0f;
	float reloadTimeAfterDeath = 4.0f;
	int gameState = 0;

public:
	static bool isGameOver;
	static bool isGameWon;
	static bool isHardMode;
	Game(const char* string, unsigned int  width, unsigned int height);
	virtual void onCreate() override;
	virtual void onUpdate(float deltaTime) override;
};