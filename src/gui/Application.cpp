#include "gui.hpp"

void onKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods) {
	auto service = KeyStrategyService::getInstance();
	for (auto strategy : *service->getKeyStrategies()) {
		if (strategy->matches(key, action)) {
			strategy->apply(0.1f);
		}
	}
}

void Application::init() {
	glfwInit();
	this->renderer = new OpenGLRenderer();
	this->factory = new ModelFactory();
	this->window = glfwCreateWindow(600, 600, "CloseToGL", NULL, NULL);
	glfwSetKeyCallback(this->window, onKeyPress);
	glfwMakeContextCurrent(window);
	gl3wInit();
	this->renderer->init(this->factory->get("data/cow_up.in"));
}

void Application::loop() {
	while (!glfwWindowShouldClose(this->window)) {
		this->renderer->display();
		glfwSwapBuffers(this->window);
		glfwPollEvents();
	}
}
void Application::detroy() {
	glfwDestroyWindow(this->window);
	glfwTerminate();
}

Application::~Application() {
	delete this->window;
}
