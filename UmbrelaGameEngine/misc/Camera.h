#pragma once
#include "../gfx/graphics.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Camera {
private:
	glm::vec3 m_cameraPos3D;
	glm::vec3 m_cameraPos2D;
	glm::mat4 m_perspectiveOrtho;
	glm::mat4 m_pv;
	float m_ZoomLv = 1.0f;
public:
	Camera(float width, float height);
	~Camera();
	glm::mat4 getView(float deltaTime);
};