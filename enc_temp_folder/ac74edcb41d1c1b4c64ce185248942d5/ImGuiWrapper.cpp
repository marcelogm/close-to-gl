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
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	this->shading();
	this->info();
	this->space();
	this->debug();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiWrapper::destroy() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiWrapper::shading() {
	ImGui::Begin("Cor e sombreamento", NULL, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Checkbox("Habilitar", config->getShadingUse());
	if (*config->getShadingUse()) {
		ImGui::RadioButton("Gouraud Shading AD", config->getShading(), 1);
		ImGui::SameLine();
		ImGui::RadioButton("Gouraud Shading ADS", config->getShading(), 2);
		ImGui::SameLine();
		ImGui::RadioButton("Phong Shading", config->getShading(), 3);

		ImGui::Text("Light position:");
		ImGui::SliderFloat("X", &config->getLightPosition()->x, -1000.0f, 1000.0f, "");
		ImGui::SameLine();
		ImGui::SliderFloat("Y", &config->getLightPosition()->y, -1000.0f, 1000.0f, "");
		ImGui::SameLine();
		ImGui::SliderFloat("Z", &config->getLightPosition()->z, -1000.0f, 1000.0f, "");
	}
	ImGui::ColorEdit4("Cor", config->getColor());
	ImGui::End();
}

void ImGuiWrapper::space() {
	ImGui::Begin("Render e camera", NULL, ImGuiWindowFlags_AlwaysAutoResize);
	if (ImGui::Button("Restaurar (R)")) {
		config->reset();
		camera->requestReset();
	}
	ImGui::SliderInt("FOV X", config->getXFOV(), 1, 180);
	ImGui::SliderInt("FOV Y", config->getYFOV(), 1, 180);
	ImGui::SliderInt("Z Near", config->getZNear(), 1, 10000, "%d", ImGuiSliderFlags_Logarithmic);
	ImGui::SliderInt("Z Far", config->getZFar(), 100, 20000, "%d", ImGuiSliderFlags_Logarithmic);
	ImGui::Checkbox("Utilizar mouse", config->getMouseStatus());
	ImGui::SliderFloat("Sensibilidade do mouse", config->getMouseSensibility(), 0.0f, 100.0f, "%.0f", ImGuiSliderFlags_Logarithmic);
	ImGui::Checkbox("Girar camera no proprio eixo (CNTRL)", config->getMove());
	ImGui::SliderFloat("Sensibilidade da movimentacao", config->getSensibility(), 0.0f, 100.0f, "%.0f", ImGuiSliderFlags_Logarithmic);
	ImGui::Text("Render mode:");
	ImGui::RadioButton("Triangulos", config->getRenderMode(), 0);
	ImGui::SameLine();
	ImGui::RadioButton("Pontos", config->getRenderMode(), 1);
	ImGui::SameLine();
	ImGui::RadioButton("Frame", config->getRenderMode(), 2);
	ImGui::Checkbox("Clockwise", config->getCW());
	ImGui::SameLine();
	ImGui::Checkbox("OpenGL", config->getOpenGLUse());
	ImGui::End();
}

void ImGuiWrapper::info() {
	ImGui::Begin("Controles e informacoes", NULL, ImGuiWindowFlags_AlwaysAutoResize);
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
	} else {
		ImGui::Text("Backface culling configurado como counter-clockwise.");
	}
	if (*config->getMouseStatus()) {
		ImGui::Text("Mouse esta sendo utilizado para pitch e yaw.");
	} else {
		ImGui::Text("Mouse nao esta sendo utilizado.");
	}
	ImGui::End();
}

void ImGuiWrapper::debug() {
	auto debug = Debug::getInstance();
	ImGui::Begin("Debug", NULL, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("Renderizando com %s", *config->getOpenGLUse() ? "OpenGL" : "Close2GL");
	ImGui::Text("FPS: %.2f", debug->getFramerate());
	ImGui::Text("Time: %.2fms", debug->getFrametime());
	ImGui::End();
}