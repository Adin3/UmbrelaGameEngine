#include "../vendor/imgui/imgui.h"
#include "../vendor/imgui/imgui_impl_glfw.h"
#include "../vendor/imgui/imgui_impl_opengl3.h"


#include "Application.h"
#include "Init.h"

GLFWwindow* Application::m_Window;


void processInput(GLFWwindow* window)
{
	for (auto& key : Input::keyList) {
		key.second.previous = key.second.current;
		key.second.current = false;
	}

	if (glfwGetKey(window, GLFW_KEY_GRAVE_ACCENT) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
} 

Application::Application(const char* string, const int width, const int height)
{
	m_Window = Init(string, width, height);
	m_Context = std::make_shared<Renderer>();
	m_Camera = std::make_shared<Camera>(width, height);
}

Application::~Application()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
}

void Application::Run()
{
	m_Context->Clear();
	onCreate();
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init("#version 450");

	while (!glfwWindowShouldClose(m_Window))
	{
		GetDeltaTime();
		glfwSetWindowTitle(m_Window, ChangeTitle().c_str());
		processInput(m_Window);

		m_Context->Clear();

		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		Renderer::BeginBatch();
		m_Context->Draw(m_Camera->getView(m_deltaTime));
		onUpdate(m_deltaTime);
		Renderer::EndBatch();

		/*ImGui::Begin("Setari");
		ImGui::Text("TEXT");
		ImGui::End();*/

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}
}

GLFWwindow* Application::GetWindow()
{
	return m_Window;
}

void Application::GetDeltaTime()
{
	float currentFrame = glfwGetTime();
	m_deltaTime = currentFrame - m_lastFrame;
	m_lastFrame = currentFrame;
}

std::string Application::ChangeTitle()
{
	int FPS = 1 / m_deltaTime;
	std::string str = "Physics - " + std::to_string(FPS); 
	return str;
}