#include "Renderer.h"

bool firstMouse = true;
float lastX = 400, lastY = 300;
float yaw = -90.0f, pitch = 0.0f;
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

Renderer::Renderer()
{
	ourShader = std::make_shared<Shader>("shader/rec/vshader.vs", "shader/rec/fshader.fs");

	float vertices[] = {
	   -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f, 1.0f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,  0.0f, 0.0f,

	   -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f,
	   -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f,  0.0f, 0.0f,

	   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f,  1.0f, 0.0f,
	   -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f, 1.0f,  0.0f, 1.0f,
	   -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f, 1.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f,

	   -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f, 1.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f,  1.0f, 0.0f,
	   -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f, 0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f,

	   -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f, 1.0f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f,  1.0f, 0.0f,
	   -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f, 0.0f,
	   -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f, 1.0f,  0.0f, 1.0f
	};


	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
	glEnableVertexAttribArray(2);

	unsigned int texture = TextureManager::LoadTexture("img/cat.png");
	unsigned int texture1 = TextureManager::LoadTexture("img/cat.png");

	ourShader->use();
	ourShader->setInt("ourTexture", 0);
	ourShader->setInt("ourTexture1", 1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);
}

Renderer::~Renderer()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Renderer::GL_ENABLE()
{
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::Draw(int w_width, int w_height, float deltaTime)
{
	GLFWwindow* window = Application::GetWindow();
	glfwSetCursorPosCallback(window, mouse_callback);
	glm::mat4 view;
	glm::mat4 perspective = glm::mat4(1.0f);
	perspective = glm::perspective(glm::radians(45.0f), (float)1000 / (float)1000, -1.0f, 1.0f);
	const float radius = 10.0f;
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	perspective = glm::perspective(glm::radians(60.0f), (float)w_width / (float)w_height, 0.1f, 100.0f);

	ourShader->use();
	glBindVertexArray(VAO);
	for (unsigned int i = 0; i != 10; ++i)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		float angle = 10.0f + 10.0f * i;
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		glm::mat4 mvp = perspective * view * model;
		ourShader->setMat4("model", mvp);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	const float cameraSpeed = 2.5 * deltaTime; // adjust accordingly
	if (Input::KeyboardInput(GLFW_KEY_W, GLFW_REPEAT))
		cameraPos += cameraSpeed * cameraFront;
	if (Input::KeyboardInput(GLFW_KEY_S, GLFW_REPEAT))
		cameraPos -= cameraSpeed * cameraFront;
	if (Input::KeyboardInput(GLFW_KEY_A, GLFW_REPEAT))
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (Input::KeyboardInput(GLFW_KEY_D, GLFW_REPEAT))
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void Renderer::Clear()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
}

