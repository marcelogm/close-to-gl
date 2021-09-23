#include "close.hpp"
#include<iostream>

using namespace close;

void CloseToGLRenderer::init(data::Model* model) {
	glGenVertexArrays(NumVAOs, this->VAOs);
	glBindVertexArray(this->VAOs[Triangles]);

	auto converter = std::unique_ptr<ModelToVertex>();
	this->vertices = converter->getVertexDataFromDataModel(model);
	this->range = converter->getRange(this->vertices);

	this->program = LoadShaders(&this->getShaders().front());
	glUseProgram(this->program);

	glGenBuffers(NumBuffers, this->buffers);
	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[VertexBuffer]);
	glBufferStorage(GL_ARRAY_BUFFER, sizeof(this->panelVertices), this->panelVertices, 0);

	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, sizeof(data::VertexData2D), BUFFER_OFFSET(0));
	this->customColor = glGetUniformLocation(program, "customColor");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_PROGRAM_POINT_SIZE);
}

void CloseToGLRenderer::display() {
	auto processed = pipeline->apply(this->vertices);
	float* rgba = config->getColor();

	glUseProgram(this->program);

	// Desabilita cull face pois ele está implementado em ClippingJob.cpp 
	glDisable(GL_CULL_FACE);
	glUniform4f(customColor, rgba[0], rgba[1], rgba[2], rgba[3]);

	glBindVertexArray(this->VAOs[Triangles]);
	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[VertexBuffer]);
	
	// TODO: remover processador de fundo, não mais necessário
	this->background->process();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, 12);
	this->reset->process(this->range);
}

bool CloseToGLRenderer::test() {
	return !*this->config->getOpenGLUse();
}

CloseToGLRenderer::CloseToGLRenderer() {
	this->config = Config::getInstance();
	this->pipeline = new CloseToGLPipeline();
	this->reset = new renderer::CameraResetProcessor();
	this->background = new renderer::BackgroundProcessor();
}

std::vector<ShaderInfo> CloseToGLRenderer::getShaders() {
	return {
		{ GL_VERTEX_SHADER, "media/shaders/close-to-gl/shader.vert" },
		{ GL_FRAGMENT_SHADER, "media/shaders/close-to-gl/shader.frag" },
		{ GL_NONE, NULL }
	};
}
