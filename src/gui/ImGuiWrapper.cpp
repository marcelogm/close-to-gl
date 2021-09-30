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
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
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

	ImGui::ColorEdit4("Cor do objeto", config->getColor());

	ImGui::Text("Shading:");
	ImGui::RadioButton("No shading", config->getShading(), LIGHT_NO_SHADING);
	if (*config->getOpenGLUse()) {
		ImGui::RadioButton("Gouraud Shading AD", config->getShading(), LIGHT_GOURAUD_AD);
	}
	ImGui::RadioButton("Gouraud Shading ADS", config->getShading(), LIGHT_GOURAUD_ADS);
	if (*config->getOpenGLUse()) {
		ImGui::RadioButton("Phong Shading", config->getShading(), LIGHT_PHONG_SHADING);
	}

	ImGui::Text("Diffuse light position:");
	ImGui::SliderFloat("X", &config->getLightPosition()->x, -1000.0f, 1000.0f, "");
	ImGui::SliderFloat("Y", &config->getLightPosition()->y, -1000.0f, 1000.0f, "");
	ImGui::SliderFloat("Z", &config->getLightPosition()->z, -1000.0f, 1000.0f, "");
	ImGui::ColorEdit4("Cor", config->getLightColor());

	ImGui::Text("Intesidade");
	ImGui::SliderFloat("Luz ambiente", config->getAmbientStrength(), 0.0f, 1.0f);
	ImGui::SliderFloat("Luz difusa", config->getDiffuseStrength(), 0.0f, 1.0f);
	ImGui::SliderFloat("Luz especular", config->getSpecularStrength(), 0.0f, 1.0f);
	ImGui::End();
}

void ImGuiWrapper::space() {
	ImGui::Begin("Render e camera", NULL, ImGuiWindowFlags_AlwaysAutoResize);
	if (ImGui::Button("Restaurar (R)")) {
		config->reset();
		camera->requestReset();
	}
	ImGui::Text("Transalacao da camera:");

	if (ImGui::SliderFloat("u", &camera->getPosition()->x, -10000.0f, 10000.0f, "")) {
		camera->update();
	}
	if (ImGui::SliderFloat("v", &camera->getPosition()->y, -10000.0f, 10000.0f, "")) {
		camera->update();
	} 
	if (ImGui::SliderFloat("n", &camera->getPosition()->z, -10000.0f, 10000.0f, "")) {
		camera->update();
	}

	ImGui::Text("Rotacao da camera:");
	if (ImGui::SliderFloat("Pitch", camera->getPitch(), -360.0f, 360.0f, "")) {
		camera->update();
	}
	if (ImGui::SliderFloat("Yaw", camera->getYaw(), (-360.0f - 90.0f), (360.0f - 90.0f), "")) {
		camera->update();
	}
	float diffRoll = 0.0f;
	if (ImGui::SliderFloat("Roll", &diffRoll, -360.0f, 360.0f, "")) {
		camera->doRoll(diffRoll);
	}

	ImGui::Text("Translacao fixa:");
	float diffRotate = 0.0f;
	if (ImGui::SliderFloat("Translacao", &diffRotate, -10.0f, 10.0f, "", ImGuiSliderFlags_Logarithmic)) {
		camera->rotateAround(diffRotate);
	}

	ImGui::Text("Visao e perspectiva:");
	ImGui::SliderInt("FOV X", config->getXFOV(), 1, 180);
	ImGui::SliderInt("FOV Y", config->getYFOV(), 1, 180);
	ImGui::SliderInt("Z Near", config->getZNear(), 1, 10000, "%d", ImGuiSliderFlags_Logarithmic);
	ImGui::SliderInt("Z Far", config->getZFar(), 100, 20000, "%d", ImGuiSliderFlags_Logarithmic);

	ImGui::Text("Configuracao de teclado:");
	ImGui::Checkbox("Utilizar mouse", config->getMouseStatus());
	ImGui::SliderFloat("Sensibilidade do mouse", config->getMouseSensibility(), 0.0f, 100.0f, "%.0f", ImGuiSliderFlags_Logarithmic);
	ImGui::Checkbox("Girar camera no proprio eixo (CNTRL)", config->getMove());
	ImGui::SliderFloat("Sensibilidade da movimentacao", config->getSensibility(), 0.0f, 100.0f, "%.0f", ImGuiSliderFlags_Logarithmic);
	ImGui::Text("Render mode:");
	ImGui::RadioButton("Triangulos", config->getRenderMode(), RENDER_MODE_TRIANGLE);
	ImGui::SameLine();
	if (*config->getOpenGLUse()) {
		ImGui::RadioButton("Pontos", config->getRenderMode(), RENDER_MODE_DOT);
		ImGui::SameLine();
	}
	ImGui::RadioButton("Frame", config->getRenderMode(), RENDER_MODE_FRAME);
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