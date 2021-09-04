#include "open.hpp"

using namespace open;

void OpenGLRenderer::init(data::Model* model) {
	this->vertices = this->converter->getVertexDataFromDataModel(model);
	this->verticesCount = this->vertices->size();
	this->range = this->converter->getRange(this->vertices);

	std::vector<ShaderInfo> shaders = this->getShaders();
	this->program = LoadShaders(&shaders.front());

	glUseProgram(this->program);

	glGenVertexArrays(NumVAOs, this->VAOs);
	glGenBuffers(NumBuffers, this->buffers);

	glBindVertexArray(this->VAOs[Triangles]);

	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[VertexBuffer]);
	glBufferData(GL_ARRAY_BUFFER, this->vertices->size() * sizeof(VertexData), &this->vertices->front(), GL_STATIC_DRAW);

	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vPosition);

	int normalOffset = sizeof(this->vertices->at(0).position);
	glVertexAttribPointer(vNormalVertex, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), BUFFER_OFFSET(normalOffset));
	glEnableVertexAttribArray(vNormalVertex);
	
	this->modelSpace = glGetUniformLocation(program, "model");
	this->viewSpace = glGetUniformLocation(program, "view");
	this->projectionSpace = glGetUniformLocation(program, "projection");
	this->customColor = glGetUniformLocation(program, "customColor");
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_PROGRAM_POINT_SIZE);
}

void OpenGLRenderer::display() {
	glUseProgram(this->program);
	glFlush();
	Camera* camera = Camera::getInstance();
	float* rgba = config->getColor();

	if (*config->getCW()) {
		glFrontFace(GL_CW);
	} else {
		glFrontFace(GL_CCW);
	}
	glCullFace(GL_BACK);

	glClearColor(0.75f, 0.75f, 0.75f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float fov = *config->getFOV();
	if (camera->getResetRequest()) {
		camera->reset(this->range.x, this->range.y, glm::radians(fov));
		camera->setResetRequest(false);
	}

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = camera->getView();
	glm::mat4 projection = glm::perspective(
		glm::radians(fov), 
		(float)*config->getWindowHeight() / *config->getWindowWidth(), 
		*config->getZNear() * 10.0f, 
		*config->getZFar() * 10.0f);

	glUniform4f(customColor, rgba[0], rgba[1], rgba[2], rgba[3]);
	glUniformMatrix4fv(modelSpace, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewSpace, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionSpace, 1, GL_FALSE, glm::value_ptr(projection));
	glBindVertexArray(VAOs[Triangles]);

	switch (*config->getRenderMode()) {
	case 0:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawArrays(GL_TRIANGLES, 0, this->verticesCount);
		break;
	case 1:
		glDrawArrays(GL_POINTS, 0, this->verticesCount);
		break;
	case 2:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawArrays(GL_TRIANGLES, 0, this->verticesCount);
		break;
	}
}

std::vector<ShaderInfo> OpenGLRenderer::getShaders() {
	return {
		{ GL_VERTEX_SHADER, "media/shaders/shader.vert" },
		{ GL_FRAGMENT_SHADER, "media/shaders/shader.frag" },
		{ GL_NONE, NULL }
	};
}

bool OpenGLRenderer::test() {
	return *this->config->getOpenGLUse();
}

OpenGLRenderer::OpenGLRenderer() {
	this->converter = new ModelToVertex();
	this->config = Config::getInstance();
}

