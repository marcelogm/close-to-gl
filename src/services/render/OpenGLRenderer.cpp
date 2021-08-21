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

	int colorOffset = normalOffset + sizeof(this->vertices->at(0).normal);
	glVertexAttribPointer(vColor, 3, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexData), BUFFER_OFFSET(colorOffset));
	glEnableVertexAttribArray(vColor);

	glUseProgram(program);
	
	this->modelSpace = glGetUniformLocation(program, "model");
	this->viewSpace = glGetUniformLocation(program, "view");
	this->projectionSpace = glGetUniformLocation(program, "projection");
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

void OpenGLRenderer::display() {
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	glClearColor(0.0f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Camera* camera = Camera::getInstance();
	float fov = 80.0f;
	if (camera->shouldReset) {
		camera->reset(this->range.x, this->range.y, glm::radians(fov));
		camera->shouldReset = false;
	}

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = camera->getView();
	float zFar = 50000.0f;
	glm::mat4 projection = glm::perspective(glm::radians(fov), 600.0f / 600.0f, 0.1f, zFar);
	glUniformMatrix4fv(modelSpace, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewSpace, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionSpace, 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(VAOs[Triangles]);
	glDrawArrays(GL_TRIANGLES, 0, this->verticesCount);

	glFlush();
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