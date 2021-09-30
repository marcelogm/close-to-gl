#include "close.hpp"

using namespace close;

std::vector<data::VertexPayload> VertexShaderJob::apply(std::vector<data::VertexData>* vertices) {
	const glm::mat4 MV = this->getMV();
	const glm::mat4 normalTransform = glm::transpose(glm::inverse(MV));
	const glm::mat4 MVP = this->projectionProvider->get() * MV;
	auto phong = PhongIlluminationModel();
	std::vector<data::VertexPayload> payload(vertices->size());

	for (size_t i = 0; i < vertices->size(); i++) {
		auto current = vertices->at(i);
		auto vertices = glm::vec4(current.position[0], current.position[1], current.position[2], 1.0f);
		auto normal = glm::vec4(current.normal[0], current.normal[1], current.normal[2], 1.0f);

		auto position = MVP * vertices;
		auto trasnformedNormal = normalTransform * normal;

		glm::vec4 color;
		if (*config->getShading() == LIGHT_GOURAUD_ADS) {
			color = glm::vec4(phong.apply(vertices, trasnformedNormal), 1.0f);
		} else {
			color = glm::vec4(config->getColor()[0], config->getColor()[1], config->getColor()[2], 1.0f);
		}

		payload[i] = {
			position,
			normal,
			color
		};
	}

	return payload;
}

glm::mat4 VertexShaderJob::getMV() {
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = this->camera->getView();
	return view * model;
}

VertexShaderJob::VertexShaderJob() {
	this->projectionProvider = new ProjectionFromConfig();
	this->camera = Camera::getInstance();
	this->config = Config::getInstance();
	this->illumination = new PhongIlluminationModel();
}