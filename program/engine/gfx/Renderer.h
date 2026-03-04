#pragma once
#include "graphics.h"
#include "GLFW/glfw3.h"
#include "Model.h"
#include "../misc/Camera.h"
#include "../scene/Scene.h"

class Renderer {
private:
	GLFWwindow* m_context;
public:
	Renderer();
	~Renderer();

	void GL_ENABLE();
	void Draw(float deltaTime, Scene& scene, std::shared_ptr<Shader> overrideShader);
	void SetWindow(GLFWwindow* window) { m_context = window; }
	void Clear(float color[3]);
};