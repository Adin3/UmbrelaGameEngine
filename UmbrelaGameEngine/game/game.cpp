#include "game.h"
#include "../entity/EntityManager.h"

enum GAME_STATE {
	MAIN_MENU = 0,
	CREDITS,
	DIFFICULTY_SELECT,
	INFO_SCREEN,
	GAME_SCREEN,
	WIN_SCREEN,
};

bool Game::isGameOver;
bool Game::isGameWon;
bool Game::isHardMode;

Game::Game(const char* string, unsigned int  width, unsigned int height) 
	: Application(string, width, height)
{
	texture = std::make_shared<TextureManager>();
	hud = TextureManager::LoadTexture("gfx/img/screen/hud.png");
	pause = TextureManager::LoadTexture("gfx/img/screen/pause.png");
	gameover = TextureManager::LoadTexture("gfx/img/screen/game_over.png");
	player = TextureManager::LoadTexture("gfx/img/sprites/player.png");
	hp = TextureManager::LoadTexture("gfx/img/sprites/hp.png");
	winscreen = TextureManager::LoadTexture("gfx/img/screen/winscreen.png");
	winscreen1 = TextureManager::LoadTexture("gfx/img/screen/winscreen1.png");
	menu = TextureManager::LoadTexture("gfx/img/screen/menu.png");
	credits = TextureManager::LoadTexture("gfx/img/screen/credits.png");
	nori_bg = TextureManager::LoadTexture("gfx/shader/rec/nor_bg.png");
	info = TextureManager::LoadTexture("gfx/img/screen/info.png");
	point = TextureManager::LoadTexture("gfx/img/sprites/point.png");
	difficulty = TextureManager::LoadTexture("gfx/img/screen/difficulty.png");
}
void Game::onCreate()
{
	spawner = std::make_shared<Spawner>();
	m_player = std::make_shared<Player>(player, glm::vec2(650, 50), glm::vec2(80.0f, 100.0f));
	EntityManager::pushPlayer(m_player);
	EntityManager::addEntity(m_player);
	isGameOver = false;
	isGameWon = false;
	Player::numberOfLifes = 4;
}

void Game::onUpdate(float deltaTime)
{
	switch (gameState)
	{
	case MAIN_MENU :
		if (glfwGetKey(m_Window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			gameState = DIFFICULTY_SELECT; lastTime = 0.0f; pauseTime = 0.4f; isHardMode = false;
		}
		if ((glfwGetKey(m_Window, GLFW_KEY_C) == GLFW_PRESS) && lastTime > pauseTime) {
			gameState = CREDITS; lastTime = 0.0f; pauseTime = 0.4f;
		}
		Renderer::CreateQuad({ 1305.0f, 1004.0f }, { 650, 500 }, menu);
		break;
	case CREDITS :
		if ((glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS) && lastTime > pauseTime) {
			gameState = MAIN_MENU; lastTime = 0.0f; 
		}
		Renderer::CreateQuad({ 1305.0f, 1004.0f }, { 650, 500 }, credits);
		break;
	case DIFFICULTY_SELECT:
		Renderer::CreateQuad({ 1305.0f, 1004.0f }, { 650, 500 }, difficulty);
		if (glfwGetKey(m_Window, GLFW_KEY_UP) == GLFW_PRESS) {
			isHardMode = false;
		}
		if (glfwGetKey(m_Window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			isHardMode = true;
		}
		if (isHardMode == true) Renderer::CreateQuad({ 200.0f, 100.0f }, { 340, 430 }, point);
		else Renderer::CreateQuad({ 200.0f, 100.0f }, { 340, 600 }, point);
		if ((glfwGetKey(m_Window, GLFW_KEY_SPACE) == GLFW_PRESS) && lastTime > pauseTime)
		{
			gameState = INFO_SCREEN; lastTime = 0.0f; pauseTime = 0.4f;
		}
		break;
	case INFO_SCREEN:
		if ((glfwGetKey(m_Window, GLFW_KEY_SPACE) == GLFW_PRESS) && lastTime > pauseTime) {
			gameState = GAME_SCREEN; pauseTime = 0.2f;
		}
		Renderer::CreateQuad({ 1305.0f, 1004.0f }, { 650, 500 }, info);
		break;
	case GAME_SCREEN :
		if (isGameOver == false)
		{
			if (isPause == false)
			{
				if (glfwGetKey(m_Window, GLFW_KEY_R) == GLFW_PRESS)
				{
					EntityManager::cleanEntity();
					onCreate();
				}
				spawner->onUpdate(deltaTime);
				EntityManager::updateEntities(deltaTime, m_Window);
				Renderer::CreateQuad({ 1305.0f, 1004.0f }, { 650, 500 }, hud);
				for (int number = 0; number < Player::numberOfLifes; number++)
				{
					Renderer::CreateQuad({ 80, 80 }, { 1240 - (number * 80), 825 }, hp);
				}
			}
			else
			{
				Renderer::CreateQuad({ 1305.0f, 1004.0f }, { 650, 500 }, hud);
				for (int number = 0; number < Player::numberOfLifes; number++)
				{
					Renderer::CreateQuad({ 80, 80 }, { 1240 - (number * 80), 825 }, hp);
				}
				Renderer::CreateQuad({ 1300.0f, 1000.0f }, { 650, 500 }, pause);
			}
		}
		else
		{
			Renderer::CreateQuad({ 1305.0f, 1004.0f }, { 650, 500 }, hud);
			Renderer::CreateQuad({ 1300.0f, 1000.0f }, { 650, 500 }, gameover);
			if (glfwGetKey(m_Window, GLFW_KEY_R) == GLFW_PRESS)
			{
				EntityManager::cleanEntity();
				onCreate();
			}
		}

		if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS && lastTime > pauseTime)
		{
			if (isPause == false) isPause = true;
			else isPause = false;
			lastTime = 0.0f;
		}

		if (isGameWon == true) {
			if(lastTimeAfterDeath > reloadTimeAfterDeath)
				gameState = WIN_SCREEN;
			lastTimeAfterDeath += deltaTime;
		}


		break;
	case WIN_SCREEN :
		pauseTime = 1.0f;
		Renderer::CreateQuad({ 1300.0f, 1000.0f }, { 650, 500 }, winscreen);
		if (lastTime > pauseTime)
		{

			lastTime1 += deltaTime;
			Renderer::CreateQuad({ 1300.0f, 1000.0f }, { 650, 500 }, winscreen1);
			if (lastTime1 > pauseTime)
			{
				lastTime = 0.0f;
				lastTime1 = 0.0f;
			}
		}
		break;
	}

	lastTime += deltaTime;
	
	//std::cout << 1 / deltaTime << std::endl;
}
