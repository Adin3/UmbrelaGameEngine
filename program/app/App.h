#pragma once
#include "../Engine/src/Application.h"
#include "../scene/Scene.h"
#include "../engine/src/Path.h"
#include <reactphysics3d/reactphysics3d.h>

class App : public Application {
public:
    App(const char* title, int width, int height)
        : Application(title, width, height) {}

    void onCreate()         override;
    void onUpdate(float dt) override;
    void onDestroy()        override;

    std::shared_ptr<Scene> scene;
    rp3d::PhysicsCommon    physicsCommon;
    rp3d::PhysicsWorld*    world;
    rp3d::RigidBody*       cubeBody;
    rp3d::RigidBody*       planeBody;
    float                  physicsAccumulator;
};