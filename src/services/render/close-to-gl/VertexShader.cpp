#include "close.hpp"

using namespace close;

VertexShader::VertexShader(VertexPayload* buffer) {
	this->projectionProvider = new renderer::ProjectionFromConfig();
	this->camera = Camera::getInstance();
	this->config = Config::getInstance();
	this->buffer = buffer;

	this->shaders = new vector<Shader*>();
	this->shaders->push_back(new PhongIlluminationModel());
	this->shaders->push_back(new ColorShader());
}

size_t VertexShader::apply(VertexData* vertices, size_t size) {
	const auto MV = this->getMV();
	const auto NT = glm::transpose(glm::inverse(MV));
	const auto MVP = this->projectionProvider->get() * MV;
	const auto shader = this->getShader();

	for (size_t i = 0; i < size; i++) {
		const auto current = vertices + i;
		const auto position = vec4(current->position[0], current->position[1], current->position[2], 1.0f);
		const auto normal = vec4(current->normal[0], current->normal[1], current->normal[2], 1.0f);
		const auto texture = vec2(current->texture[0], current->texture[1]);
		const auto transformedPosition = MVP * position;
		const auto transformedNormal = NT * normal;
		buffer[i] = {
			transformedPosition,
			normal,
			texture,
			shader->apply(position, transformedNormal)
		};
	}

	return size;
}

mat4 VertexShader::getMV() {
	const auto model = mat4(1.0f);
	const auto view = this->camera->getView();
	return view * model;
}

Shader* close::VertexShader::getShader() {
	for (Shader* s : *this->shaders) {
		if (s->test()) {
			return s;
		}
	}
	return nullptr;
}
