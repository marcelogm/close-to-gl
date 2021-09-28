#include "close.hpp"

using namespace close;

std::vector<data::VertexPayload> ViewportTransformationJob::apply(std::vector<data::VertexPayload>* vertices) {
	std::vector<data::VertexPayload> transformed(vertices->size());
	glm::mat4 V = this->getViewport();
	for (size_t i = 0; i < vertices->size(); i++) {
		const auto vertex = vertices->at(i);
		transformed[i] = {
			V * vertex.position,
			vertex.normal,
			vertex.color
		};
	}
	return transformed;
}

glm::mat4 close::ViewportTransformationJob::getViewport() {
	const float l = 0.0f;
	const float r = (float) *config->getWindowWidth() - 1.0f;
	const float t = 0.0f;
	const float b = (float) *config->getWindowHeight() - 1.0f;
	return glm::ortho(l, r, b, t);
	/*return glm::mat4(
		(r - l) / 2,        0.0f, 0.0f, 0.0f,
		0.0f,        (t - b) / 2, 0.0f, 0.0f,
		0.0f,               0.0f, 1.0f, 0.0f,
		(r + l) / 2, (t + b) / 2, 0.0f, 1.0f
	);*/
}

close::ViewportTransformationJob::ViewportTransformationJob() {
	this->config = Config::getInstance();
}
