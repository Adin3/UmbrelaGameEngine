#pragma once
#include "../Engine/src/Application.h"
#include "../scene/Scene.h"
#include "../engine/src/Path.h"

class App : public Application {
public:
    App(const char* title, int width, int height)
        : Application(title, width, height) {}

    void onCreate()         override;
    void onUpdate(float dt) override;
    void onDestroy()        override;

    std::shared_ptr<Scene> scene;
};