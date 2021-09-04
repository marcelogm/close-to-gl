#include "close.hpp"

using namespace close;

std::vector<glm::vec4> VertexShaderJob::apply(std::vector<data::VertexData>* vertices) {
	const glm::mat4 MVP = this->getMVP();
	std::vector<glm::vec4> positions(vertices->size());
	for (size_t i = 0; i < vertices->size(); i++) {
		positions[i] = this->toHomogeneous(vertices->at(i)) * MVP;
	}
	return positions;
}

glm::mat4 VertexShaderJob::getMVP() {
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = this->camera->getView();
	glm::mat4 projection = this->projectionProvider->get();
	return model * view * projection;
}

glm::vec4 VertexShaderJob::toHomogeneous(data::VertexData vertex) {
	return glm::vec4(
		vertex.position[0], 
		vertex.position[1], 
		vertex.position[2], 
		1.0f
	);
}

VertexShaderJob::VertexShaderJob() {
	this->projectionProvider = new ProjectionFromConfig();
	this->camera = Camera::getInstance();
}