#include "Application.hpp"

void onKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods) {
	auto camera = Camera::getInstance();
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		camera->lookRight();
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		camera->lookLeft();
	}
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		camera->lookUp();
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		camera->lookDown();
	}
	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		camera->requestReset();
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
