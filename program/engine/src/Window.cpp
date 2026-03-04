#include "Window.h"

Window::Window(int width, int height, const char* title)
    : width(width), height(height), title(title)
{
    window = Init(title, width, height);
}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool Window::ShouldClose() const {
    return glfwWindowShouldClose(window);
}

void Window::PollEvents() const {
    glfwPollEvents();
}

void Window::SwapBuffers() const {
    glfwSwapBuffers(window);
}

void Window::GetSize(int& w, int& h) const {
    glfwGetFramebufferSize(window, &w, &h);
}