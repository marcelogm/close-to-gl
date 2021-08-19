#include "Application.hpp"

void Application::init() {
	glfwInit();
	this->renderer = new OpenGLRenderer();
	this->factory = new ModelFactory();
	this->window = glfwCreateWindow(600, 600, "CloseToGL", NULL, NULL);
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