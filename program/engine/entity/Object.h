// Object.h
#pragma once
#include <reactphysics3d/reactphysics3d.h>
#include "Entity.h"

class Object : public Entity
{
protected:
    rp3d::BodyType objectType = rp3d::BodyType::STATIC;
    rp3d::RigidBody* body = nullptr;

public:

    void createRigidBody(rp3d::PhysicsWorld* world, rp3d::PhysicsCommon& physicsCommon, rp3d::BodyType objectType)
    {
        glm::vec3 pos = GetPosition();
        glm::vec3 scale = GetScale();
        body = world->createRigidBody(
            rp3d::Transform(rp3d::Vector3(pos.x, pos.y, pos.z), rp3d::Quaternion::identity()));
        body->setType(objectType);
        rp3d::BoxShape* cubeShape = physicsCommon.createBoxShape(rp3d::Vector3(scale.x, scale.y, scale.z));
        body->addCollider(cubeShape, rp3d::Transform::identity());
    }

    void SetWorldPosition(glm::vec3 pos)
    {
        if (body) {
            rp3d::Transform t = body->getTransform();
            t.setPosition(rp3d::Vector3(pos.x, pos.y, pos.z));
            body->setTransform(t);
        }
    }

    glm::vec3 GetWorldPosition() const
    {
        if (body)
        {
            rp3d::Vector3 pos = body->getTransform().getPosition();
            return glm::vec3(pos.x, pos.y, pos.z);
        }
        return Entity::GetPosition();
    }

    glm::mat4 GetTransform()
    {
        if (body)
        {
            rp3d::Transform t = body->getTransform();
            rp3d::Vector3 pos = t.getPosition();
            rp3d::Quaternion rot = t.getOrientation();

            glm::mat4 m = glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, pos.z));
            m *= glm::mat4_cast(glm::quat(rot.w, rot.x, rot.y, rot.z));
            m *= glm::scale(glm::mat4(1.0f), GetScale());
            return m;
        }
        return glm::mat4(1.0f);
    }

    void Draw() override
    {
        if (model && shader)
        {
            shader->setMat4("model", GetTransform());
            model->Draw(shader);
        }
    }
};