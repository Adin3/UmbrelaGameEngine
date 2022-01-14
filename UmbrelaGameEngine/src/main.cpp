#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <array>
#include "../vendor/stb_image.h"
#include "../gfx/graphics.h"
#include "Init.h"
#include "../gfx/Renderer.h"
#include "Application.h"

const int WND_WIDTH = 1050;
const int WND_HEIGHT = 1050;

void frameBuffer_size_callBack(GLFWwindow* window, GLuint height, GLuint width);

int main()
{
	Application* app = new Application("Umbrela3D", WND_WIDTH, WND_HEIGHT);
	app->Run();

	delete app;
}

void frameBuffer_size_callBack(GLFWwindow* window, GLuint height, GLuint width)
{
	glViewport(0, 0, height, width);
}
