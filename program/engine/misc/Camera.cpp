#include "Camera.h"
#include <iostream>

Camera::Camera() {
	position   = glm::vec3(-3.0f, 3.5f, 1.0f);
	front      = glm::vec3(0.79116, -0.60237, -0.531637);
	up         = glm::vec3(0.0f, 1.0f, 0.0f);
	yaw        = -90.0f;
	pitch	   = 0.0f;
	lastX	   = 400.0f;
	lastY	   = 300.0f;
	firstMouse = true;
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProjectionMatrix(float aspect) const
{
	return glm::perspective(glm::radians(60.0f), aspect, 0.1f, 100.0f);
}

void Camera::processKeyboard(float deltaTime)
{
	float speed = 2.5f * deltaTime;
	if (Input::KeyboardInput(GLFW_KEY_LEFT_SHIFT, GLFW_REPEAT))
		speed = 7.5f * deltaTime;
	if (Input::KeyboardInput(GLFW_KEY_W, GLFW_REPEAT))
		position += speed * front;
	if (Input::KeyboardInput(GLFW_KEY_S, GLFW_REPEAT))
		position -= speed * front;
	if (Input::KeyboardInput(GLFW_KEY_A, GLFW_REPEAT))
		position -= glm::normalize(glm::cross(front, up)) * speed;
	if (Input::KeyboardInput(GLFW_KEY_D, GLFW_REPEAT))
		position += glm::normalize(glm::cross(front, up)) * speed;
	if (Input::KeyboardInput(GLFW_KEY_SPACE, GLFW_REPEAT))
		position += up * speed;
	if (Input::KeyboardInput(GLFW_KEY_LEFT_CONTROL, GLFW_REPEAT))
		position -= up * speed;
}

void Camera::processMouse(float xoffset, float yoffset) {
	std::cout << "front " << front.x << " " << front.y << " " << front.z << std::endl;
	std::cout << "up " << up.x << " " << up.y << " " << up.z << std::endl;

	xoffset *= 0.1f;
	yoffset *= 0.1f;

	yaw += xoffset;
	pitch += yoffset;

	pitch = glm::clamp(pitch, -89.0f, 89.0f);

	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);
}