#pragma once

#include "vgl.h"

class Application {
private:
	GLFWwindow* window;
public:
	void init();
	void loop();
	void detroy();
	~Application();
};