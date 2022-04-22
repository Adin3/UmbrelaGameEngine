#pragma once
#include "graphics.h"
#include "GLFW/glfw3.h"
#include "../misc/Input.h"
#include "Model.h"

class Renderer {
private:
	unsigned int VAO, lightVAO;
	unsigned int VBO, EBO;
	std::shared_ptr<Shader> ourShader;
	std::shared_ptr<Shader> lightShader;
	std::shared_ptr<Model> ourModel;
	unsigned int diffuseMap;
	unsigned int specularMap;
public:
	Renderer();
	~Renderer();
	void GL_ENABLE();
	void Draw(int w_width, int w_height, float deltaTime);
	void Clear();
};