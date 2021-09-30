#include "close.hpp"

using namespace close;

close::VertexShader::VertexShader(vector<VertexPayload>* buffer) {
	this->projectionProvider = new ProjectionFromConfig();
	this->camera = Camera::getInstance();
	this->config = Config::getInstance();
	this->buffer = buffer;
}

size_t VertexShader::apply(vector<VertexData>* vertices) {
	const mat4 MV = this->getMV();
	const mat4 normalTransform = glm::transpose(glm::inverse(MV));
	const mat4 MVP = this->projectionProvider->get() * MV;
	const size_t SIZE = vertices->size();
	auto phong = PhongIlluminationModel();

	for (size_t i = 0; i < SIZE; i++) {
		auto current = vertices->at(i);
		auto vertices = vec4(current.position[0], current.position[1], current.position[2], 1.0f);
		auto normal = vec4(current.normal[0], current.normal[1], current.normal[2], 1.0f);

		auto position = MVP * vertices;
		auto trasnformedNormal = normalTransform * normal;

		vec4 color;
		if (*config->getShading() == LIGHT_GOURAUD_ADS) {
			color = vec4(phong.apply(vertices, trasnformedNormal), 1.0f);
		} else {
			color = vec4(config->getColor()[0], config->getColor()[1], config->getColor()[2], 1.0f);
		}

		buffer->at(i) = { position, normal, color };
	}

	return SIZE;
}

mat4 VertexShader::getMV() {
	mat4 model = mat4(1.0f);
	mat4 view = this->camera->getView();
	return view * model;
}