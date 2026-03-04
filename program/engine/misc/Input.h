#pragma once
#include <GLFW/glfw3.h>
#include <unordered_map>

struct KeyProp {
    bool current, previous;
};

class Input {
private:
    static GLFWwindow* windowContext;
    static std::unordered_map<int, KeyProp> keyList;

public:
    Input(GLFWwindow* ctx);
    static void Update();
    static bool KeyboardInput(int key, int state);
    static bool MouseInput(int button, int state);
};