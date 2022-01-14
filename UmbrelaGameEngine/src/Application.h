#pragma once
#include "../gfx/graphics.h"
#include "../gfx/Renderer.h"
#include <memory>
#include <GLFW/glfw3.h>
#include "../misc/Input.h"
#include <string>

class Renderer;

class Application {
private:
	float m_deltaTime;
	float m_lastFrame;
	unsigned int m_height;
	unsigned int m_width;
	std::string title;
public:
	 Application(const char* string, const int width, const int height);
	 virtual ~Application();
	 void Run();
	 void GetDeltaTime();
	 std::string ChangeTitle();
	 virtual void onCreate() { }
	 virtual void onUpdate(float deltaTime) { }
	 virtual void onDestory() { }
	 static GLFWwindow* GetWindow();
protected:
	static GLFWwindow* m_Window;
	std::shared_ptr<Renderer> m_Context;
};