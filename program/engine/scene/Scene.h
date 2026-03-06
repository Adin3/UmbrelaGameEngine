#pragma once
#include "../shader/Shader.h"
#include "../gfx/Model.h"
#include "../misc/Camera.h"
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <memory>
#include "entity/Object.h"

struct Light {
    glm::vec3   position = glm::vec3(0.0f);
    glm::vec3   ambient = glm::vec3(0.1f);
    glm::vec3   diffuse = glm::vec3(0.7f);
    glm::vec3   specular = glm::vec3(1.0f);
    float       constant = 1.0f;
    float       linear = 0.045f;
    float       quadratic = 0.0075f;
};

class Scene {
public:
    Camera                                      camera;
    std::vector<std::shared_ptr<Object>>        objects;
    std::vector<std::shared_ptr<Light>>         lights;
    std::string                                 name;

    Scene(const std::string& name) : name(name) {}

    void AddObject(std::shared_ptr<Object> obj) { objects.push_back(obj); }
    void AddLight(std::shared_ptr<Light> light) { lights.push_back(light); }

    std::shared_ptr<Object> GetObject(const std::string& name)
    {
        for (auto& obj : objects)
            if (obj->GetName() == name) return obj;
        return nullptr;
    }
};