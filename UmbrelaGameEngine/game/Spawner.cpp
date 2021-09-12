#include "Spawner.h"

Spawner::Spawner()
{
	m_basicEnemySprite 	   = TextureManager::LoadTexture("gfx/img/sprites/enemies/frunza.png");
	m_minionEnemySprite    = TextureManager::LoadTexture("gfx/img/sprites/enemies/strop.png");
	m_summonerEnemySprite  = TextureManager::LoadTexture("gfx/img/sprites/enemies/nor.png");
	m_bossSprite       	   = TextureManager::LoadTexture("gfx/img/sprites/enemies/boss.png");
}							 

void Spawner::onUpdate(float deltatime)
{
	//if (m_lastFireBig > m_reloadTimeBig)
	//{
	//	enemy = new BasicEnemy(m_basicEnemySprite, { 450, 1200 }, { 70.0f, 50.0f });
	//	EntityManager::pushEnemies(enemy);
	//	m_lastFireBig = 0;
	//}
	//if (m_lastFireSmall > m_reloadTimeSmall)
	//{
	//	EntityManager::cleanLowEnemies();
	//	enemy = new BasicEnemy(m_basicEnemySprite, { 1001, 500}, { 40.0f, 24.0f }, 100.0f);
	//	EntityManager::pushLowEnemies(enemy);
	//	m_reloadTimeSmall = m_reloadTimeBig;
	//	m_lastFireSmall = 0;
	//}
	if (m_lastFireBig > m_reloadTimeBig)
	{
		if (isBossReady == 0)
		{
			switch (spwType) {
			case 1:
				enemy = std::make_shared<BasicEnemy>(m_basicEnemySprite, glm::vec2(200, 1050 ), glm::vec2( 70.0f, 50.0f ), 250);
				EntityManager::pushEnemies(enemy);
				EntityManager::addEntity(enemy);
				enemy = std::make_shared<BasicEnemy>(m_basicEnemySprite, glm::vec2(350, 1050), glm::vec2(70.0f, 50.0f), 200);
				EntityManager::pushEnemies(enemy);
				EntityManager::addEntity(enemy);
				enemy = std::make_shared<BasicEnemy>(m_basicEnemySprite, glm::vec2(500, 1050), glm::vec2(70.0f, 50.0f), 150);
				EntityManager::pushEnemies(enemy);
				EntityManager::addEntity(enemy);
				enemy = std::make_shared<BasicEnemy>(m_basicEnemySprite, glm::vec2(650, 1050), glm::vec2(70.0f, 50.0f), 100);
				EntityManager::pushEnemies(enemy);
				EntityManager::addEntity(enemy);
				break;
			case 2:
				enemy = std::make_shared<BasicEnemy>(m_basicEnemySprite, glm::vec2(650, 1050), glm::vec2(70.0f, 50.0f), 200);
				EntityManager::pushEnemies(enemy);
				EntityManager::addEntity(enemy);
				enemy = std::make_shared<BasicEnemy>(m_basicEnemySprite, glm::vec2(500, 1050), glm::vec2(70.0f, 50.0f), 200);
				EntityManager::pushEnemies(enemy);
				EntityManager::addEntity(enemy);
				enemy = std::make_shared<BasicEnemy>(m_basicEnemySprite, glm::vec2(350, 1050), glm::vec2(70.0f, 50.0f), 150);
				EntityManager::pushEnemies(enemy);
				EntityManager::addEntity(enemy);
				enemy = std::make_shared<BasicEnemy>(m_basicEnemySprite, glm::vec2(200, 1050), glm::vec2(70.0f, 50.0f), 100);
				EntityManager::pushEnemies(enemy);
				EntityManager::addEntity(enemy);
				break;
			case 3:
				enemyminion = std::make_shared<MinionEnemy>(m_minionEnemySprite, glm::vec2(300, 1200 ), glm::vec2(50.0f, 70.0f ));
				EntityManager::pushEnemies(enemyminion);
				EntityManager::addEntity(enemyminion);
				enemyminion = std::make_shared<MinionEnemy>(m_minionEnemySprite, glm::vec2(800, 1200), glm::vec2(50.0f, 70.0f));
				EntityManager::pushEnemies(enemyminion);
				EntityManager::addEntity(enemyminion);
				break;
			case 4:
				enemysummoner = std::make_shared<SummonerEnemy>(m_summonerEnemySprite, glm::vec2(300, 1200 ), glm::vec2(160.0f, 100.0f ));
				EntityManager::pushEnemies(enemysummoner);
				EntityManager::addEntity(enemysummoner);
				enemysummoner = std::make_shared<SummonerEnemy>(m_summonerEnemySprite, glm::vec2(800, 1200), glm::vec2(160.0f, 100.0f));
				EntityManager::pushEnemies(enemysummoner);
				EntityManager::addEntity(enemysummoner);
				break;
			case 5:
				enemysummoner = std::make_shared<SummonerEnemy>(m_summonerEnemySprite, glm::vec2(300, 1200), glm::vec2(160.0f, 100.0f));
				EntityManager::pushEnemies(enemysummoner);
				EntityManager::addEntity(enemysummoner);
				enemyminion = std::make_shared<MinionEnemy>(m_minionEnemySprite, glm::vec2(800, 1400), glm::vec2(50.0f, 70.0f));
				EntityManager::pushEnemies(enemyminion);
				EntityManager::addEntity(enemyminion);
				break;
			case 6:
				enemyminion = std::make_shared<MinionEnemy>(m_minionEnemySprite, glm::vec2(550, 1200), glm::vec2(50.0f, 70.0f));
				EntityManager::pushEnemies(enemyminion);
				EntityManager::addEntity(enemyminion);
				enemy = std::make_shared<BasicEnemy>(m_basicEnemySprite, glm::vec2(250, 1050), glm::vec2(70.0f, 50.0f), 150);
				EntityManager::pushEnemies(enemy);
				EntityManager::addEntity(enemy);
				enemy = std::make_shared<BasicEnemy>(m_basicEnemySprite, glm::vec2(600, 1050), glm::vec2(70.0f, 50.0f), 150);
				EntityManager::pushEnemies(enemy);
				EntityManager::addEntity(enemy);
				break;
			}
		}

		if (isBossReady == 1)
		{
			numberOfEnemies = 0;
			isBossReady++;
			boss = std::make_shared<Boss>(m_bossSprite, glm::vec2(600, 1100 ), glm::vec2(240.0f, 280.0f ));
			EntityManager::pushEnemies(boss);
			EntityManager::addEntity(boss);
		}

		m_reloadTimeBig = 999.0f;
		m_lastFireBig = 0;
	}
	if (m_lastFireSmall > m_reloadTimeSmall)
	{
		spwType = rand() % 6 + 1;

		if (numberOfEnemies > 12)
		{
			EntityManager::cleanLowEnemies();
			isBossReady++;
			boss = std::make_shared<Boss>(m_bossSprite, glm::vec2(1100, 500), glm::vec2(30.0f, 35.0f), 50.0f, 100.0f, false);
			EntityManager::pushEnemies(boss);
			EntityManager::addEntity(boss);
			m_reloadTimeBig = 2.0f;
			m_reloadTimeSmall = 999.0f;
		}

		if (isBossReady == 0)
		{
			switch (spwType) {
			case 1:
				EntityManager::cleanLowEnemies();
				enemy = std::make_shared<BasicEnemy>(m_basicEnemySprite, glm::vec2(925, 500 ), glm::vec2( 40.0f, 24.0f ), 120.0f);
				EntityManager::pushLowEnemies(enemy);
				EntityManager::addEntity(enemy);
				enemy = std::make_shared<BasicEnemy>(m_basicEnemySprite, glm::vec2(975, 500), glm::vec2(40.0f, 24.0f), 100.0f);
				EntityManager::pushLowEnemies(enemy);
				EntityManager::addEntity(enemy);
				enemy = std::make_shared<BasicEnemy>(m_basicEnemySprite, glm::vec2(1025, 500), glm::vec2(40.0f, 24.0f), 80.0f);
				EntityManager::pushLowEnemies(enemy);
				EntityManager::addEntity(enemy);
				enemy = std::make_shared<BasicEnemy>(m_basicEnemySprite, glm::vec2(1075, 500), glm::vec2(40.0f, 24.0f), 60.0f);
				EntityManager::pushLowEnemies(enemy);
				EntityManager::addEntity(enemy);
				m_reloadTimeSmall = 6.0f;
				m_reloadTimeBig = 2.0f;
				numberOfEnemies += 1;
				break;
			case 2:
				EntityManager::cleanLowEnemies();
				enemy = std::make_shared<BasicEnemy>(m_basicEnemySprite, glm::vec2(1075, 500), glm::vec2(40.0f, 24.0f), 120.0f);
				EntityManager::pushLowEnemies(enemy);
				EntityManager::addEntity(enemy);
				enemy = std::make_shared<BasicEnemy>(m_basicEnemySprite, glm::vec2(1025, 500), glm::vec2(40.0f, 24.0f), 100.0f);
				EntityManager::pushLowEnemies(enemy);
				EntityManager::addEntity(enemy);
				enemy = std::make_shared<BasicEnemy>(m_basicEnemySprite, glm::vec2(975, 500), glm::vec2(40.0f, 24.0f), 80.0f);
				EntityManager::pushLowEnemies(enemy);
				EntityManager::addEntity(enemy);
				enemy = std::make_shared<BasicEnemy>(m_basicEnemySprite, glm::vec2(925, 500), glm::vec2(40.0f, 24.0f), 60.0f);
				EntityManager::pushLowEnemies(enemy);
				EntityManager::addEntity(enemy);
				m_reloadTimeSmall = 6.0f;
				m_reloadTimeBig = 2.0f;
				numberOfEnemies += 1;
				break;
			case 3:
				EntityManager::cleanLowEnemies();
				enemyminion = std::make_shared<MinionEnemy>(m_minionEnemySprite, glm::vec2(1000, 500 ), glm::vec2(24.0f, 40.0f ), 100.0f);
				EntityManager::pushLowEnemies(enemyminion);
				EntityManager::addEntity(enemyminion);
				enemyminion = std::make_shared<MinionEnemy>(m_minionEnemySprite, glm::vec2(1225, 500), glm::vec2(24.0f, 40.0f), 100.0f);
				EntityManager::pushLowEnemies(enemyminion);
				EntityManager::addEntity(enemyminion);
				m_reloadTimeSmall = 4.0f;
				m_reloadTimeBig = 2.0f;
				numberOfEnemies += 1;
				break;
			case 4:
				EntityManager::cleanLowEnemies();
				enemysummoner = std::make_shared<SummonerEnemy>(m_summonerEnemySprite, glm::vec2(1000, 550 ), glm::vec2(40.0f, 24.0f ), 30.0f);
				EntityManager::pushLowEnemies(enemysummoner);
				EntityManager::addEntity(enemysummoner);
				enemysummoner = std::make_shared<SummonerEnemy>(m_summonerEnemySprite, glm::vec2(1225, 550), glm::vec2(40.0f, 24.0f), 30.0f);
				EntityManager::pushLowEnemies(enemysummoner);
				EntityManager::addEntity(enemysummoner);
				m_reloadTimeSmall = 13.0f;
				m_reloadTimeBig = 2.0f;
				numberOfEnemies += 1;
				break;
			case 5:
				EntityManager::cleanLowEnemies();
				enemysummoner = std::make_shared<SummonerEnemy>(m_summonerEnemySprite, glm::vec2(1000, 500), glm::vec2(40.0f, 24.0f), 30.0f);
				EntityManager::pushLowEnemies(enemysummoner);
				EntityManager::addEntity(enemysummoner);
				enemyminion = std::make_shared<MinionEnemy>(m_minionEnemySprite, glm::vec2(1225, 700), glm::vec2(24.0f, 40.0f), 100.0f);
				EntityManager::pushLowEnemies(enemyminion);
				EntityManager::addEntity(enemyminion);
				m_reloadTimeSmall = 10.0f;
				m_reloadTimeBig = 2.0f;
				numberOfEnemies += 1;
				break;
			case 6:
				EntityManager::cleanLowEnemies();
				enemyminion = std::make_shared<MinionEnemy>(m_minionEnemySprite, glm::vec2(1112, 600), glm::vec2(24.0f, 40.0f), 100.0f);
				EntityManager::pushLowEnemies(enemyminion);
				EntityManager::addEntity(enemyminion);
				enemy = std::make_shared<BasicEnemy>(m_basicEnemySprite, glm::vec2(950, 500), glm::vec2(40.0f, 24.0f), 100.0f);
				EntityManager::pushLowEnemies(enemy);
				EntityManager::addEntity(enemy);
				enemy = std::make_shared<BasicEnemy>(m_basicEnemySprite, glm::vec2(1050, 500), glm::vec2(40.0f, 24.0f), 100.0f);
				EntityManager::pushLowEnemies(enemy);
				EntityManager::addEntity(enemy);
				m_reloadTimeSmall = 6.0f;
				m_reloadTimeBig = 2.0f;
				numberOfEnemies += 1;
				break;
			}
		}

		m_lastFireSmall = 0;
		m_lastFireBig = 0;
	}
	m_lastFireBig += deltatime;
	m_lastFireSmall += deltatime;
}
