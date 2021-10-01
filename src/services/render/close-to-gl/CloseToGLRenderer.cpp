#include "close.hpp"
#include<iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace close;

void CloseToGLRenderer::init(data::Model* model) {
	glGenVertexArrays(NumVAOs, this->VAOs);
	glBindVertexArray(this->VAOs[Triangles]);

	auto converter = std::unique_ptr<ModelToVertex>();
	this->vertices = converter->getVertexDataFromDataModel(model);
	this->size = model->getTriangles()->size() * 3;
	this->range = converter->getRange(this->vertices, this->size);

	*config->getCloseToGLProgramId() = LoadShaders(&this->getShaders().front());

	glGenBuffers(NumBuffers, this->buffers);
	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[VertexBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->panelVertices), this->panelVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), BUFFER_OFFSET(0));
	glVertexAttribPointer(aTexCoord, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), BUFFER_OFFSET(2 * sizeof(float)));

	glEnableVertexAttribArray(vPosition);
	glEnableVertexAttribArray(aTexCoord);

	glUseProgram(*config->getCloseToGLProgramId());

	glGenTextures(1, config->getCloseToGLTextureId());
	glBindTexture(GL_TEXTURE_2D, *config->getCloseToGLTextureId());

	int width = *config->getWindowWidth();
	int height = *config->getWindowHeight();

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glGenerateMipmap(GL_TEXTURE_2D);

	glUniform1i(glGetUniformLocation(*config->getCloseToGLProgramId(), "text"), 0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_PROGRAM_POINT_SIZE);
}

void CloseToGLRenderer::display() {
	// model deve carregar o size
	auto processed = pipeline->apply(this->vertices, this->size);
	float* rgba = config->getColor();

	glActiveTexture(GL_TEXTURE0);
	glUseProgram(*config->getCloseToGLProgramId());

	// Desabilita cull face pois ele está implementado em ClippingJob.cpp 
	glDisable(GL_CULL_FACE);

	auto width = *config->getWindowWidth();
	auto height = *config->getWindowHeight();
	
	if (processed.size() > 0) {
		glBindTexture(GL_TEXTURE_2D, *config->getCloseToGLTextureId());
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, &processed.front());
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	glBindVertexArray(this->VAOs[Triangles]);
	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[VertexBuffer]);

	this->background->process();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, 6);
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
