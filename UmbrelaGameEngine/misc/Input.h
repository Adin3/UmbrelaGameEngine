#pragma once
#include "../src/Application.h"
#include <map>

struct KeyProp {
	bool current, previous;
};

class Input {
private:

public:
	static std::unordered_map<int, KeyProp> keyList;
	static bool KeyboardInput(int key, int state);
	static bool MouseInput(int key, int state);
};