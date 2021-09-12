#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <array>

#include "../vendor/stb_image.h"
#include "../gfx/graphics.h"
#include "Init.h"
#include "Application.h"
#include "../game/game.h"

const int WND_WIDTH = 1300;
const int WND_HEIGHT = 1000;
//unsigned int tudy = TextureManager::LoadTexture("gfx/img/sprites/enemies/tposetudy.png");

int main()
{
	std::cout 
	<< "Game made with opengl for the olcCodeJam2021\n" 
	<< " \n"
	<< "I hope you'll enjoy it\n"
	<< ":)"
	<< "\n";
	Application* app = new Game("Precognition", WND_WIDTH, WND_HEIGHT);
	app->Run();

	delete app;
	return 1;
}
