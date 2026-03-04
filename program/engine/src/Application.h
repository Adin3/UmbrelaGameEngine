#pragma once
#include "../vendor/imgui/imgui.h"
#include "../vendor/imgui/imgui_impl_glfw.h"
#include "../vendor/imgui/imgui_impl_opengl3.h"

#include "../gfx/Renderer.h"
#include "../misc/Input.h"
#include "Path.h"
#include "Window.h"
#include <memory>
#include <string>

class Application {
public:
    Application(const char* title, int width, int height);
    virtual ~Application();
    void Run();

    virtual void onCreate() {}
    virtual void onUpdate(float dt) {}
    virtual void onDestroy() {}

    Window& GetWindow() { return *m_Window; }

protected:
    std::unique_ptr<Window>   m_Window;
    std::unique_ptr<Input>    m_input;
    std::shared_ptr<Renderer> m_Context;

private:
    float       m_deltaTime = 0.0f;
    float       m_lastFrame = 0.0f;
    int         m_width, m_height;
    std::string m_title;

    void InitImGui();
    void ShutdownImGui();
    void GetDeltaTime();
    std::string BuildTitle();
    GLFWwindow* ctx() { return m_Window->GetWindowContext(); }
};