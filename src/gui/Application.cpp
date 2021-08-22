#include "gui.hpp"

void onKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods) {
	KeyStrategyService::getInstance()->apply(key, action);
}

void onMouseMove(GLFWwindow* window, double xpos, double ypos) {
	auto config = Config::getInstance();
	if (*config->getMouseStatus()) {
		MouseService::getInstance()->apply(xpos, ypos);
	}
}

void onMouseEnter(GLFWwindow* window, int entered) {
	if (!entered) {
		MouseService::getInstance()->mouseLeft();
	}
}

void Application::init() {
	this->renderer = new OpenGLRenderer();
	this->factory = new ModelFactory();
	this->ui = ImGuiWrapper::getInstance();
	auto config = Config::getInstance();

	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, false);
	this->window = glfwCreateWindow(800, 600, "Programming Assignment 1", NULL, NULL);
	glfwSetKeyCallback(this->window, onKeyPress);
	glfwSetCursorPosCallback(this->window, onMouseMove);
	glfwMakeContextCurrent(window);
	gl3wInit();

	this->ui->init(window);
	this->renderer->init(this->factory->get("data/cow_up.in"));

	glfwGetWindowSize(window, config->getWindowHeight(), config->getWindowWidth());
}

void Application::loop() {
	while (!glfwWindowShouldClose(this->window)) {
		this->renderer->display();
		this->ui->display();
		glfwSwapBuffers(this->window);
		glfwPollEvents();
	}
}
void Application::detroy() {
	this->ui->destroy();
	glfwDestroyWindow(this->window);
	glfwTerminate();
}
