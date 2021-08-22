#include "render.hpp"

using namespace std;

void OpenGLRenderer::init(data::Model* model) {
	this->vertices = this->getVertexDataFromDataModel(model);
	this->verticesCount = this->vertices->size();
	this->range = this->getRange(this->vertices);

	vector<ShaderInfo> shaders = this->getShaders();
	GLuint program = LoadShaders(&shaders.front());

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

	glUseProgram(program);
	
	this->modelSpace = glGetUniformLocation(program, "model");
	this->viewSpace = glGetUniformLocation(program, "view");
	this->projectionSpace = glGetUniformLocation(program, "projection");
	this->customColor = glGetUniformLocation(program, "customColor");
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}


void OpenGLRenderer::display() {
	glFlush();
	Camera* camera = Camera::getInstance();
	Config* config = Config::getInstance();
	float* rgba = config->getColor();

	if (*config->getCW()) {
		glFrontFace(GL_CW);
	} else {
		glFrontFace(GL_CCW);
	}
	glCullFace(GL_BACK);

	glClearColor(0.5f, 0.8f, 0.5f, 1.0f);
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
	glDrawArrays(GL_TRIANGLES, 0, this->verticesCount);
}

vector<ShaderInfo> OpenGLRenderer::getShaders() {
	return {
		{ GL_VERTEX_SHADER, "media/shaders/shader.vert" },
		{ GL_FRAGMENT_SHADER, "media/shaders/shader.frag" },
		{ GL_NONE, NULL }
	};
}

vector<VertexData>* OpenGLRenderer::getVertexDataFromDataModel(data::Model* model) {
	vector<VertexData>* vertices = new vector<VertexData>();
	for (auto triangle : *model->getTriangles()) {
		for (auto vertex : *triangle->getVertices()) {
			auto position = vertex->getPosition();
			auto normal = vertex->getNormal();
			auto color = vertex->getColor();
			vertices->push_back({
				{ position->x, position->y, position->z },
				{ normal->x, normal->y, normal->z },
				{ color->r, color->g, color->b }
			});
		}
	}
	return vertices;
}

VertexDataRange OpenGLRenderer::getRange(vector<VertexData>* vertices) {
	float minX = 0, minY = 0, minZ = 0, maxX = 0, maxY = 0, maxZ = 0;
	for (auto vertex : *vertices) {
		minX = glm::min(minX, vertex.position[0]);
		minY = glm::min(minY, vertex.position[1]);
		minZ = glm::min(minZ, vertex.position[2]);
		maxX = glm::max(maxX, vertex.position[0]);
		maxY = glm::max(maxY, vertex.position[1]);
		maxZ = glm::max(maxZ, vertex.position[2]);
	}
	return {
		glm::vec2(minX, maxX), glm::vec2(minY, maxY), glm::vec2(minZ, maxZ)
	};
}