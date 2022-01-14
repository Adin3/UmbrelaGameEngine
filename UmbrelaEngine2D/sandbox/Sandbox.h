#pragma once
#include "../gfx/graphics.h"
#include "../src/Application.h"

class Sandbox : public Application {
private:
	int m_height;
	int m_width;
	glm::vec2 m_size;
	
public:
	Sandbox(const char* window, const int width, const int height);
	void onCreate();
	void onUpdate(float deltaTime);
	void onDestory();
protected:

};