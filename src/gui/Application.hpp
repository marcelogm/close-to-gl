#pragma once

#include "vgl.h"
#include "../services/services.hpp"
#include "../services/render/render.hpp"
#include "../data/data.hpp"

class Application {
private:
	GLFWwindow* window;
	ModelFactory* factory;
	OpenGLRenderer* renderer;
public:
	void init();
	void loop();
	void detroy();
	~Application();
};