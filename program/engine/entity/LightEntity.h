#pragma once
#include "Entity.h"

struct LightEntity : Entity
{
    glm::vec3 color = glm::vec3(1.0f);
    float intensity = 1.0f;
};