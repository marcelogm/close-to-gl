#include "gui.hpp"
#include <chrono>


ImGuiWrapper::ImGuiWrapper() {
	config = Config::getInstance();
	camera = Camera::getInstance();
};

ImGuiWrapper* ImGuiWrapper::getInstance() {
	if (instance == nullptr) {
		instance = new ImGuiWrapper();
	}
	return instance;
}

ImGuiWrapper* ImGuiWrapper::instance = nullptr;

void ImGuiWrapper::init(GLFWwindow* window) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 410");
	ImGui::StyleColorsDark();
}

void ImGuiWrapper::display() {
	bool open = true;
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin("Ferramentas", &open, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::ColorEdit4("Color", config->getColor());
	if (ImGui::Button("Restaurar")) {
		camera->requestReset();
	}
	if (ImGui::SliderInt("FOV", config->getFOV(), 1, 180)) {
		camera->requestReset();
	}
	ImGui::SliderInt("Z Near", config->getZNear(), 1, 1000, "%d", ImGuiSliderFlags_Logarithmic);
	ImGui::SliderInt("Z Far", config->getZFar(), 100, 10000, "%d", ImGuiSliderFlags_Logarithmic);
	ImGui::SliderFloat("Sensibilidade", config->getSensibility(), 0.0f, 100.0f, "%.0f", ImGuiSliderFlags_Logarithmic);
	ImGui::Checkbox("Girar camera no proprio eixo (cntrl)", config->getMove());
	ImGui::Checkbox("Clockwise", config->getCW());
	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiWrapper::destroy() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
