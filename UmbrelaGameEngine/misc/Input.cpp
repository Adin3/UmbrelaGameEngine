#include "Input.h"

std::unordered_map<int, KeyProp> Input::keyList;

bool Input::KeyboardInput(int key, int state)
{
    if (keyList.find(key) == keyList.end()) {
        keyList.insert({ key,{ 0 }});
    }

    if (glfwGetKey(Application::GetWindow(), key) == GLFW_PRESS)
        keyList[key].current = true;

    switch (state)
    {
    case GLFW_PRESS :
        if (keyList[key].current == true && keyList[key].previous == false)
            return true;
        break;
    case GLFW_REPEAT :
        if (keyList[key].current == true && keyList[key].previous == true)
            return true;
        break;
    case GLFW_RELEASE:
        if (keyList[key].current == false && keyList[key].previous == true)
            return true;
        break;
    }

    return false;
}

bool Input::MouseInput(int key, int state)
{
    if (glfwGetMouseButton(Application::GetWindow(), key) == state)
        return true;
    return false;
}
