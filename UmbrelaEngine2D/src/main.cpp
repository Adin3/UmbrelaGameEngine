#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <array>

#include "../vendor/stb_image.h"
#include "../gfx/graphics.h"
#include "Init.h"
#include "Application.h"
#include "../sandbox/Sandbox.h"

const int WND_WIDTH = 750;
const int WND_HEIGHT = 750;

int main()
{
	Application* app = new Sandbox("Physics", WND_WIDTH, WND_HEIGHT);
	app->Run();

	delete app;
	return 1;
}
