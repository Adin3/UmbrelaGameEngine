#include "Camera.h"
#include "../gfx/graphics.h"
#include "../src/Application.h"
#include "Input.h"

Camera::Camera(float width, float height)
{
	m_cameraPos3D = glm::vec3(0.0f, 0.0f, 0.0f);
	m_cameraPos2D = glm::vec3(10.0f, 10.0f, 0.0f);
	m_perspectiveOrtho = glm::ortho(0.0f, width, 0.0f, height);
}

Camera::~Camera()
{

}

glm::mat4 Camera::getView(float deltaTime)
{
	float speed = 250.0f * deltaTime;
	if(Input::KeyboardInput(GLFW_KEY_KP_8, GLFW_REPEAT))
		m_cameraPos2D.y -= speed;
	if (Input::KeyboardInput(GLFW_KEY_KP_5, GLFW_REPEAT))
		m_cameraPos2D.y += speed;
	if (Input::KeyboardInput(GLFW_KEY_KP_4, GLFW_REPEAT))
		m_cameraPos2D.x += speed;
	if (Input::KeyboardInput(GLFW_KEY_KP_6, GLFW_REPEAT))
		m_cameraPos2D.x -= speed;

	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-m_cameraPos2D));
	m_pv = m_perspectiveOrtho * view;
	return m_pv;
}
