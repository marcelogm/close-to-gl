#include "close.hpp"
#include<iostream>

using namespace close;

void CloseToGLRenderer::init(data::Model* model) {
	glGenVertexArrays(NumVAOs, this->VAOs);
	glBindVertexArray(this->VAOs[Triangles]);

	auto converter = std::unique_ptr<ModelToVertex>();
	this->vertices = converter->getVertexDataFromDataModel(model);
	this->range = converter->getRange(this->vertices);
	this->verticesCount = this->vertices->size();

	this->program = LoadShaders(&this->getShaders().front());
	glUseProgram(this->program);

	glGenBuffers(NumBuffers, this->buffers);
	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[VertexBuffer]);
	glBufferData(GL_ARRAY_BUFFER, this->vertices->size() * sizeof(data::VertexData2D), 0, GL_DYNAMIC_DRAW);
	
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
	if (processed->size() > 0) {
		glBufferSubData(GL_ARRAY_BUFFER, 0, processed->size() * sizeof(data::VertexData2D), &processed.get()->front());
	}

	this->background->process();
	this->drawer->process(processed->size());
	this->reset->process(this->range);
}

bool CloseToGLRenderer::test() {
	return !*this->config->getOpenGLUse();
}

CloseToGLRenderer::CloseToGLRenderer() {
	this->config = Config::getInstance();
	this->pipeline = new CloseToGLPipeline();
	this->drawer = new renderer::OpenGLDrawProcessor();
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
