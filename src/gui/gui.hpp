#pragma once

#include "vgl.h"
#include "../services/services.hpp"
#include "../services/render/render.hpp"
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
	OpenGLRenderer* renderer;
	ImGuiWrapper* ui;
public:
	void init();
	void loop();
	void detroy();
	~Application();
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
	virtual void apply(float angle) = 0;
};

class KeyStrategyService {
private:
	vector<KeyCommandStrategy*>* strategies;
	static KeyStrategyService* instance;
	KeyStrategyService();
public:
	vector<KeyCommandStrategy*>* getKeyStrategies();
	static KeyStrategyService* getInstance();
};