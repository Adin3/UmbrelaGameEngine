#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

static GLFWwindow* Init(const char* string, const int width, const int height)
{
	if (!glfwInit()) {
		std::cout << "<ERROR> - GLFW FAILURE - INIT.H \n";
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	GLFWwindow* window = glfwCreateWindow(width, height, string, NULL, NULL);
	if (!window) {
		std::cout << "<ERROR> - WINDOW CREATION FAILED - INIT.H \n";
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "<ERROR> - GLAD FAILURE - INIT.H \n";
	}
	return window;
}