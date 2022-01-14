#pragma once
#include "graphics.h"
#include "GLFW/glfw3.h"
#include "../misc/Input.h"

class Renderer {
private:
	unsigned int VBO, VAO, EBO;
	std::shared_ptr<Shader> ourShader;
public:
	Renderer();
	~Renderer();
	void GL_ENABLE();
	void Draw(int w_width, int w_height, float deltaTime);
	void Clear();
};