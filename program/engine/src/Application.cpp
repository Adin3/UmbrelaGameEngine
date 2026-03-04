#include "Application.h"
#include "Init.h"

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_GRAVE_ACCENT) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
} 

Application::Application(const char* string, const int width, const int height)
{
	m_Window   = std::make_unique<Window>(width, height, string);
	m_input    = std::make_unique<Input>(ctx());
	m_Context  = std::make_shared<Renderer>();
	m_title    = string;
	m_width	   = width;
	m_height   = height;

	m_Context->GL_ENABLE();
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
	float color[3] = {0.0f, 0.0f, 0.0f};
	float rotCoords[3] = { 0.0f, 0.0f, 0.0f};
	const char* scenes[]{ "Ceainic", "Ghiozdan", "Noise", "Sponza" };
	int speedRotation = 0.0f;
	int indexScene = 0;
	m_Context->Clear(color);
	onCreate();
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(ctx(), true);
	ImGui_ImplOpenGL3_Init("#version 330");

	while (!glfwWindowShouldClose(ctx()))
	{
		GetDeltaTime();
		// glfwSetWindowTitle(ctx(), ChangeTitle().c_str());
		processInput(ctx());
		Input::Update();

		if (!Input::KeyboardInput(GLFW_KEY_LEFT_ALT, GLFW_REPEAT))
			glfwSetInputMode(ctx(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		else
			glfwSetInputMode(ctx(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		
		m_Context->Clear(color);

		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		onUpdate(m_deltaTime);

		ImGui::Begin("Setari");
		ImGui::ColorEdit3("Culoare", color);
		ImGui::SliderInt("Viteza de rotatie", &speedRotation, 0, 100);
		ImGui::SliderFloat("Rotatie X", &rotCoords[0], 0.0f, 1.0f);
		ImGui::SliderFloat("Rotatie Y", &rotCoords[1], 0.0f, 1.0f);
		ImGui::SliderFloat("Rotatie Z", &rotCoords[2], 0.0f, 1.0f);
		ImGui::ListBox("Scena", &indexScene, scenes, IM_ARRAYSIZE(scenes));
		ImGui::Text("TEXT");
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(ctx());
		glfwPollEvents();
	}
}

void Application::GetDeltaTime()
{
	float currentFrame = glfwGetTime();
	m_deltaTime = currentFrame - m_lastFrame;
	m_lastFrame = currentFrame;
}