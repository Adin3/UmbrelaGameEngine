#pragma once
#include "Init.h"
#include <string>

class Window {
private:
    GLFWwindow* window;
    int width,  height;
    std::string title;

public:
    Window(int width, int height, const char* title);
    ~Window();

    bool ShouldClose() const;
    void PollEvents() const;
    void SwapBuffers() const;
    void GetSize(int& w, int& h) const;

    GLFWwindow* GetWindowContext() { return window;};
    GLFWwindow* GetHandle() const { return window; }
};