#include "Renderer.h"

bool firstMouse = true;
float lastX = 400, lastY = 300;
float yaw = -90.0f, pitch = 0.0f;
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

glm::vec3 cameraPos = glm::vec3(0.0f, 0.5f, 5.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);


glm::vec3 cubePositions[] = {
	glm::vec3(0.25f, 4.75f, -0.30f),
	//glm::vec3(0.0f,  0.0f,  0.0f),
	//glm::vec3(-1.5f, -2.2f, -2.5f),
	//glm::vec3(-3.8f, -2.0f, -12.3f),
	//glm::vec3(2.4f, -0.4f, -3.5f),
	//glm::vec3(-1.7f,  3.0f, -7.5f),
	//glm::vec3(1.3f, -2.0f, -2.5f),
	//glm::vec3(1.5f,  2.0f, -2.5f),
	//glm::vec3(1.5f,  0.2f, -1.5f),
	//glm::vec3(-1.3f,  1.0f, -1.5f)
};

Renderer::Renderer()
{
	ourShader = std::make_shared<Shader>("shader/rec/vshader.vs", "shader/rec/fshader.fs");
	lightShader = std::make_shared<Shader>("shader/rec/lightvshader.vs", "shader/rec/lightfshader.fs");
	ourModel = std::make_shared<Model>("img/sponza/Sponza.gltf");

	//diffuseMap = TextureManager::LoadTexture("img/container2.png");
	//specularMap = TextureManager::LoadTexture("img/container4.png");

	float vertices[] = {
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  //0.0f,  0.0f,
	    0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  //1.0f,  0.0f,
	    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  //1.0f,  1.0f,
	    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  //1.0f,  1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  //0.0f,  1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  //0.0f,  0.0f,
	   											  //
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   //0.0f,  0.0f,
	    0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,	  //1.0f,  0.0f,
	    0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,	  //1.0f,  1.0f,
	    0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,	  //1.0f,  1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,	  //0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,	  //0.0f,  0.0f,
	   											  //
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  //0.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  //1.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  //1.0f,  1.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  //1.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  //0.0f,  1.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  //0.0f,  0.0f,
	   											  //
	    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  //0.0f,  0.0f,
	    0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  //1.0f,  0.0f,
	    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  //1.0f,  1.0f,
	    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  //1.0f,  1.0f,
	    0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  //0.0f,  1.0f,
	    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  //0.0f,  0.0f,
	   											  //
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  //0.0f,  0.0f,
	    0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  //1.0f,  0.0f,
	    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  //1.0f,  1.0f,
	    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  //1.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  //0.0f,  1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  //0.0f,  0.0f,
	   											  //
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  //0.0f,  0.0f,
	    0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  //1.0f,  0.0f,
	    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  //1.0f,  1.0f,
	    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  //1.0f,  1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  //0.0f,  1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  //0.0f,  0.0f,
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	/*glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);*/

	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(1);

	ourShader->use();
	//ourShader->setVec3("lightColor", 1, glm::vec3(1.0f, 1.0f, 1.0f));
	//ourShader->setVec3("objectColor", 1, glm::vec3(1.0f, 0.5f, 0.31f));
	//ourShader->setInt("material.diffuse", 0);
	//ourShader->setInt("material.specular", 1);
}

Renderer::~Renderer()
{
	glDeleteVertexArrays(1, &lightVAO);
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
	//std::cout << cameraPos.x << " "<<cameraPos.y << " "<<cameraPos.z <<std::endl;
	GLFWwindow* window = Application::GetWindow();
	if(!Input::KeyboardInput(GLFW_KEY_LEFT_ALT, GLFW_REPEAT))
		glfwSetCursorPosCallback(window, mouse_callback);

	glm::mat4 view;
	const float radius = 10.0f;
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	glm::mat4 perspective = glm::mat4(1.0f);
	perspective = glm::perspective(glm::radians(60.0f), (float)w_width / (float)w_height, 0.1f, 100.0f);
	//cubePositions[1].x = 1.0f + sin(glfwGetTime()) * 2.0f;
	//cubePositions[1].y = sin(glfwGetTime() / 2.0f) * 1.0f;

	ourShader->use();
	glBindVertexArray(VAO);

	glm::mat4 model = glm::mat4(1.0f);
    float angle = sin(glfwGetTime()) * 0;
	glm::vec3 lightColor = {1.0f, 1.0f, 1.0f};
		model = glm::translate(model, cubePositions[1]);
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.01f));
		//model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		//ourShader->setVec3("lightColor", 1, glm::vec3(1.0f, 0.0f, 1.0f));
		//ourShader->setVec3("objectColor", 1, glm::vec3(1.0f, 0.5f, 0.31f));
		ourShader->setVec3("viewPos", 1, cameraPos);
		ourShader->setVec3("light.position", 1, cubePositions[0]);
		//lightColor.x = sin(glfwGetTime() * 2.0f);
		//lightColor.y = sin(glfwGetTime() * 0.7f);
		//lightColor.z = sin(glfwGetTime() * 1.3f);
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.7f); // decrease the influence
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.35f); // low influence
		ourShader->setVec3("light.ambient", 1, ambientColor);
		ourShader->setVec3("light.diffuse", 1, diffuseColor);
		ourShader->setVec3("light.specular", 1, { 1.0f, 1.0f, 1.0f });
		ourShader->setFloat("light.constant", 1.0f);
		ourShader->setFloat("light.linear", 0.045f);
		ourShader->setFloat("light.quadratic", 0.0075f);
		//ourShader->setVec3("material.ambient", 1, { 0.0f, 0.1f, 0.06f });
		ourShader->setVec3("material.diffuse", 1, { 0.0f, 0.50980392f, 0.50980392f });
		ourShader->setVec3("material.specular", 1, { 0.50196078f, 0.50196078f, 0.50196078f });
		ourShader->setFloat("material.shininess", 32.0f);
		ourShader->setMat4("model", model);
		ourShader->setMat4("view", view);
		ourShader->setMat4("perspective", perspective);
		ourModel->Draw(ourShader);
		//glDrawArrays(GL_TRIANGLES, 0, 36);

	lightShader->use();
	glBindVertexArray(lightVAO);
	model = glm::mat4(1.0f);
	model = glm::translate(model, cubePositions[0]);
	model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
	angle = sin(glfwGetTime()) * 100;
	model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
	lightShader->setMat4("model", model);
	lightShader->setMat4("view", view);
	lightShader->setMat4("perspective", perspective);
	lightShader->setVec3("lightColor", 1, lightColor);

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, diffuseMap);
	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, specularMap);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	float cameraSpeed = 2.5 * deltaTime; // adjust accordingly
	if (Input::KeyboardInput(GLFW_KEY_LEFT_SHIFT, GLFW_REPEAT))
		cameraSpeed = 7.5 * deltaTime;
	if (Input::KeyboardInput(GLFW_KEY_W, GLFW_REPEAT))
		cameraPos += cameraSpeed * cameraFront;
	if (Input::KeyboardInput(GLFW_KEY_S, GLFW_REPEAT))
		cameraPos -= cameraSpeed * cameraFront;
	if (Input::KeyboardInput(GLFW_KEY_A, GLFW_REPEAT))
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (Input::KeyboardInput(GLFW_KEY_D, GLFW_REPEAT))
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (Input::KeyboardInput(GLFW_KEY_SPACE, GLFW_REPEAT))
		cameraPos += cameraUp * cameraSpeed;
	if (Input::KeyboardInput(GLFW_KEY_LEFT_CONTROL, GLFW_REPEAT))
		cameraPos -= cameraUp * cameraSpeed;
}

void Renderer::Clear()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (!Input::KeyboardInput(GLFW_KEY_LEFT_ALT, GLFW_REPEAT))
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
}

