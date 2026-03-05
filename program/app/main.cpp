#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <array>
#include "../vendor/stb_image.h"
#include "../gfx/graphics.h"
#include "../gfx/Renderer.h"
#include "App.h"

const int WND_WIDTH = 1200;
const int WND_HEIGHT = 800;

void frameBuffer_size_callBack(GLFWwindow* window, GLuint height, GLuint width);

int main()
{
	App* app = new App("Umbrela3D", WND_WIDTH, WND_HEIGHT);
	app->Run();
	
	delete app;
}

void frameBuffer_size_callBack(GLFWwindow* window, GLuint height, GLuint width)
{
	glViewport(0, 0, height, width);
}
