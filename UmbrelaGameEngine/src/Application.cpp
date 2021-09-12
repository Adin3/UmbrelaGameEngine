#include "Application.h"
#include "Init.h"

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_GRAVE_ACCENT) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

Application::Application(const char* string, const int width, const int height)
{
	m_Window = Init(string, width, height);
	m_Context = std::make_shared<Renderer>();
	m_Camera = std::make_shared<Camera>();
}

Application::~Application()
{
	glfwTerminate();
}

void Application::Run()
{
	m_Context->Clear();
	onCreate();
	while (!glfwWindowShouldClose(m_Window))
	{
		GetDeltaTime();
		processInput(m_Window);
		m_Context->Clear();
		Renderer::BeginBatch();
		m_Context->Draw(m_Camera->getView(m_Window, m_deltaTime));
		onUpdate(m_deltaTime);
		Renderer::EndBatch();
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}
}

void Application::GetDeltaTime()
{
	float currentFrame = glfwGetTime();
	m_deltaTime = currentFrame - m_lastFrame;
	m_lastFrame = currentFrame;
}
