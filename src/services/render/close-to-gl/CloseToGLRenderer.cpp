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
	this->range = converter->getRange(this->vertices);

	this->program = LoadShaders(&this->getShaders().front());

	glGenBuffers(NumBuffers, this->buffers);
	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[VertexBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->panelVertices), this->panelVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), BUFFER_OFFSET(0));
	glVertexAttribPointer(aTexCoord, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), BUFFER_OFFSET(2 * sizeof(float)));

	glEnableVertexAttribArray(vPosition);
	glEnableVertexAttribArray(aTexCoord);

	glUseProgram(this->program);

	glGenTextures(1, &this->texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);	
	unsigned char* data = stbi_load("data/teste.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glUniform1i(glGetUniformLocation(program, "text"), 0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_PROGRAM_POINT_SIZE);
}

void CloseToGLRenderer::display() {
	auto processed = pipeline->apply(this->vertices);
	float* rgba = config->getColor();

	glActiveTexture(GL_TEXTURE0);
	glUseProgram(this->program);

	// Desabilita cull face pois ele está implementado em ClippingJob.cpp 
	glDisable(GL_CULL_FACE);

	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(this->VAOs[Triangles]);
	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[VertexBuffer]);

	// TODO: remover processador de fundo, não mais necessário
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
