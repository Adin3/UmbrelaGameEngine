// Entity.h
#pragma once
#include "../gfx/Model.h"
#include "../shader/shader.h"

class Entity
{
protected:
    std::string name;
    std::shared_ptr<Model> model;
    std::shared_ptr<Shader> shader;
    glm::vec3 position = glm::vec3(0.0f);
    glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    glm::vec3 scale = glm::vec3(1.0f);

public:
    const std::string& GetName() const { return name; }
    void SetName(const std::string& n) { name = n; }

    std::shared_ptr<Model> GetModel() const { return model; }
    void SetModel(std::shared_ptr<Model> m) { model = m; }

    std::shared_ptr<Shader> GetShader() const { return shader; }
    void SetShader(std::shared_ptr<Shader> s) { shader = s; }

    const glm::vec3& GetPosition() const { return position; }
    void SetPosition(const glm::vec3& p) { position = p; }

    const glm::quat& GetRotation() const { return rotation; }
    void SetRotation(const glm::quat& r) { rotation = r; }

    const glm::vec3& GetScale() const { return scale; }
    void SetScale(const glm::vec3& s) { scale = s; }

    glm::mat4 GetTransform() const;

    virtual void Update(float deltaTime) {}
    virtual void Draw() {}
};

struct LightObject : public Entity
{
    glm::vec3 color = glm::vec3(1.0f);
    float intensity = 1.0f;
};