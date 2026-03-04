#include "Input.h"
#include<iostream>

GLFWwindow* Input::windowContext = nullptr;
std::unordered_map<int, KeyProp> Input::keyList;

Input::Input(GLFWwindow* ctx) {
    windowContext = ctx;
}

void Input::Update() {
    for (auto& [key, prop] : keyList) {
        prop.previous = prop.current;
        prop.current = false;
    }
}

bool Input::KeyboardInput(int key, int state) {
    keyList.try_emplace(key, KeyProp{ false, false });

    if (glfwGetKey(windowContext, key) == GLFW_PRESS)
        keyList[key].current = true;

    switch (state) {
    case GLFW_PRESS:    return  keyList[key].current && !keyList[key].previous;
    case GLFW_REPEAT:   return  keyList[key].current && keyList[key].previous;
    case GLFW_RELEASE:  return !keyList[key].current && keyList[key].previous;
    }
    return false;
}

bool Input::MouseInput(int button, int state) {
    return glfwGetMouseButton(windowContext, button) == state;
}