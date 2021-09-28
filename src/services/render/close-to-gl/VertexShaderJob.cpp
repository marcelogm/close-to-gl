#include "close.hpp"
#include <algorithm>
#include <functional>

using namespace close;

std::vector<data::VertexPayload> VertexShaderJob::apply(std::vector<data::VertexData>* vertices) {
	const glm::mat4 MVP = this->getMVP();
	auto color = this->config->getColor();

	std::vector<data::VertexPayload> payload(vertices->size());
	for (size_t i = 0; i < vertices->size(); i++) {
		auto current = vertices->at(i);
		payload[i] = {
			MVP * this->toHomogeneous(&current),
			glm::vec3(current.normal[0], current.normal[1], current.normal[2]),
			glm::vec3(color[0], color[1], color[2])
		};
	}
	return payload;
}

glm::mat4 VertexShaderJob::getMVP() {
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = this->camera->getView();
	glm::mat4 projection = this->projectionProvider->get();
	return projection * view * model;
}

glm::vec4 VertexShaderJob::toHomogeneous(data::VertexData* vertex) {
	return glm::vec4(
		vertex->position[0], 
		vertex->position[1], 
		vertex->position[2], 
		1.0f
	);
}

VertexShaderJob::VertexShaderJob() {
	this->projectionProvider = new ProjectionFromConfig();
	this->camera = Camera::getInstance();
	this->config = Config::getInstance();
}