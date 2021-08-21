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
	this->window = glfwCreateWindow(1200, 800, "CloseToGL", NULL, NULL);
	glfwSetKeyCallback(this->window, onKeyPress);
	glfwMakeContextCurrent(window);
	gl3wInit();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 410");
	ImGui::StyleColorsDark();

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
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(this->window);
	glfwTerminate();
}

Application::~Application() {
	delete this->window;
}
