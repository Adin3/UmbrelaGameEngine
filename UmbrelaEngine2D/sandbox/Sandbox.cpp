#include "Sandbox.h"
#include "../entity/EntityManager.h"
#include "../misc/Input.h"

glm::vec2 pos(250.0f, 250.0f);

Sandbox::Sandbox(const char* string, const int width, const int height) 
	: Application(string, width, height)
{
	m_height = height+10;
	m_width = width+10;
	m_size = {m_width / 3 , m_height};
}

void Sandbox::onCreate()
{
	
}

void Sandbox::onUpdate(float deltaTime)
{
	if (Input::MouseInput(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS)) {
		double posx, posy;
		glfwGetCursorPos(Application::GetWindow(), &posx, &posy);
		std::cout << posx << " " << posy << std::endl;
	}
	
	if (Input::KeyboardInput(GLFW_KEY_R, GLFW_REPEAT)) {
		Renderer::CreateQuad(glm::vec2(m_size), glm::vec2(m_size.x / 2, m_size.y / 2), glm::vec3(1.0f, 0.0f, 0.0f));
	}
	if (Input::KeyboardInput(GLFW_KEY_G, GLFW_REPEAT)) {
		Renderer::CreateQuad(glm::vec2(m_size), glm::vec2(m_size.x / 2 + m_size.x, m_size.y / 2), glm::vec3(0.0f, 1.0f, 0.0f));
	}
	if (Input::KeyboardInput(GLFW_KEY_B, GLFW_REPEAT)) {
		Renderer::CreateQuad(glm::vec2(m_size), glm::vec2(m_size.x / 2 + 2 * m_size.x, m_size.y / 2), glm::vec3(0.0f, 0.0f, 1.0f));
	}
}

void Sandbox::onDestory()
{

}
