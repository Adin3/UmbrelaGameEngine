#include "App.h"
#include "../engine/gfx/Model.h"
#include "../engine/shader/shader.h"

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void App::onCreate()
{
    scene = std::make_shared<Scene>("Main");

    SceneObject sponza;
    sponza.name = "sponza";
    sponza.model = std::make_shared<Model>(MODEL("sponza/Sponza.gltf"));
    sponza.shader = std::make_shared<Shader>(
        SHADER("vshader.vs"), 
        SHADER("fshader.fs"));
    sponza.scale = glm::vec3(0.01f);
    scene->AddObject(sponza);

    Light sun;
    sun.position = glm::vec3(0.25f, 4.75f, -0.30f);
    scene->AddLight(sun);

    scene->camera = Camera();

    GLFWwindow* win = GetWindow().GetWindowContext();
    glfwSetWindowUserPointer(win, this);
    glfwSetCursorPosCallback(win, mouse_callback);

    m_Context->SetWindow(win);
}

void App::onUpdate(float dt)
{
    m_Context->Draw(dt, *scene, nullptr);

    scene->camera.processKeyboard(dt);

    // imgui specific to this app
    ImGui::Begin("My App");
    ImGui::Text("FPS: %d", (int)(1.0f / dt));
    ImGui::End();
}

void App::onDestroy()
{
    scene.reset();
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

    App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
    if (!app || !app->scene) return;

	static bool firstMouse = true;
	static float lastX = 400.0f, lastY = 300.0f;

	if (Input::KeyboardInput(GLFW_KEY_LEFT_ALT, GLFW_REPEAT)) return;

	if (firstMouse) {
		lastX = xpos; lastY = ypos;
		firstMouse = false;
	}

	float xoffset = (xpos - lastX);
	float yoffset = -(ypos - lastY); // inverted Y
	lastX = xpos;
	lastY = ypos;

	app->scene->camera.processMouse(xoffset, yoffset);
}