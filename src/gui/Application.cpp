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

void onWindowSizeChange(GLFWwindow* window, int width, int height) {
	auto config = Config::getInstance();
	*config->getWindowHeight() = height;
	*config->getWindowWidth() = width;
	*config->getXFOV() = ((float)width / (float)height) * *config->getYFOV();
	glViewport(0, 0, width, height);

	glUseProgram(*config->getCloseToGLProgramId());
	glDeleteTextures(1, config->getCloseToGLTextureId());
	glGenTextures(1, config->getCloseToGLTextureId());
	glBindTexture(GL_TEXTURE_2D, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glGenerateMipmap(GL_TEXTURE_2D);
	glUniform1i(glGetUniformLocation(*config->getCloseToGLProgramId(), "text"), 0);
}

void Application::init() {
	this->renderers = new std::vector<renderer::Renderer*>();
	this->renderers->push_back(new open::OpenGLRenderer());
	this->renderers->push_back(new close::CloseToGLRenderer());

	this->factory = new ModelFactory();
	this->ui = ImGuiWrapper::getInstance();
	auto config = Config::getInstance();

	glfwInit();
	this->window = glfwCreateWindow(800, 800, "Programming Assignment 1", NULL, NULL);
	glfwSetKeyCallback(this->window, onKeyPress);
	glfwSetCursorPosCallback(this->window, onMouseMove);
	glfwSetWindowSizeCallback(this->window, onWindowSizeChange);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
	gl3wInit();

	this->ui->init(window);
	glfwGetWindowSize(window, config->getWindowHeight(), config->getWindowWidth());

	data::Model* model = this->factory->get("data/cow_up.in");
	for (auto renderer : *this->renderers) {
		renderer->init(model);
	}

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
		Debug::getInstance()->countFrame();
	}
}
void Application::detroy() {
	this->ui->destroy();
	glfwDestroyWindow(this->window);
	glfwTerminate();
}