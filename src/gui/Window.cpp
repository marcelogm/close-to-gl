#include "Window.hpp"

void Application::init() {
	glfwInit();
	this->window = glfwCreateWindow(600, 600, "CloseToGL", NULL, NULL);
	glfwMakeContextCurrent(window);
	gl3wInit();
}

void Application::loop() {
	while (!glfwWindowShouldClose(this->window)) {
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