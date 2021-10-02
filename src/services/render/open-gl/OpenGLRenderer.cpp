#include "open.hpp"

using namespace open;

void OpenGLRenderer::init(data::Model* model) {
	this->verticesCount = model->getTriangles()->size() * 3;
	this->vertices = this->converter->getVertexDataFromDataModel(model);
	this->range = this->converter->getRange(this->vertices, verticesCount);

	std::vector<ShaderInfo> shaders = this->getShaders();
	this->program = LoadShaders(&shaders.front());

	glUseProgram(this->program);

	glGenVertexArrays(NumVAOs, this->VAOs);
	glGenBuffers(NumBuffers, this->buffers);

	glBindVertexArray(this->VAOs[Triangles]);

	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[VertexBuffer]);
	glBufferData(GL_ARRAY_BUFFER, verticesCount * sizeof(data::VertexData), this->vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, sizeof(data::VertexData), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vPosition);

	int normalOffset = sizeof(this->vertices[0].position);
	glVertexAttribPointer(vNormalVertex, 3, GL_FLOAT, GL_FALSE, sizeof(data::VertexData), BUFFER_OFFSET(normalOffset));
	glEnableVertexAttribArray(vNormalVertex);
	
	this->modelSpace = glGetUniformLocation(program, "model");
	this->viewSpace = glGetUniformLocation(program, "view");
	this->projectionSpace = glGetUniformLocation(program, "projection");
	this->normalTransform = glGetUniformLocation(program, "normalTransform");
	this->light->setup(program);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_PROGRAM_POINT_SIZE);
}

#undef min
#undef max
void OpenGLRenderer::display() {
	glUseProgram(this->program);

	glEnable(GL_CULL_FACE);
	if (*config->getCW()) {
		glFrontFace(GL_CW);
	} else {
		glFrontFace(GL_CCW);
	}
	glCullFace(GL_BACK);

	const glm::mat4 model = glm::mat4(1.0f);
	const glm::mat4 view = camera->getView();
	const glm::mat4 projection = this->projectionProvider->get();
	const glm::mat4 normal = glm::transpose(glm::inverse(model * view));

	this->light->process();
	glUniformMatrix4fv(modelSpace, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewSpace, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionSpace, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(normalTransform, 1, GL_FALSE, glm::value_ptr(normal));
	glBindVertexArray(VAOs[Triangles]);

	this->background->process();
	this->drawer->process(this->verticesCount);	
	this->reset->process(this->range);
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
	this->drawer = new renderer::OpenGLDrawProcessor();
	this->reset = new renderer::CameraResetProcessor();
	this->background = new renderer::BackgroundProcessor();
	this->light = new LightProcessor();
	this->config = Config::getInstance();
	this->camera = Camera::getInstance();
	this->projectionProvider = new ProjectionFromConfig();
}

