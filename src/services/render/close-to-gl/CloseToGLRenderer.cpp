#include "close.hpp"

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
}

void CloseToGLRenderer::display() {
	auto processed = pipeline->apply(this->vertices);
	glUseProgram(this->program);
	glCullFace(GL_FRONT);

	glFlush();
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(this->VAOs[Triangles]);
	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[VertexBuffer]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, processed->size() * sizeof(data::VertexData2D), &processed.get()->front());

	glDrawArrays(GL_TRIANGLES, 0, processed->size());
}

bool CloseToGLRenderer::test() {
	return !*this->config->getOpenGLUse();
}

CloseToGLRenderer::CloseToGLRenderer() {
	this->config = Config::getInstance();
	this->pipeline = new CloseToGLPipeline();
}

