#pragma once
#include "../gfx/graphics.h"
#include "../src/Application.h"

class Sandbox : public Application {
private:

public:
	Sandbox(const char* window, const int width, const int height);
	void onCreate();
	void onUpdate(float deltaTime);
	void onDestory();
};