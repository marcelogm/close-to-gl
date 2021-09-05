#include "close.hpp"
#include<iostream>

using namespace close;

void CloseToGLRenderer::init(data::Model* model) {
	glGenVertexArrays(NumVAOs, this->VAOs);
	glBindVertexArray(this->VAOs[Triangles]);

	auto converter = std::unique_ptr<ModelToVertex>();
	this->vertices = converter->getVertexDataFromDataModel(model);
	this->verticesCount = this->vertices->size();
	this->range = converter->getRange(this->vertices);
	auto processed = pipeline->apply(this->vertices);

	std::vector<ShaderInfo> shaders = {
		{ GL_VERTEX_SHADER, "media/shaders/close-to-gl/shader.vert" },
		{ GL_FRAGMENT_SHADER, "media/shaders/close-to-gl/shader.frag" },
		{ GL_NONE, NULL }
	};
	this->program = LoadShaders(&shaders.front());
	glUseProgram(this->program);

	glGenBuffers(NumBuffers, this->buffers);
	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[VertexBuffer]);
	glBufferData(GL_ARRAY_BUFFER, this->vertices->size() * sizeof(data::VertexData2D), 0, GL_DYNAMIC_DRAW);
	
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, sizeof(data::VertexData2D), BUFFER_OFFSET(0));
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_PROGRAM_POINT_SIZE);
}

void CloseToGLRenderer::display() {
	auto processed = pipeline->apply(this->vertices);

	glFlush();
	glUseProgram(this->program);
	glDisable(GL_CULL_FACE);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(this->VAOs[Triangles]);
	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[VertexBuffer]);
	if (processed->size() > 0) {
		glBufferSubData(GL_ARRAY_BUFFER, 0, processed->size() * sizeof(data::VertexData2D), &processed.get()->front());
	}

	switch (*config->getRenderMode()) {
	case 0:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawArrays(GL_TRIANGLES, 0, processed->size());
		break;
	case 1:
		glDrawArrays(GL_POINTS, 0, processed->size());
		break;
	case 2:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawArrays(GL_TRIANGLES, 0, processed->size());
		break;
	}
}

bool CloseToGLRenderer::test() {
	return !*this->config->getOpenGLUse();
}

CloseToGLRenderer::CloseToGLRenderer() {
	this->config = Config::getInstance();
	this->pipeline = new CloseToGLPipeline();
}

