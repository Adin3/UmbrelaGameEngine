#pragma once
#include "../gfx/graphics.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Camera {
private:
	glm::vec3 m_cameraPos;
	glm::vec2 m_position;
	glm::mat4 m_perspectiveOrtho;
	glm::mat4 m_pv;
	float m_ZoomLv = 1.0f;
public:
	Camera();
	~Camera();
	glm::mat4 getView(GLFWwindow* window, float deltaTime);
};