#pragma once
#include "graphics.h"
#include "GLFW/glfw3.h"
#include "../misc/Input.h"
#include "Model.h"

class Renderer {
private:
	unsigned int VAO, lightVAO;
	unsigned int VBO, EBO;
	std::shared_ptr<Shader> ObjShader;
	std::shared_ptr<Shader> lightShader;
	std::shared_ptr<Model> ObjModel1;
	std::shared_ptr<Model> ObjModel2;
	std::shared_ptr<Model> ObjModel3;
	std::shared_ptr<Model> ObjModel4;
	unsigned int diffuseMap;
	unsigned int specularMap;
public:
	Renderer();
	~Renderer();
	void GL_ENABLE();
	void Draw(int w_width, int w_height, float deltaTime, int indexScene, int speed, float rotCoords[3]);
	void Clear(float color[3]);
};