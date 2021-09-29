#include "close.hpp"

using namespace close;

std::vector<data::VertexPayload> ViewportTransformationJob::apply(std::vector<data::VertexPayload>* vertices) {
	std::vector<data::VertexPayload> transformed(vertices->size());
	const float width = (float)*config->getWindowWidth();
	const float height = (float)*config->getWindowHeight();
	for (size_t i = 0; i < vertices->size(); i++) {
		const auto vertex = vertices->at(i);
		const auto position = vertex.position;
		transformed[i] = {
			glm::vec4(
				((position.x + 1) * 0.5f * height),
				((position.y + 1) * 0.5f * width),
				vertex.position.z,
				vertex.position.w
			),
			vertex.normal,
			vertex.color
		};
	}
	return transformed;
}

close::ViewportTransformationJob::ViewportTransformationJob() {
	this->config = Config::getInstance();
}
