#pragma once

#include "vgl.h"
#include "../services/services.hpp"
#include "../services/render/render.hpp"
#include "../services/render/close-to-gl/close.hpp"
#include "../services/render/open-gl/open.hpp"
#include "../data/data.hpp"
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

class ImGuiWrapper {
private:
	Camera* camera;
	Config* config;
	static ImGuiWrapper* instance;
	ImGuiWrapper();
	void space();
	void info();
	void debug();
	void shading();
	void render();
public:
	static ImGuiWrapper* getInstance();
	void init(GLFWwindow* window);
	void display();
	void destroy();
};

class Application {
private:
	GLFWwindow* window;
	ModelFactory* factory;
	std::vector<renderer::Renderer*>* renderers;
	ImGuiWrapper* ui;
public:
	void init();
	void loop();
	void detroy();
};

class KeyCommandStrategy {
protected:
	Camera* camera;
	Config* config;
	bool isPressing(int action);
	float getSensibility();
public:
	KeyCommandStrategy();
	virtual bool matches(int key, int action) = 0;
	virtual void apply() = 0;
};

class KeyStrategyService {
private:
	std::vector<KeyCommandStrategy*>* strategies;
	static KeyStrategyService* instance;
	KeyStrategyService();
public:
	void apply(int, int);
	static KeyStrategyService* getInstance();
};

class MouseService {
private:
	bool first = true;
	double lastY;
	double lastX;
	Camera* camera;
	Config* config;
	static MouseService* instance;
	MouseService();
public:
	void apply(double, double);
	static MouseService* getInstance();
	void mouseLeft();
};