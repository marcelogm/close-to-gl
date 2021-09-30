#include "close.hpp"

using namespace close;

size_t ViewportTransformationJob::apply(size_t count) {
	const float width = (float)*config->getWindowWidth();
	const float height = (float)*config->getWindowHeight();
	for (size_t i = 0; i < count; i++) {
		const auto vertex = buffer->at(i);
		const auto position = vertex.position;
		buffer->at(i) = {
			glm::vec4(
				((position.x + 1) * 0.5f * width),
				((position.y + 1) * 0.5f * height),
				vertex.position.z,
				vertex.position.w
			),
			vertex.normal,
			vertex.color
		};
	}
	return count;
}

close::ViewportTransformationJob::ViewportTransformationJob(vector<VertexPayload>* buffer) {
	this->config = Config::getInstance();
	this->buffer = buffer;
}
