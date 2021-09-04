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
	this->renderers = new std::vector<renderer::Renderer*>();
	this->renderers->push_back(new open::OpenGLRenderer());
	this->renderers->push_back(new close::CloseToGLRenderer());

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

	data::Model* model = this->factory->get("data/cow_up.in");
	for (auto renderer : *this->renderers) {
		renderer->init(model);
	}

	glfwGetWindowSize(window, config->getWindowHeight(), config->getWindowWidth());
}

void Application::loop() {
	while (!glfwWindowShouldClose(this->window)) {
		for (auto renderer : *this->renderers) {
			if (renderer->test()) {
				renderer->display();
			}
		}
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
