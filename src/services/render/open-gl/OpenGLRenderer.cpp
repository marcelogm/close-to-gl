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

	int textureOffset = sizeof(this->vertices[0].normal) + normalOffset;
	glVertexAttribPointer(aTextCoord, 2, GL_FLOAT, GL_FALSE, sizeof(data::VertexData), BUFFER_OFFSET(textureOffset));
	glEnableVertexAttribArray(aTextCoord);

	glGenTextures(1, &this->texture);
	glBindBuffer(GL_TEXTURE_2D, this->texture);
	data::Texture texture = this->getTexture();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.width, texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture.data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(texture.data);

	glActiveTexture(GL_TEXTURE2);
	glUniform1f(glGetUniformLocation(program, "texture1"), 2);
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
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture);
	glGenerateMipmap(GL_TEXTURE_2D);

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
	this->background->process();

	glUniformMatrix4fv(modelSpace, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewSpace, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionSpace, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(normalTransform, 1, GL_FALSE, glm::value_ptr(normal));
	glBindVertexArray(VAOs[Triangles]);
	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[VertexBuffer]);

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
	this->drawer = new OpenGLDrawProcessor();
	this->reset = new renderer::CameraResetProcessor();
	this->background = new renderer::BackgroundProcessor();
	this->light = new LightProcessor();
	this->config = Config::getInstance();
	this->camera = Camera::getInstance();
	this->projectionProvider = new renderer::ProjectionFromConfig();
}

data::Texture OpenGLRenderer::getTexture() {
	int width, height, nrChannels;
	unsigned char* data = stbi_load("data/wall.jpg", &width, &height, &nrChannels, 0);
	if (data) {
		return { (size_t) width, (size_t) height, data };
	}
	return { 0, 0, nullptr };
}