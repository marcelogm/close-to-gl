#include "close.hpp"

using namespace close;

std::vector<data::VertexPayload> VertexShaderJob::apply(std::vector<data::VertexData>* vertices) {
	const glm::mat4 MVP = this->getMVP();
	auto color = this->config->getColor();
	auto phong = PhongIlluminationModel();

	std::vector<data::VertexPayload> payload(vertices->size());
	for (size_t i = 0; i < vertices->size(); i++) {
		auto current = vertices->at(i);
		auto normal = glm::vec3(current.normal[0], current.normal[1], current.normal[2]);
		auto position = MVP * this->toHomogeneous(&current);
		payload[i] = {
			position,
			normal,
			phong.apply(position, glm::vec4(color[0], color[1], color[2], 1.0f))
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
	this->illumination = new PhongIlluminationModel();
}