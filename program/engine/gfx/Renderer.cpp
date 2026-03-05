#include "Renderer.h"
#include "../misc/Camera.h"

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

Renderer::Renderer()
{
}

Renderer::~Renderer()
{

}

void Renderer::GL_ENABLE()
{
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
    //glEnable(GL_FRAMEBUFFER_SRGB);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_MULTISAMPLE);
}

void Renderer::Draw(float deltaTime, Scene& scene, std::shared_ptr<Shader> overrideShader)
{
    int width, height;
    glfwGetWindowSize(m_context, &width, &height);
    glm::mat4 projection = scene.camera.getProjectionMatrix((float)width / (float)height);
    glm::mat4 view = scene.camera.getViewMatrix();
    glm::vec3 cameraPos = scene.camera.position;

    for (auto& obj : scene.objects) {
        auto shader = overrideShader ? overrideShader : obj.shader;
        shader->use();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, obj.position);
        model = glm::rotate(model, glm::radians(obj.rotationAngle), obj.rotationAxis);
        model = glm::scale(model, obj.scale);

        shader->setMat4("model", model);
        shader->setMat4("view", view);
        shader->setMat4("perspective", projection);
        shader->setVec3("viewPos", 1, cameraPos);

        if (!scene.lights.empty()) {
            auto& light = scene.lights[0];
            shader->setVec3("light.position", 1, light.position);
            shader->setVec3("light.ambient", 1, light.ambient);
            shader->setVec3("light.diffuse", 1, light.diffuse);
            shader->setVec3("light.specular", 1, light.specular);
            shader->setFloat("light.constant", light.constant);
            shader->setFloat("light.linear", light.linear);
            shader->setFloat("light.quadratic", light.quadratic);

            shader->setVec3("material.diffuse", 1, { 0.0f, 0.50980392f, 0.50980392f });
            shader->setVec3("material.specular", 1, { 0.50196078f, 0.50196078f, 0.50196078f });
            shader->setFloat("material.shininess", 32.0f);
        }

        obj.model->Draw(shader);

    }
}

void Renderer::Clear(float color[3])
{
	glClearColor(color[0], color[1], color[2], 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
