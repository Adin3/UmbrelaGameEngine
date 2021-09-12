#include "Camera.h"
#include "../gfx/graphics.h"

Camera::Camera()
{
	m_cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
	m_position = glm::vec2(2.0f, 2.0f);
	m_perspectiveOrtho = glm::ortho(0.0f, 1300.0f, 0.0f, 1000.0f);
}

Camera::~Camera()
{

}

glm::mat4 Camera::getView(GLFWwindow* window, float deltaTime)
{
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-m_position, 0.0f));
	m_pv = m_perspectiveOrtho * view;
	return m_pv;
}
