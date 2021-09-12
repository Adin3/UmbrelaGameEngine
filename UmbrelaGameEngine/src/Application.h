#pragma once
#include "../gfx/graphics.h"
#include <memory>
#include <GLFW/glfw3.h>
#include "../misc/Camera.h"

class Application {
private:
	float m_deltaTime;
	float m_lastFrame;
public:
	 Application(const char* string, const int width, const int height);
	 virtual ~Application();
	 void Run();
	 void GetDeltaTime();
	 virtual void onCreate() { }
	 virtual void onUpdate(float deltaTime) { }
	 virtual void onDestory() { }


protected:
	GLFWwindow* m_Window;
	std::shared_ptr<Renderer> m_Context;
	std::shared_ptr<Camera> m_Camera;
};