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
	ImGui::Text("Render mode:");
	ImGui::RadioButton("Triangulos", config->getRenderMode(), 0);
	ImGui::RadioButton("Pontos", config->getRenderMode(), 1);
	ImGui::RadioButton("Frame", config->getRenderMode(), 2);
	if (ImGui::Button("Restaurar (R)")) {
		config->reset();
		camera->requestReset();
	}
	ImGui::ColorEdit4("Color", config->getColor());
	ImGui::SliderInt("FOV X", config->getXFOV(), 1, 180);
	ImGui::SliderInt("FOV Y", config->getYFOV(), 1, 180);
	ImGui::SliderInt("Z Near", config->getZNear(), 1, 1000, "%d", ImGuiSliderFlags_Logarithmic);
	ImGui::SliderInt("Z Far", config->getZFar(), 100, 10000, "%d", ImGuiSliderFlags_Logarithmic);
	ImGui::Checkbox("Utilizar mouse", config->getMouseStatus());
	ImGui::SliderFloat("Sensibilidade do mouse", config->getMouseSensibility(), 0.0f, 100.0f, "%.0f", ImGuiSliderFlags_Logarithmic);
	ImGui::Checkbox("Girar camera no proprio eixo (CNTRL)", config->getMove());
	ImGui::SliderFloat("Sensibilidade da movimentacao", config->getSensibility(), 0.0f, 100.0f, "%.0f", ImGuiSliderFlags_Logarithmic);
	ImGui::Checkbox("Clockwise", config->getCW());
	ImGui::End();

	ImGui::Begin("Configurado atualmente para:", &open, ImGuiWindowFlags_AlwaysAutoResize);
	switch (*config->getRenderMode()) {
	case 0:
		ImGui::Text("Renderizando os triangulos.");
		break;
	case 1:
		ImGui::Text("Renderizando os pontos.");
		break;
	case 2:
		ImGui::Text("Renderizando os wireframes.");
		break;
	}
	if (*config->getMove()) {
		ImGui::Text("Setas fazem pitch e yaw. Z e X fazem roll.");
	} else {
		ImGui::Text("Setas movimentam a camera. Z e X sobem e descem a camera.");
	}
	ImGui::Text("A e D giram ao redor do objeto.");
	if (*config->getCW()) {
		ImGui::Text("Backface culling configurado como clockwise.");
	}
	else {
		ImGui::Text("Backface culling configurado como counter-clockwise.");
	}
	if (*config->getMouseStatus()) {
		ImGui::Text("Mouse esta sendo utilizado para pitch e yaw.");
	}
	else {
		ImGui::Text("Mouse nao esta sendo utilizado.");
	}
	ImGui::End();
	ImGui::Begin("Debug:", &open, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("FPS: %.2f", Debug::getInstance()->getFramerate());
	ImGui::Text("Time: %.2fms", Debug::getInstance()->getFrametime());
	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiWrapper::destroy() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
